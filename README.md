# Database Management Systems Lab

## Getting Started
To start MySQL / MariaDB in terminal, enter:
```
mysql -h 10.10.14.125 -u te{your roll number} -p
```
Then enter the password.

## Useful Commands
### USE
`USE {db name}` : Uses the specified database.
```
USE 31380_db
```
---
### CREATE
`CREATE TABLE {table name} (colname datatype, colname datatype, colname datatype);`: Creates a table
```
CREATE TABLE student (Roll INT, Name VARCHAR(150), Marks INT);
```
---
### SHOW
`SHOW TABLES;` : Shows all tables present in the current database.
```
SHOW TABLES;
```
Output:
```
+--------------------+
| Tables_in_31380_db |
+--------------------+
| student            |
+--------------------+
1 row in set (0.00 sec)
```
---
### DESCRIBE
`DESCRIBE {table}` : Shows all info related to the given table.
```
DESCRIBE student;
```
Output:
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
---
### INSERT
`INSERT INTO {table} VALUES {records};`
```
INSERT INTO student values (01, 'ABC', 70);
INSERT INTO student values (02, 'DEF', 80), (03, 'GHI', 90);
```
---
### SELECT
`SELECT {field names / *} FROM {table name} WHERE {condition};`
```
SELECT * from student;
```
Output:
```
+------+------+-------+
| Roll | name | Marks |
+------+------+-------+
|    1 | ABC  |    70 |
|    2 | DEF  |    80 |
|    3 | GHI  |    90 |
|    4 | JKL  |    65 |
|    5 | MNO  |    75 |
+------+------+-------+
```
More Examples:
```
MariaDB [31380_db]> SELECT 5 from student;
+---+
| 5 |
+---+
| 5 |
| 5 |
| 5 |
| 5 |
| 5 |
+---+
5 rows in set (0.001 sec)

MariaDB [31380_db]> SELECT Roll from student;
+------+
| Roll |
+------+
|    1 |
|    2 |
|    3 |
|    4 |
|    5 |
+------+
5 rows in set (0.001 sec)

MariaDB [31380_db]> SELECT Marks from student;
+-------+
| Marks |
+-------+
|    70 |
|    80 |
|    90 |
|    65 |
|    75 |
+-------+
5 rows in set (0.001 sec)

MariaDB [31380_db]> SELECT * FROM student where Roll=5;
+------+------+-------+
| Roll | name | Marks |
+------+------+-------+
|    5 | MNO  |    75 |
+------+------+-------+
1 row in set (0.001 sec)

MariaDB [31380_db]> SELECT * FROM student where Name='ABC';
+------+------+-------+
| Roll | name | Marks |
+------+------+-------+
|    1 | ABC  |    70 |
+------+------+-------+
1 row in set (0.001 sec)

MariaDB [31380_db]> SELECT Name, Roll FROM student where Roll=2&&Name='DEF';
+------+------+
| Name | Roll |
+------+------+
| DEF  |    2 |
+------+------+
1 row in set (0.001 sec)

MariaDB [31380_db]> SELECT Name, Roll FROM student where Roll=5&&Name='MNO';
+------+------+
| Name | Roll |
+------+------+
| MNO  |    5 |
| MNO  |    5 |
+------+------+
2 rows in set (0.001 sec)
```
---
