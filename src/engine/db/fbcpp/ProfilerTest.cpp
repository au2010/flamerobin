/*
  Copyright (c) 2004-2026 The FlameRobin Development Team

  Permission is hereby granted, free of charge, to any person obtaining
  a copy of this software and associated documentation files (the
  "Software"), to deal in the Software without restriction, including
  without limitation the rights to use, copy, modify, merge, publish,
  distribute, sublicense, and/or sell copies of the Software, and to
  permit persons to whom the Software is furnished to do so, subject to
  the following conditions:

  The above copyright notice and this permission notice shall be included
  in all copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
  EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
  MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
  IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
  CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
  TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
  SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#include <ibpp.h>

#include "engine/db/DatabaseFactory.h"
#include "engine/db/IDatabase.h"
#include "engine/db/ITransaction.h"
#include "engine/db/IStatement.h"
#include "engine/db/TestUtils.h"

int main()
{
    const char* envServer = std::getenv("IBPP_TEST_SERVER");
    const std::string serverName = envServer ? envServer : "";
    if (serverName.empty())
    {
        std::cout << "IBPP_TEST_SERVER is not set, skipping ProfilerTest.\n";
        return 0;
    }

    const std::string dbName = fr_test::getTestDbPath("profiler_test");

    // Create DB using IBPP
    try 
    {
        IBPP::Database db = IBPP::DatabaseFactory(serverName, dbName, "SYSDBA", "masterkey");
        db->Create(3);
    }
    catch (const IBPP::Exception& e)
    {
        fr_test::printException(e, "create test database");
        return 1;
    }

    bool ok = true;
    std::cout << "Starting RDB$PROFILER extensive tests...\n";

    try 
    {
        fr::IDatabasePtr db = fr::DatabaseFactory::createDatabase(fr::DatabaseBackend::FbCpp);
        std::string fullConnStr = serverName + ":" + dbName;
        std::cout << "  Connecting to database: " << fullConnStr << "\n";
        db->setConnectionString(fullConnStr);
        db->setCredentials("SYSDBA", "masterkey");
        try {
            db->connect();
        } catch (const std::exception& e) {
            std::cerr << "    FAILED to connect to " << fullConnStr << " using fb-cpp backend\n";
            throw;
        }

        std::cout << "  Engine version: " << db->getEngineVersion() << "\n";

        fr::ITransactionPtr tr = db->createTransaction();
        tr->start();

        fr::IStatementPtr st = db->createStatement(tr);
        
        // Check if RDB$PROFILER exists
        try {
            st->prepare("SELECT 1 FROM RDB$PACKAGES WHERE RDB$PACKAGE_NAME = 'RDB$PROFILER'");
            st->execute();
            if (!st->fetch())
            {
                std::cout << "RDB$PROFILER package not found, skipping tests.\n";
                tr->rollback();
                db->disconnect();
                return 0;
            }
        } catch(const std::exception& e) {
            fr_test::printException(e, "checking for RDB$PROFILER");
            return 0;
        }

        // Check active profiler plugin
        try {
            st->prepare("SELECT RDB$CONFIG_VALUE FROM RDB$CONFIG WHERE RDB$CONFIG_NAME = 'Default_Profiler'");
            st->execute();
            if (st->fetch())
                std::cout << "    Debug: Default_Profiler = " << st->getString(0) << "\n";
            else
                std::cout << "    Debug: Default_Profiler NOT SET in RDB$CONFIG\n";
        } catch(...) {
             std::cout << "    Debug: RDB$CONFIG check failed (normal on older versions)\n";
        }

        // Check if profiler tables exist
        std::vector<std::string> tables = { "PLG$PROF_SESSIONS", "PLG$PROF_STATEMENTS", "PLG$PROF_RECORD_SOURCES", "PLG$PROF_RECORD_SOURCE_STATS", "PLG$PROF_REQUESTS" };
        for (const auto& t : tables)
        {
            try {
                st->prepare("SELECT COUNT(*) FROM " + t);
                st->execute();
                if (st->fetch())
                    std::cout << "    Debug: Table " << t << " exists, count = " << st->getInt32(0) << "\n";
            } catch(const std::exception& e) {
                std::cout << "    Debug: Table " << t << " check FAILED: " << e.what() << "\n";
            }
        }

        // Create table first, then profile
        st->prepare("CREATE TABLE t1 (id INT PRIMARY KEY, val VARCHAR(100))");
        st->execute();
        tr->commitRetain();

        // Test 1: Simple Profiling Session
        std::cout << "  Test 1: Simple Profiling Session...\n";
        st->prepare("SELECT RDB$PROFILER.START_SESSION(?) FROM RDB$DATABASE");
        st->setString(0, "Test Session");
        st->execute();
        int64_t sessionId = 0;
        if (st->fetch())
            sessionId = st->getInt64(0);
        
        std::cout << "    Debug: Session ID = " << sessionId << "\n";
        ok = fr_test::check(sessionId != 0, "Session started") && ok;

        // Use INSERT ... SELECT to ensure there is a record source to profile
        std::cout << "    Executing INSERT ... SELECT...\n";
        st->prepare("INSERT INTO t1 (id, val) SELECT 1, 'test' FROM RDB$DATABASE");
        st->execute();
        
        // Add a simple SELECT as well
        std::cout << "    Executing SELECT * FROM t1...\n";
        st->prepare("SELECT * FROM t1");
        st->execute();
        while (st->fetch()) {}

        tr->commitRetain();

        // Flush and finish
        try {
            std::cout << "    Flushing stats...\n";
            st->prepare("EXECUTE PROCEDURE RDB$PROFILER.FLUSH_STATS");
            st->execute();
            std::cout << "    Debug: FLUSH_STATS executed.\n";
        } catch(const std::exception& e) {
             std::cout << "    Debug: FLUSH_STATS failed: " << e.what() << " (continuing...)\n";
        }

        std::cout << "    Finishing session...\n";
        st->prepare("EXECUTE PROCEDURE RDB$PROFILER.FINISH_SESSION(TRUE)");
        st->execute();
        std::cout << "    Debug: FINISH_SESSION executed.\n";
        tr->commit();

        // Start new transaction to check results
        tr = db->createTransaction();
        tr->start();
        st = db->createStatement(tr);

        // Check statements first
        st->prepare("SELECT COUNT(*) FROM PLG$PROF_STATEMENTS WHERE PROFILE_ID = ?");
        st->setInt64(0, sessionId);
        st->execute();
        int stmtCount = 0;
        if (st->fetch()) stmtCount = st->getInt32(0);
        std::cout << "    Debug: Statement count in PLG$PROF_STATEMENTS for session " << sessionId << ": " << stmtCount << "\n";

        if (stmtCount == 0)
        {
            std::cout << "    Debug: Dumping PLG$PROF_STATEMENTS for all sessions:\n";
            st->prepare("SELECT PROFILE_ID, STATEMENT_ID, SQL_TEXT FROM PLG$PROF_STATEMENTS");
            st->execute();
            while (st->fetch())
            {
                std::cout << "      Profile: " << st->getInt64(0) << ", Stmt ID: " << st->getInt32(1) << ", SQL: " << st->getString(2).substr(0, 50) << "...\n";
            }
        }

        // Give Firebird a moment to flush profiler data if needed
        st->prepare("SELECT COUNT(*) FROM PLG$PROF_RECORD_SOURCE_STATS WHERE PROFILE_ID = ?");
        st->setInt64(0, sessionId);
        st->execute();
        int count = 0;
        if (st->fetch())
            count = st->getInt32(0);
        
        std::cout << "    Debug: Record source stats count for session " << sessionId << ": " << count << "\n";

        if (count == 0)
        {
             std::cout << "    FAILURE: No record source stats found for session " << sessionId << "\n";
             // Debug: check session and profiling setup
             st->prepare("SELECT PROFILE_ID, ATTACHMENT_ID, DESCRIPTION, STATE FROM PLG$PROF_SESSIONS WHERE PROFILE_ID = ?");
             st->setInt64(0, sessionId);
             st->execute();
             if (st->fetch())
             {
                 std::cout << "    Debug: Session exists: " << st->getInt64(0) 
                           << ", Attachment: " << st->getInt64(1)
                           << ", Description: " << st->getString(2)
                           << ", State: " << st->getInt32(3) << "\n";
             }
             else
             {
                 std::cout << "    Debug: Session NOT FOUND in PLG$PROF_SESSIONS for ID " << sessionId << "\n";
             }
             
             st->prepare("SELECT COUNT(*) FROM PLG$PROF_RECORD_SOURCES WHERE PROFILE_ID = ?");
             st->setInt64(0, sessionId);
             st->execute();
             int rsCount = 0;
             if (st->fetch()) rsCount = st->getInt32(0);
             std::cout << "    Debug: Record sources defined for this session: " << rsCount << "\n";

             st->prepare("SELECT MON$ATTACHMENT_ID, MON$USER, MON$REMOTE_PROTOCOL FROM MON$ATTACHMENTS WHERE MON$ATTACHMENT_ID = CURRENT_CONNECTION");
             st->execute();
             if (st->fetch())
             {
                 std::cout << "    Debug: Current Connection: " << st->getInt64(0) 
                           << ", User: " << st->getString(1) 
                           << ", Protocol: " << st->getString(2) << "\n";
             }
        }

        ok = fr_test::check(count > 0, "Record source stats collected for INSERT ... SELECT") && ok;

        // Test 2: Nested PSQL calls
        std::cout << "  Test 2: Nested PSQL calls...\n";
        st->prepare("CREATE PROCEDURE p_child AS BEGIN END");
        st->execute();
        st->prepare("CREATE PROCEDURE p_parent AS BEGIN EXECUTE PROCEDURE p_child; END");
        st->execute();
        tr->commitRetain();

        st->prepare("SELECT RDB$PROFILER.START_SESSION(?) FROM RDB$DATABASE");
        st->setString(0, "Nested Session");
        st->execute();
        sessionId = 0;
        if (st->fetch())
            sessionId = st->getInt64(0);

        std::cout << "    Executing parent procedure...\n";
        st->prepare("EXECUTE PROCEDURE p_parent");
        st->execute();

        try {
            st->prepare("EXECUTE PROCEDURE RDB$PROFILER.FLUSH_STATS");
            st->execute();
        } catch(...) {}

        st->prepare("EXECUTE PROCEDURE RDB$PROFILER.FINISH_SESSION(TRUE)");
        st->execute();

        st->prepare("SELECT COUNT(DISTINCT REQUEST_NAME) FROM PLG$PROF_REQUESTS WHERE PROFILE_ID = ?");
        st->setInt64(0, sessionId);
        st->execute();
        count = 0;
        if (st->fetch())
            count = st->getInt32(0);
        
        std::cout << "    Debug: Distinct request count for nested session " << sessionId << ": " << count << "\n";
        if (count < 2)
        {
            std::cout << "    Debug: Dumping PLG$PROF_REQUESTS for session " << sessionId << ":\n";
            st->prepare("SELECT REQUEST_ID, REQUEST_NAME, CALLER_ID FROM PLG$PROF_REQUESTS WHERE PROFILE_ID = ?");
            st->setInt64(0, sessionId);
            st->execute();
            while (st->fetch())
            {
                std::cout << "      Req ID: " << st->getInt32(0) << ", Name: " << st->getString(1) << ", Caller ID: " << st->getInt32(2) << "\n";
            }
        }
        ok = fr_test::check(count >= 2, "Stats collected for both parent and child procedures") && ok;

        // Test 3: Triggers
        std::cout << "  Test 3: Triggers...\n";
        st->prepare("CREATE TABLE t2 (id INT)");
        st->execute();
        st->prepare("CREATE TRIGGER t2_ai FOR t2 AFTER INSERT AS BEGIN END");
        st->execute();
        tr->commitRetain();

        st->prepare("SELECT RDB$PROFILER.START_SESSION(?) FROM RDB$DATABASE");
        st->setString(0, "Trigger Session");
        st->execute();
        sessionId = 0;
        if (st->fetch())
            sessionId = st->getInt64(0);

        st->prepare("INSERT INTO t2 VALUES (1)");
        st->execute();

        try {
            st->prepare("EXECUTE PROCEDURE RDB$PROFILER.FLUSH_STATS");
            st->execute();
        } catch(...) {}

        st->prepare("EXECUTE PROCEDURE RDB$PROFILER.FINISH_SESSION(TRUE)");
        st->execute();

        st->prepare("SELECT COUNT(*) FROM PLG$PROF_REQUESTS WHERE PROFILE_ID = ? AND REQUEST_NAME = 'T2_AI'");
        st->setInt64(0, sessionId);
        st->execute();
        count = 0;
        if (st->fetch())
            count = st->getInt32(0);
        
        std::cout << "    Debug: Trigger stats count for session " << sessionId << ": " << count << "\n";
        if (count == 0)
        {
            std::cout << "    Debug: Dumping PLG$PROF_REQUESTS for session " << sessionId << ":\n";
            st->prepare("SELECT REQUEST_ID, REQUEST_NAME FROM PLG$PROF_REQUESTS WHERE PROFILE_ID = ?");
            st->setInt64(0, sessionId);
            st->execute();
            while (st->fetch())
            {
                std::cout << "      Req ID: " << st->getInt32(0) << ", Name: " << st->getString(1) << "\n";
            }
        }
        ok = fr_test::check(count > 0, "Stats collected for trigger") && ok;

        // Test 4: Record Source Stats with JOIN
        std::cout << "  Test 4: Record Source Stats with JOIN...\n";
        st->prepare("SELECT RDB$PROFILER.START_SESSION(?) FROM RDB$DATABASE");
        st->setString(0, "JOIN Session");
        st->execute();
        sessionId = 0;
        if (st->fetch())
            sessionId = st->getInt64(0);

        st->prepare("SELECT COUNT(*) FROM t1 a JOIN t2 b ON a.id = b.id");
        st->execute();
        if (st->fetch()) {}

        try {
            st->prepare("EXECUTE PROCEDURE RDB$PROFILER.FLUSH_STATS");
            st->execute();
        } catch(...) {}

        st->prepare("EXECUTE PROCEDURE RDB$PROFILER.FINISH_SESSION(TRUE)");
        st->execute();

        st->prepare("SELECT COUNT(*) FROM PLG$PROF_RECORD_SOURCE_STATS WHERE PROFILE_ID = ?");
        st->setInt64(0, sessionId);
        st->execute();
        count = 0;
        if (st->fetch())
            count = st->getInt32(0);
        
        std::cout << "    Debug: Record source stats count for JOIN session " << sessionId << ": " << count << "\n";
        if (count < 2)
        {
            std::cout << "    Debug: Dumping PLG$PROF_RECORD_SOURCES for session " << sessionId << ":\n";
            st->prepare("SELECT STATEMENT_ID, RECORD_SOURCE_ID, PARENT_ID, LEVEL, LINE, COLUMN FROM PLG$PROF_RECORD_SOURCES WHERE PROFILE_ID = ?");
            st->setInt64(0, sessionId);
            st->execute();
            while (st->fetch())
            {
                std::cout << "      Stmt: " << st->getInt32(0) << ", RS ID: " << st->getInt32(1) << ", Parent: " << st->getInt32(2) 
                          << ", Level: " << st->getInt32(3) << ", Line: " << st->getInt32(4) << ", Col: " << st->getInt32(5) << "\n";
            }
        }
        ok = fr_test::check(count >= 2, "Record source stats collected for JOIN") && ok;

        tr->commit();
        db->disconnect();
    }
    catch (const std::exception& e)
    {
        fr_test::printException(e, "ProfilerTest");
        ok = false;
    }

    // Cleanup
    try 
    {
        IBPP::Database db = IBPP::DatabaseFactory(serverName, dbName, "SYSDBA", "masterkey");
        db->Connect();
        db->Drop();
    }
    catch (...) {}

    if (ok)
    {
        std::cout << "ALL Profiler TESTS PASSED\n";
        return 0;
    }
    else
    {
        std::cout << "SOME Profiler TESTS FAILED\n";
        return 1;
    }
}
