# Database Management Systems Lab

## Getting Started
To start MySQL / MariaDB in terminal, enter:
```
mysql -h 10.10.14.125 -u te{your roll number} -p
```
Then enter the password.

## Useful Commands

- `USE {db name}` : Uses the specified database.
```
USE 31380_db
```
- `CREATE TABLE {table name} (colname datatype, colname datatype, colname datatype);`: Creates a table
```
CREATE TABLE student (Roll INT, Name VARCHAR(150), Marks INT);
```
- `SHOW TABLES;` : Shows all tables present in the current database.
```
SHOW TABLES;
```
```
+--------------------+
| Tables_in_31380_db |
+--------------------+
| student            |
+--------------------+
1 row in set (0.00 sec)
```
- `DESCRIBE {table}` : Shows all info related to the given table.
```
DESCRIBE student;
```
```
+-------+------------------+------+-----+---------+----------------+
| Field | Type             | Null | Key | Default | Extra          |
+-------+------------------+------+-----+---------+----------------+
| id    | int(10) unsigned | NO   | PRI | NULL    | auto_increment |
| name  | varchar(150)     | NO   |     | NULL    |                |
| owner | varchar(150)     | NO   |     | NULL    |                |
| birth | date             | NO   |     | NULL    |                |
+-------+------------------+------+-----+---------+----------------+
4 rows in set (0.00 sec)
```
- `INSERT INTO {table} VALUES {records};`
```
INSERT INTO student values (01, 'ABC', 70);
INSERT INTO student values (02, 'DEF', 80), (03, 'GHI', 90);
```
