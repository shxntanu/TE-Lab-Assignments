USE 31380_db;

SELECT * FROM dept;
SELECT * FROM project;
SELECT * FROM employee;

UPDATE employee
	SET emp_fname = "Yogi",
	emp_lname = "Adityanath",
	emp_position = "Neta"
	WHERE emp_id = 32
;

DELETE FROM employee WHERE emp_id = 53;
