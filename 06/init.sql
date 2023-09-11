USE 31380_db;

CREATE TABLE N_EmpID ( 
	emp_id INT,
	dept_id INT,
	emp_fname VARCHAR(20),
	emp_lname VARCHAR(20),
	emp_position VARCHAR(50),
	emp_salary INT,
	emp_jdate DATE,
	PRIMARY KEY (emp_id)
);

CREATE TABLE O_EmpID ( 
	emp_id INT,
	dept_id INT,
	emp_fname VARCHAR(20),
	emp_lname VARCHAR(20),
	emp_position VARCHAR(50),
	emp_salary INT,
	emp_jdate DATE,
	PRIMARY KEY (emp_id)
);
