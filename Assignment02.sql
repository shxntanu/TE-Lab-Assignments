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

INSERT INTO dept VALUES
	(1, "Computer", "Pune"),
	(2, "IT", "Kolhapur"),
	(3, "ENTC", "Mumbai")
;

INSERT INTO employee VALUES 
	(53,2,'voluptas','adipisci','qui',436894,'2004-12-03'),
	(130,2,'distinctio','labore','ducimus',233644,'2016-06-21'),
	(77,1,'vitae','quasi','quia',493742,'1991-10-20'),
	(81,3,'soluta','non','sed',695828,'1993-02-08'),
	(87,3,'est','dolores','accusamus',400252,'1995-09-01'),
	(61,3,'vero','assumenda','voluptates',188762,'2010-08-25'),
	(32,2,'illum','ut','amet',828665,'1985-01-10'),
	(138,3,'nesciunt','quos','aut',648156,'1979-08-27'),
	(144,3,'earum','qui','maxime',657188,'1983-07-01'),
	(13,1,'dolores','sit','nemo',296957,'2022-04-23'),
	(27,2,'expedita','quam','et',467684,'1987-09-09'),
	(116,1,'cum','aut','beatae',935748,'1980-03-29'),
	(102,3,'autem','placeat','eos',747086,'2010-06-26'),
	(2,3,'laudantium','iste','sit',904317,'2006-03-03'),
	(1,2,'inventore','quis','fugit',950738,'2006-02-21'),
	(41,1,'modi','sint','voluptatem',947192,'1984-04-11'),
	(47,1,'placeat','aut','corporis',360642,'2016-09-30'),
	(123,1,'consequatur','impedit','officia',805100,'1971-11-26'),
	(65,3,'qui','ut','consequatur',539625,'2018-10-14'),
	(145,3,'tenetur','velit','voluptatibus',488586,'2005-03-01'),
	(60,1,'voluptatibus','eaque','quas',268439,'1984-07-17'),
	(100,3,'nihil','atque','et',762354,'1981-06-26'),
	(136,3,'labore','qui','est',524763,'2000-11-30'),
	(127,3,'quo','iusto','ut',804839,'2001-09-27'),
	(64,3,'voluptatem','dolorum','quos',369025,'2005-09-24')
;

INSERT INTO project VALUES 
	(19425,3,'a','Sydniborough',4781828,1988),
	(46820,2,'ea','North Oralchester',8720384,2000),
	(20534,2,'tenetur','Faheytown',2499445,2001),
	(18716,1,'veritatis','Morarhaven',5600366,1974),
	(27422,3,'reiciendis','West Amber',6150142,2012),
	(18617,2,'dolores','New Leannastad',7298848,2017),
	(41545,1,'quia','Starkmouth',2614732,1985),
	(13874,3,'est','Maraview',7153335,2002),
	(31164,1,'rerum','Lake Darylbury',2075820,1982),
	(18597,1,'ullam','Garrickberg',5537116,1971),
	(43491,3,'aspernatur','Hermistonstad',1819411,2021),
	(31940,2,'suscipit','North Robynfurt',4336490,2022),
	(35719,1,'alias','North Nikitaberg',6851360,1978),
	(23950,2,'quis','Lake Jammie',1905239,1996),
	(25632,3,'sint','West Rodolfoport',7924719,1979)
;

/*	
 SELECT * from employee;
 SELECT * from project;
*/

CREATE VIEW BasicDeets AS
SELECT emp_id, emp_jdate, emp_position
FROM employee;
