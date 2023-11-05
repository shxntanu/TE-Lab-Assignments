/*
Author: Shantanu Wable

Assignment 2: SQL Queries

a. Design and Develop SQL DDL statements which demonstrate the use of SQL objects such as Table, View, Index, Sequence, Synonym, different constraints etc. 
b. Write at least 10 SQL queries on the suitable database application using SQL DML statements.
*/

USE 31380_db;

CREATE TABLE dept (
	dept_id INT PRIMARY KEY,
	dept_name VARCHAR(50),
	dept_loc VARCHAR(50)
);

CREATE TABLE project (
	proj_id INT PRIMARY KEY,
	dept_id INT, 
	proj_name VARCHAR(50),
	proj_location VARCHAR(50),
	proj_cost INT,
	proj_year INT,
	FOREIGN KEY (dept_id) REFERENCES dept(dept_id) ON DELETE CASCADE
);

CREATE TABLE employee ( 
	emp_id INT PRIMARY KEY,
	dept_id INT,
	emp_fname VARCHAR(20),
	emp_lname VARCHAR(20),
	emp_position VARCHAR(50),
	emp_salary INT,
	emp_jdate DATE,
	FOREIGN KEY (dept_id) REFERENCES dept(dept_id) ON DELETE CASCADE
);