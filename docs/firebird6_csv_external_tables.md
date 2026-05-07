# Firebird 6.0 CSV External Tables Support in FlameRobin

FlameRobin now supports the new CSV External Tables feature introduced in Firebird 6.0 (ODS 14.x).

## Overview

Firebird 6.0 allows creating external tables that are backed by delimited text files (CSV, TSV, etc.), rather than the traditional fixed-width binary format. This makes it much easier to import and export data using standard formats.

## Creating a CSV External Table

To create a new CSV external table, right-click on the **Tables** folder in the database tree and select **Create new CSV external table...**.

This will open a SQL editor with a template like this:

```sql
CREATE TABLE table_name
EXTERNAL 'file_path'
FORMAT CSV (
    DELIMITER ',',
    QUOTE '"',
    ESCAPE '"',
    SKIP_ROWS 1,
    NULL AS ''
)
(
    column_name <datatype>,
    ...
);
```

### Supported Options

- **DELIMITER**: The character used to separate fields (default is `,`).
- **QUOTE**: The character used to enclose string fields (default is `"`).
- **ESCAPE**: The character used to escape the quote character (default is `"`).
- **SKIP_ROWS**: The number of header rows to skip at the beginning of the file.
- **NULL AS**: The string that represents a NULL value in the file.

## Viewing Table Properties

When you select a CSV external table in the tree, the property page will display the external file path and the CSV formatting options used.

## DDL Generation

When extracting DDL for a CSV external table, FlameRobin will correctly include the `FORMAT CSV` clause and all defined options.

## Metadata Storage

Firebird 6.0 stores this information in:
- `RDB$RELATIONS.RDB$EXTERNAL_FORMAT`: `1` for CSV.
- `RDB$EXTERNAL_TABLE_OPTIONS`: Stores the name-value pairs for the CSV options.

## Requirements

- Firebird 6.0 or later.
- ODS 14.0 or later.
- `ExternalFileAccess` in `firebird.conf` must be configured to allow access to the external file location.
