# Database Management Systems Lab

## Getting Started
To start MySQL / MariaDB in terminal, enter:
```shell
mysql -h 10.10.14.125 -u te{your roll number} -p
```
Then enter the password.

## Table Creation Commands

<details>
<summary>USE</summary>

Uses the specified database.

`USE {db name}`
```
USE 31380_db
```
</details>

<details>
<summary>CREATE</summary>
    
Creates a table.

`CREATE TABLE {table name} (colname datatype, colname datatype, colname datatype);`
```
CREATE TABLE student (Roll INT, Name VARCHAR(150), Marks INT);
```
</details>

<details>
<summary>SHOW</summary>

Shows all tables present in the current database.
    
`SHOW TABLES;`
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
</details>

<details>
<summary>DESCRIBE</summary>

Shows all info related to the given table.
    
`DESCRIBE {table}`
```
DESCRIBE student;
```
Output:
```
+-------+--------------+------+-----+---------+-------+
| Field | Type         | Null | Key | Default | Extra |
+-------+--------------+------+-----+---------+-------+
| Roll  | int(11)      | YES  |     | NULL    |       |
| name  | varchar(150) | YES  |     | NULL    |       |
| Marks | int(11)      | YES  |     | NULL    |       |
+-------+--------------+------+-----+---------+-------+
3 rows in set (0.002 sec)
```
</details>

## Table Updation Commands

<details>
<summary>INSERT</summary>
    
`INSERT INTO {table} VALUES {records};`
```
INSERT INTO student values (01, 'ABC', 70);
INSERT INTO student values (02, 'DEF', 80), (03, 'GHI', 90);
```
</details>

<details>
<summary>SELECT</summary>

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
</details>

<details>
<summary>DELETE</summary>
    
`DELETE FROM {table name} WHERE {condition};` : Deletes a given record from the current table.
```
MariaDB [31380_db]> DELETE FROM student WHERE Roll=1;
Query OK, 1 row affected (0.042 sec)

MariaDB [31380_db]> SELECT * from student;
+------+------+-------+
| Roll | name | Marks |
+------+------+-------+
|    2 | DEF  |    80 |
|    3 | GHI  |    90 |
|    4 | JKL  |    65 |
|    5 | MNO  |    75 |
|    4 | JKL  |    65 |
|    5 | MNO  |    75 |
+------+------+-------+
6 rows in set (0.001 sec)

MariaDB [31380_db]> DELETE FROM student WHERE Roll=5;
Query OK, 2 rows affected (0.038 sec)

MariaDB [31380_db]> SELECT * from student;
+------+------+-------+
| Roll | name | Marks |
+------+------+-------+
|    2 | DEF  |    80 |
|    3 | GHI  |    90 |
|    4 | JKL  |    65 |
|    4 | JKL  |    65 |
+------+------+-------+
4 rows in set (0.001 sec)
```
</details>

<details>
<summary>DROP</summary>
    
`DROP TABLE {table name}` : Deletes the table and schema.
```
DROP TABLE student;
```
</details>

<details>
<summary>Update an entry (UPDATE)</summary>
    
`UPDATE {table name} 
SET column1 = value1, column2 = value2, ... 
WHERE {condition};`
```
UPDATE Customers
SET ContactName = 'Alfred Schmidt', City = 'Frankfurt'
WHERE CustomerID = 1;
```
</details>

## Updating the Schema (ALTER)

<details>
<summary>ADD</summary>
    
Add a new column to the DB.
```
ALTER TABLE table_name
    ADD new_column_name column_definition
    [FIRST | AFTER column_name],
    ADD new_column_name column_definition
    [FIRST | AFTER column_name],
    ...;
```
</details>

<details>
<summary>DROP</summary>
    
Delete a column from the schema.
```
ALTER TABLE table_name
    DROP COLUMN column_name;
```
</details>

<details>
<summary>MODIFY</summary>
    
Modify an existing column schema.
```
ALTER TABLE table_name
    MODIFY column_name column_definition
    [ FIRST | AFTER column_name],
    MODIFY column_name column_definition
    [ FIRST | AFTER column_name],
    ...;
```
</details>

<details>
<summary>RENAME</summary>
    
Rename an existing column.
```
ALTER TABLE table_name
    CHANGE COLUMN original_name new_name column_definition
    [FIRST | AFTER column_name];
```
</details>

<details>
    <summary>Add a column with default value</summary>

    ALTER TABLE table_name 
        ADD col_name data_type 
        DEFAULT def_value 
        [FIRST | AFTER column_name];
    
</details>

<details>
    <summary>Rename a table</summary>
    
    ALTER TABLE old_table_name RENAME new_table_name;
    
</details>
