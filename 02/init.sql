/*
Author: Shantanu Wable

Assignment 2: SQL Queries

a. Design and Develop SQLDDL statements which demonstrate the use of SQL objects such as Table, View, Index, Sequence, Synonym, different constraints etc. 
b. Write at least 10 SQL queries on the suitable database application using SQL DML statements.
*/


USE 31380_db;

DROP TABLE dept;
DROP TABLE project;
DROP TABLE employee;
DROP VIEW BasicDeets;

CREATE TABLE dept (
	dept_id INT,
	dept_name VARCHAR(50),
	dept_loc VARCHAR(50),
	PRIMARY KEY(dept_id)
);

CREATE TABLE project (
	proj_id INT,
	dept_id INT, 
	proj_name VARCHAR(50),
	proj_location VARCHAR(50),
	proj_cost INT,
	proj_year INT,
	PRIMARY KEY (proj_id),
	FOREIGN KEY (dept_id) REFERENCES dept(dept_id) ON DELETE CASCADE
);

CREATE TABLE employee ( 
	emp_id INT,
	dept_id INT,
	emp_fname VARCHAR(20),
	emp_lname VARCHAR(20),
	emp_position VARCHAR(20),
	emp_salary INT,
	emp_jdate DATE,
	PRIMARY KEY (emp_id)
);

DESCRIBE employee;

ALTER TABLE employee 
	ADD CONSTRAINT `emfk_1` 	
	FOREIGN KEY (dept_id) 
	REFERENCES dept(dept_id) 
	ON DELETE CASCADE
;

DESCRIBE employee;
