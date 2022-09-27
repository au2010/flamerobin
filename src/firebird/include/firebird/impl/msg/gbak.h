FB_IMPL_MSG_NO_SYMBOL(GBAK, 0, "could not locate appropriate error message")
FB_IMPL_MSG(GBAK, 1, gbak_unknown_switch, -901, "00", "000", "found unknown switch")
FB_IMPL_MSG(GBAK, 2, gbak_page_size_missing, -901, "00", "000", "page size parameter missing")
FB_IMPL_MSG(GBAK, 3, gbak_page_size_toobig, -901, "00", "000", "Page size specified (@1) greater than limit (32768 bytes)")
FB_IMPL_MSG(GBAK, 4, gbak_redir_ouput_missing, -901, "00", "000", "redirect location for output is not specified")
FB_IMPL_MSG(GBAK, 5, gbak_switches_conflict, -901, "00", "000", "conflicting switches for backup/restore")
FB_IMPL_MSG(GBAK, 6, gbak_unknown_device, -901, "00", "000", "device type @1 not known")
FB_IMPL_MSG(GBAK, 7, gbak_no_protection, -901, "00", "000", "protection is not there yet")
FB_IMPL_MSG(GBAK, 8, gbak_page_size_not_allowed, -901, "00", "000", "page size is allowed only on restore or create")
FB_IMPL_MSG(GBAK, 9, gbak_multi_source_dest, -901, "00", "000", "multiple sources or destinations specified")
FB_IMPL_MSG(GBAK, 10, gbak_filename_missing, -901, "00", "000", "requires both input and output filenames")
FB_IMPL_MSG(GBAK, 11, gbak_dup_inout_names, -901, "00", "000", "input and output have the same name.  Disallowed.")
FB_IMPL_MSG(GBAK, 12, gbak_inv_page_size, -901, "00", "000", "expected page size, encountered \"@1\"")
FB_IMPL_MSG(GBAK, 13, gbak_db_specified, -901, "00", "000", "REPLACE specified, but the first file @1 is a database")
FB_IMPL_MSG(GBAK, 14, gbak_db_exists, -901, "00", "000", "database @1 already exists.  To replace it, use the -REP switch")
FB_IMPL_MSG(GBAK, 15, gbak_unk_device, -901, "00", "000", "device type not specified")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 16, "cannot create APOLLO tape descriptor file @1")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 17, "cannot set APOLLO tape descriptor attribute for @1")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 18, "cannot create APOLLO cartridge descriptor file @1")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 19, "cannot close APOLLO tape descriptor file @1")
FB_IMPL_MSG(GBAK, 20, gbak_blob_info_failed, -901, "00", "000", "gds_$blob_info failed")
FB_IMPL_MSG(GBAK, 21, gbak_unk_blob_item, -901, "00", "000", "do not understand BLOB INFO item @1")
FB_IMPL_MSG(GBAK, 22, gbak_get_seg_failed, -901, "00", "000", "gds_$get_segment failed")
FB_IMPL_MSG(GBAK, 23, gbak_close_blob_failed, -901, "00", "000", "gds_$close_blob failed")
FB_IMPL_MSG(GBAK, 24, gbak_open_blob_failed, -901, "00", "000", "gds_$open_blob failed")
FB_IMPL_MSG(GBAK, 25, gbak_put_blr_gen_id_failed, -901, "00", "000", "Failed in put_blr_gen_id")
FB_IMPL_MSG(GBAK, 26, gbak_unk_type, -901, "00", "000", "data type @1 not understood")
FB_IMPL_MSG(GBAK, 27, gbak_comp_req_failed, -901, "00", "000", "gds_$compile_request failed")
FB_IMPL_MSG(GBAK, 28, gbak_start_req_failed, -901, "00", "000", "gds_$start_request failed")
FB_IMPL_MSG(GBAK, 29, gbak_rec_failed, -901, "00", "000", "gds_$receive failed")
FB_IMPL_MSG(GBAK, 30, gbak_rel_req_failed, -901, "00", "000", "gds_$release_request failed")
FB_IMPL_MSG(GBAK, 31, gbak_db_info_failed, -901, "00", "000", "gds_$database_info failed")
FB_IMPL_MSG(GBAK, 32, gbak_no_db_desc, -901, "00", "000", "Expected database description record")
FB_IMPL_MSG(GBAK, 33, gbak_db_create_failed, -901, "00", "000", "failed to create database @1")
FB_IMPL_MSG(GBAK, 34, gbak_decomp_len_error, -901, "00", "000", "RESTORE: decompression length error")
FB_IMPL_MSG(GBAK, 35, gbak_tbl_missing, -901, "00", "000", "cannot find table @1")
FB_IMPL_MSG(GBAK, 36, gbak_blob_col_missing, -901, "00", "000", "Cannot find column for BLOB")
FB_IMPL_MSG(GBAK, 37, gbak_create_blob_failed, -901, "00", "000", "gds_$create_blob failed")
FB_IMPL_MSG(GBAK, 38, gbak_put_seg_failed, -901, "00", "000", "gds_$put_segment failed")
FB_IMPL_MSG(GBAK, 39, gbak_rec_len_exp, -901, "00", "000", "expected record length")
FB_IMPL_MSG(GBAK, 40, gbak_inv_rec_len, -901, "00", "000", "wrong length record, expected @1 encountered @2")
FB_IMPL_MSG(GBAK, 41, gbak_exp_data_type, -901, "00", "000", "expected data attribute")
FB_IMPL_MSG(GBAK, 42, gbak_gen_id_failed, -901, "00", "000", "Failed in store_blr_gen_id")
FB_IMPL_MSG(GBAK, 43, gbak_unk_rec_type, -901, "00", "000", "do not recognize record type @1")
FB_IMPL_MSG(GBAK, 44, gbak_inv_bkup_ver, -901, "00", "000", "Expected backup version 1..10.  Found @1")
FB_IMPL_MSG(GBAK, 45, gbak_missing_bkup_desc, -901, "00", "000", "expected backup description record")
FB_IMPL_MSG(GBAK, 46, gbak_string_trunc, -901, "00", "000", "string truncated")
FB_IMPL_MSG(GBAK, 47, gbak_cant_rest_record, -901, "00", "000", "warning -- record could not be restored")
FB_IMPL_MSG(GBAK, 48, gbak_send_failed, -901, "00", "000", "gds_$send failed")
FB_IMPL_MSG(GBAK, 49, gbak_no_tbl_name, -901, "00", "000", "no table name for data")
FB_IMPL_MSG(GBAK, 50, gbak_unexp_eof, -901, "00", "000", "unexpected end of file on backup file")
FB_IMPL_MSG(GBAK, 51, gbak_db_format_too_old, -901, "00", "000", "database format @1 is too old to restore to")
FB_IMPL_MSG(GBAK, 52, gbak_inv_array_dim, -901, "00", "000", "array dimension for column @1 is invalid")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 53, "expected array version number @1 but instead found @2")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 54, "expected array dimension @1 but instead found @2")
FB_IMPL_MSG(GBAK, 55, gbak_xdr_len_expected, -901, "00", "000", "Expected XDR record length")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 56, "Unexpected I/O error while @1 backup file")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 57, "adding file @1, starting at page @2")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 58, "array")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 59, "backup")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 60, "    @1B(ACKUP_DATABASE)    backup database to file")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 61, "		backup file is compressed")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 62, "    @1D(EVICE)             backup file device type on APOLLO (CT or MT)")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 63, "    @1M(ETA_DATA)          backup or restore metadata only")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 64, "blob")
FB_IMPL_MSG(GBAK, 65, gbak_open_bkup_error, -901, "00", "000", "cannot open backup file @1")
FB_IMPL_MSG(GBAK, 66, gbak_open_error, -901, "00", "000", "cannot open status and error output file @1")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 67, "closing file, committing, and finishing")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 68, "committing metadata")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 69, "commit failed on table @1")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 70, "committing secondary files")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 71, "creating index @1")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 72, "committing data for table @1")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 73, "    @1C(REATE_DATABASE)    create database from backup file (restore)")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 74, "created database @1, page_size @2 bytes")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 75, "creating file @1")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 76, "creating indexes")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 77, "database @1 has a page size of @2 bytes.")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 78, "    @1I(NACTIVE)           deactivate indexes during restore")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 79, "do not understand BLOB INFO item @1")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 80, "do not recognize @1 attribute @2 -- continuing")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 81, "error accessing BLOB column @1 -- continuing")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 82, "Exiting before completion due to errors")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 83, "Exiting before completion due to errors")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 84, "column")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 85, "file")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 86, "file length")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 87, "filter")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 88, "finishing, closing, and going home")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 89, "function")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 90, "function argument")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 91, "gbak version @1")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 92, "domain")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 93, "index")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 94, "trigger @1 is invalid")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 95, "legal switches are:")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 96, "length given for initial file (@1) is less than minimum (@2)")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 97, "    @1E(XPAND)             no data compression")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 98, "    @1L(IMBO)              ignore transactions in limbo")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 99, "    @1O(NE_AT_A_TIME)      restore one table at a time")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 100, "opened file @1")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 101, "    @1P(AGE_SIZE)          override default page size")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 102, "page size")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 103, "page size specified (@1 bytes) rounded up to @2 bytes")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 104, "    @1Z                    print version number")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 105, "privilege")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 106, "     @1 records ignored")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 107, "   @1 records restored")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 108, "@1 records written")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 109, "    @1Y  <path>            redirect/suppress status message output")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 110, "Reducing the database page size from @1 bytes to @2 bytes")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 111, "table")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 112, "    @1REP(LACE_DATABASE)   replace database from backup file (restore)")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 113, "    @1V(ERIFY)             report each action taken")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 114, "restore failed for record in table @1")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 115, "    restoring column @1")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 116, "    restoring file @1")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 117, "    restoring filter @1")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 118, "restoring function @1")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 119, "    restoring argument for function @1")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 120, "     restoring gen id value of: @1")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 121, "restoring domain @1")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 122, "    restoring index @1")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 123, "    restoring privilege for user @1")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 124, "restoring data for table @1")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 125, "restoring security class @1")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 126, "    restoring trigger @1")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 127, "    restoring trigger message for @1")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 128, "    restoring type @1 for column @2")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 129, "started transaction")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 130, "starting transaction")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 131, "security class")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 132, "switches can be abbreviated to the unparenthesized characters")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 133, "transportable backup -- data in XDR format")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 134, "trigger")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 135, "trigger message")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 136, "trigger type")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 137, "unknown switch \"@1\"")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 138, "validation error on column in table @1")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 139, "    Version(s) for database \"@1\"")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 140, "view")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 141, "    writing argument for function @1")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 142, "    writing data for table @1")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 143, "     writing gen id of: @1")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 144, "         writing column @1")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 145, "    writing filter @1")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 146, "writing filters")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 147, "    writing function @1")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 148, "writing functions")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 149, "    writing domain @1")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 150, "writing domains")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 151, "    writing index @1")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 152, "    writing privilege for user @1")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 153, "    writing table @1")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 154, "writing tables")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 155, "    writing security class @1")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 156, "    writing trigger @1")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 157, "    writing trigger message for @1")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 158, "writing trigger messages")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 159, "writing triggers")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 160, "    writing type @1 for column @2")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 161, "writing types")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 162, "writing shadow files")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 163, "    writing shadow file @1")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 164, "writing id generators")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 165, "    writing generator @1 value @2")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 166, "readied database @1 for backup")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 167, "restoring table @1")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 168, "type")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 169, "gbak:")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 170, "committing metadata for table @1")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 171, "error committing metadata for table @1")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 172, "    @1K(ILL)               restore without creating shadows")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 173, "cannot commit index @1")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 174, "cannot commit files")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 175, "    @1T(RANSPORTABLE)      transportable backup -- data in XDR format")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 176, "closing file, committing, and finishing. @1 bytes written")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 177, "    @1G(ARBAGE_COLLECT)    inhibit garbage collection")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 178, "    @1IG(NORE)             ignore bad checksums")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 179, "	column @1 used in index @2 seems to have vanished")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 180, "index @1 omitted because @2 of the expected @3 keys were found")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 181, "    @1FA(CTOR)             blocking factor")
FB_IMPL_MSG(GBAK, 182, gbak_missing_block_fac, -901, "00", "000", "blocking factor parameter missing")
FB_IMPL_MSG(GBAK, 183, gbak_inv_block_fac, -901, "00", "000", "expected blocking factor, encountered \"@1\"")
FB_IMPL_MSG(GBAK, 184, gbak_block_fac_specified, -901, "00", "000", "a blocking factor may not be used in conjunction with device CT")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 185, "restoring generator @1 value: @2")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 186, "    @1OL(D_DESCRIPTIONS)   save old style metadata descriptions")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 187, "    @1N(O_VALIDITY)        do not restore database validity conditions")
FB_IMPL_MSG(GBAK, 188, gbak_missing_username, -901, "00", "000", "user name parameter missing")
FB_IMPL_MSG(GBAK, 189, gbak_missing_password, -901, "00", "000", "password parameter missing")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 190, "    @1PAS(SWORD)           Firebird password")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 191, "    @1USER                 Firebird user name")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 192, "writing stored procedures")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 193, "writing stored procedure @1")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 194, "writing parameter @1 for stored procedure")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 195, "restoring stored procedure @1")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 196, "    restoring parameter @1 for stored procedure")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 197, "writing exceptions")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 198, "writing exception @1")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 199, "restoring exception @1")
FB_IMPL_MSG(GBAK, 200, gbak_missing_skipped_bytes, -901, "00", "000", " missing parameter for the number of bytes to be skipped")
FB_IMPL_MSG(GBAK, 201, gbak_inv_skipped_bytes, -901, "00", "000", "expected number of bytes to be skipped, encountered \"@1\"")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 202, "adjusting an invalid decompression length from @1 to @2")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 203, "skipped @1 bytes after reading a bad attribute @2")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 204, "    @1S(KIP_BAD_DATA)      skip number of bytes after reading bad data")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 205, "skipped @1 bytes looking for next valid attribute, encountered attribute @2")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 206, "writing table constraints")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 207, "writing constraint @1")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 208, "table constraint")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 209, "writing referential constraints")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 210, "writing check constraints")
FB_IMPL_MSG_SYMBOL(GBAK, 211, msgVerbose_write_charsets, "writing character sets")
FB_IMPL_MSG_SYMBOL(GBAK, 212, msgVerbose_write_collations, "writing collations")
FB_IMPL_MSG(GBAK, 213, gbak_err_restore_charset, -901, "00", "000", "character set")
FB_IMPL_MSG_SYMBOL(GBAK, 214, msgVerbose_restore_charset, "writing character set @1")
FB_IMPL_MSG(GBAK, 215, gbak_err_restore_collation, -901, "00", "000", "collation")
FB_IMPL_MSG_SYMBOL(GBAK, 216, msgVerbose_restore_collation, "writing collation @1")
FB_IMPL_MSG(GBAK, 220, gbak_read_error, -901, "00", "000", "Unexpected I/O error while reading from backup file")
FB_IMPL_MSG(GBAK, 221, gbak_write_error, -901, "00", "000", "Unexpected I/O error while writing to backup file")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 222, "\n\nCould not open file name \"@1\"")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 223, "\n\nCould not write to file \"@1\"")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 224, "\n\nCould not read from file \"@1\"")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 225, "Done with volume #@1, \"@2\"")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 226, "	Press return to reopen that file, or type a new\n	name followed by return to open a different file.")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 227, "Type a file name to open and hit return")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 228, "  Name: ")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 229, "\n\nERROR: Backup incomplete")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 230, "Expected backup start time @1, found @2")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 231, "Expected backup database @1, found @2")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 232, "Expected volume number @1, found volume @2")
FB_IMPL_MSG(GBAK, 233, gbak_db_in_use, -901, "00", "000", "could not drop database @1 (no privilege or database might be in use)")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 234, "Skipped bad security class entry: @1")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 235, "Unknown V3 SUB_TYPE: @1 in FIELD: @2.")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 236, "Converted V3 sub_type: @1 to character_set_id: @2 and collate_id: @3.")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 237, "Converted V3 scale: @1 to character_set_id: @2 and callate_id: @3.")
FB_IMPL_MSG(GBAK, 238, gbak_sysmemex, -901, "00", "000", "System memory exhausted")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 239, "    @1NT                   Non-Transportable backup file format")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 240, "Index \"@1\" failed to activate because:")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 241, "  The unique index has duplicate values or NULLs.")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 242, "  Delete or Update duplicate values or NULLs, and activate index with")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 243, "  ALTER INDEX \"@1\" ACTIVE;")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 244, "  Not enough disk space to create the sort file for an index.")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 245, "  Set the TMP environment variable to a directory on a filesystem that does have enough space, and activate index with")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 246, "Database is not online due to failure to activate one or more indices.")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 247, "Run gfix -online to bring database online without active indices.")
FB_IMPL_MSG_SYMBOL(GBAK, 248, write_role_1, "writing SQL roles")
FB_IMPL_MSG_SYMBOL(GBAK, 249, write_role_2, "    writing SQL role: @1")
FB_IMPL_MSG(GBAK, 250, gbak_restore_role_failed, -901, "00", "000", "SQL role")
FB_IMPL_MSG_SYMBOL(GBAK, 251, restore_role, "    restoring SQL role: @1")
FB_IMPL_MSG_SYMBOL(GBAK, 252, gbak_role_op, "    @1RO(LE)               Firebird SQL role")
FB_IMPL_MSG(GBAK, 253, gbak_role_op_missing, -901, "00", "000", "SQL role parameter missing")
FB_IMPL_MSG_SYMBOL(GBAK, 254, gbak_convert_ext_tables, "    @1CO(NVERT)            backup external files as tables")
FB_IMPL_MSG_SYMBOL(GBAK, 255, gbak_warning, "gbak: WARNING:")
FB_IMPL_MSG_SYMBOL(GBAK, 256, gbak_error, "gbak: ERROR:")
FB_IMPL_MSG_SYMBOL(GBAK, 257, gbak_page_buffers, "    @1BU(FFERS)            override page buffers default")
FB_IMPL_MSG(GBAK, 258, gbak_page_buffers_missing, -901, "00", "000", "page buffers parameter missing")
FB_IMPL_MSG(GBAK, 259, gbak_page_buffers_wrong_param, -901, "00", "000", "expected page buffers, encountered \"@1\"")
FB_IMPL_MSG(GBAK, 260, gbak_page_buffers_restore, -901, "00", "000", "page buffers is allowed only on restore or create")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 261, "Starting with volume #@1, \"@2\"")
FB_IMPL_MSG(GBAK, 262, gbak_inv_size, -901, "00", "000", "size specification either missing or incorrect for file @1")
FB_IMPL_MSG(GBAK, 263, gbak_file_outof_sequence, -901, "00", "000", "file @1 out of sequence")
FB_IMPL_MSG(GBAK, 264, gbak_join_file_missing, -901, "00", "000", "can't join -- one of the files missing")
FB_IMPL_MSG(GBAK, 265, gbak_stdin_not_supptd, -901, "00", "000", " standard input is not supported when using join operation")
FB_IMPL_MSG(GBAK, 266, gbak_stdout_not_supptd, -901, "00", "000", "standard output is not supported when using split operation or in verbose mode")
FB_IMPL_MSG(GBAK, 267, gbak_bkup_corrupt, -901, "00", "000", "backup file @1 might be corrupt")
FB_IMPL_MSG(GBAK, 268, gbak_unk_db_file_spec, -901, "00", "000", "database file specification missing")
FB_IMPL_MSG(GBAK, 269, gbak_hdr_write_failed, -901, "00", "000", "can't write a header record to file @1")
FB_IMPL_MSG(GBAK, 270, gbak_disk_space_ex, -901, "00", "000", "free disk space exhausted")
FB_IMPL_MSG(GBAK, 271, gbak_size_lt_min, -901, "00", "000", "file size given (@1) is less than minimum allowed (@2)")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 272, "Warning -- free disk space exhausted for file @1, the rest of the bytes (@2) will be written to file @3")
FB_IMPL_MSG(GBAK, 273, gbak_svc_name_missing, -901, "00", "000", "service name parameter missing")
FB_IMPL_MSG(GBAK, 274, gbak_not_ownr, -901, "00", "000", "Cannot restore over current database, must be SYSDBA or owner of the existing database.")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 275, "")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 276, "    @1USE_(ALL_SPACE)      do not reserve space for record versions")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 277, "    @1SE(RVICE)            use services manager")
FB_IMPL_MSG_SYMBOL(GBAK, 278, gbak_opt_mode, "    @1MO(DE) <access>      \"read_only\" or \"read_write\" access")
FB_IMPL_MSG(GBAK, 279, gbak_mode_req, -901, "00", "000", "\"read_only\" or \"read_write\" required")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 280, "setting database to read-only access")
FB_IMPL_MSG(GBAK, 281, gbak_just_data, -901, "00", "000", "just data ignore all constraints etc.")
FB_IMPL_MSG(GBAK, 282, gbak_data_only, -901, "00", "000", "restoring data only ignoring foreign key, unique, not null & other constraints")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 283, "closing file, committing, and finishing. @1 bytes written")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 284, "    @1R(ECREATE_DATABASE) [O(VERWRITE)] create (or replace if OVERWRITE used)\\n				database from backup file (restore)")
FB_IMPL_MSG_SYMBOL(GBAK, 285, gbak_activating_idx, "    activating and creating deferred index @1")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 286, "check constraint")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 287, "exception")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 288, "array dimensions")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 289, "generator")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 290, "procedure")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 291, "procedure parameter")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 292, "referential constraint")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 293, "type (in RDB$TYPES)")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 294, "    @1NOD(BTRIGGERS)       do not run database triggers")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 295, "    @1TRU(STED)            use trusted authentication")
FB_IMPL_MSG_SYMBOL(GBAK, 296, write_map_1, "writing names mapping")
FB_IMPL_MSG_SYMBOL(GBAK, 297, write_map_2, "    writing map for @1")
FB_IMPL_MSG_SYMBOL(GBAK, 298, get_map_1, "    restoring map for @1")
FB_IMPL_MSG_SYMBOL(GBAK, 299, get_map_2, "name mapping")
FB_IMPL_MSG_SYMBOL(GBAK, 300, get_map_3, "cannot restore arbitrary mapping")
FB_IMPL_MSG_SYMBOL(GBAK, 301, get_map_4, "restoring names mapping")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 302, "    @1FIX_FSS_D(ATA)       fix malformed UNICODE_FSS data")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 303, "    @1FIX_FSS_M(ETADATA)   fix malformed UNICODE_FSS metadata")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 304, "Character set parameter missing")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 305, "Character set @1 not found")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 306, "    @1FE(TCH_PASSWORD)     fetch password from file")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 307, "too many passwords provided")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 308, "could not open password file @1, errno @2")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 309, "could not read password file @1, errno @2")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 310, "empty password file @1")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 311, "Attribute @1 was already processed for exception @2")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 312, "Skipping attribute @1 because the message already exists for exception @2")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 313, "Trying to recover from unexpected attribute @1 due to wrong message length for exception @2")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 314, "Attribute not specified for storing text bigger than 255 bytes")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 315, "Unable to store text bigger than 65536 bytes")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 316, "Failed while adjusting the security class name")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 317, "Usage:")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 318, "     gbak -b <db set> <backup set> [backup options] [general options]")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 319, "     gbak -c <backup set> <db set> [restore options] [general options]")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 320, "     <db set> = <database> | <db1 size1>...<dbN> (size in db pages)")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 321, "     <backup set> = <backup> | <bk1 size1>...<bkN> (size in bytes = n[K|M|G])")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 322, "     -recreate overwrite and -replace can be used instead of -c")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 323, "backup options are:")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 324, "restore options are:")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 325, "general options are:")
FB_IMPL_MSG(GBAK, 326, gbak_missing_interval, -901, "00", "000", "verbose interval value parameter missing")
FB_IMPL_MSG(GBAK, 327, gbak_wrong_interval, -901, "00", "000", "verbose interval value cannot be smaller than @1")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 328, "    @1VERBI(NT) <n>        verbose information with explicit interval")
FB_IMPL_MSG(GBAK, 329, gbak_verify_verbint, -901, "00", "000", "verify (verbose) and verbint options are mutually exclusive")
FB_IMPL_MSG(GBAK, 330, gbak_option_only_restore, -901, "00", "000", "option -@1 is allowed only on restore or create")
FB_IMPL_MSG(GBAK, 331, gbak_option_only_backup, -901, "00", "000", "option -@1 is allowed only on backup")
FB_IMPL_MSG(GBAK, 332, gbak_option_conflict, -901, "00", "000", "options -@1 and -@2 are mutually exclusive")
FB_IMPL_MSG(GBAK, 333, gbak_param_conflict, -901, "00", "000", "parameter for option -@1 was already specified with value \"@2\"")
FB_IMPL_MSG(GBAK, 334, gbak_option_repeated, -901, "00", "000", "option -@1 was already specified")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 335, "writing package @1")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 336, "writing packages")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 337, "restoring package @1")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 338, "package")
FB_IMPL_MSG(GBAK, 339, gbak_max_dbkey_recursion, -901, "00", "000", "dependency depth greater than @1 for view @2")
FB_IMPL_MSG(GBAK, 340, gbak_max_dbkey_length, -901, "00", "000", "value greater than @1 when calculating length of rdb$db_key for view @2")
FB_IMPL_MSG(GBAK, 341, gbak_invalid_metadata, -901, "00", "000", "Invalid metadata detected. Use -FIX_FSS_METADATA option.")
FB_IMPL_MSG(GBAK, 342, gbak_invalid_data, -901, "00", "000", "Invalid data detected. Use -FIX_FSS_DATA option.")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 343, "text for attribute @1 is too large in @2, truncating to @3 bytes")
FB_IMPL_MSG(GBAK, 344, gbak_inv_bkup_ver2, -901, "00", "000", "Expected backup version @2..@3.  Found @1")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 345, "    writing view @1")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 346, "    table @1 is a view")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 347, "writing security classes")
FB_IMPL_MSG(GBAK, 348, gbak_db_format_too_old2, -901, "00", "000", "database format @1 is too old to backup")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 349, "backup version is @1")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 350, "adjusting system generators")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 351, "Error closing database, but backup file is OK")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 352, "database")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 353, "required mapping attributes are missing in backup file")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 354, "missing regular expression to skip tables")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 355, "    @1SKIP_D(ATA)          skip data for table")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 356, "regular expression to skip tables was already set")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 357, "adjusting views dbkey length")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 358, "updating ownership of packages, procedures and tables")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 359, "adding missing privileges")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 360, "adjusting the ONLINE and FORCED WRITES flags")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 361, "    @1ST(ATISTICS) TDRW    show statistics:")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 362, "        T                 time from start")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 363, "        D                 delta time")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 364, "        R                 page reads")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 365, "        W                 page writes")
FB_IMPL_MSG_SYMBOL(GBAK, 366, gbak_missing_perf, "statistics parameter missing")
FB_IMPL_MSG_SYMBOL(GBAK, 367, gbak_wrong_perf, "wrong char \"@1\" at statistics parameter")
FB_IMPL_MSG_SYMBOL(GBAK, 368, gbak_too_long_perf, "too many chars at statistics parameter")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 369, "total statistics")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 370, "could not append BLOB data to batch")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 371, "could not start batch when restoring table @1, trying old way")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 372, "    @1KEYNAME              name of a key to be used for encryption")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 373, "    @1CRYPT                crypt plugin name")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 374, "    @1ZIP                  backup file is in zip compressed format")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 375, "Keyname parameter missing")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 376, "Key holder parameter missing but backup file is encrypted")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 377, "CryptPlugin parameter missing")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 378, "Unknown crypt plugin name - use -CRYPT switch")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 379, "Inflate error @1")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 380, "Deflate error @1")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 381, "Key holder parameter missing")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 382, "    @1KEYHOLDER            name of a key holder plugin")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 383, "Decompression stream init error @1")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 384, "Compression stream init error @1")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 385, "Invalid reply from getInfo() when waiting for DB encryption")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 386, "Problems with just created database encryption")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 387, "Skipped trigger @1 on system table @2")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 388, "    @1INCLUDE(_DATA)       backup data of table(s)")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 389, "missing regular expression to include tables")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 390, "regular expression to include tables was already set")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 391, "writing database create grants")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 392, "    database create grant for @1")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 393, "    restoring database create grant for @1")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 394, "restoring database create grants")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 395, "database create grant")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 396, "writing publications")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 397, "    writing publication @1")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 398, "    writing publication for table @1")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 399, "restoring publication @1")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 400, "publication")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 401, "restoring publication for table @1")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 402, "publication for table")
FB_IMPL_MSG_SYMBOL(GBAK, 403, gbak_opt_replica, "    @1REPLICA <mode>      \"none\", \"read_only\" or \"read_write\" replica mode")
FB_IMPL_MSG_SYMBOL(GBAK, 404, gbak_replica_req, "\"none\", \"read_only\" or \"read_write\" required")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 405, "could not access batch parameters")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 406, "    @1PAR(ALLEL)           parallel workers")
FB_IMPL_MSG_SYMBOL(GBAK, 407, gbak_missing_prl_wrks, "parallel workers parameter missing")
FB_IMPL_MSG_SYMBOL(GBAK, 408, gbak_inv_prl_wrks, "expected parallel workers, encountered \"@1\"")
FB_IMPL_MSG_NO_SYMBOL(GBAK, 409, "    @1D(IRECT_IO)          direct IO for backup file(s)")
