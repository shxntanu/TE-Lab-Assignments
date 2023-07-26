USE 31380_db;

ALTER TABLE employee DROP PRIMARY KEY;

ALTER TABLE employee
   	ADD CONSTRAINT `empk`
	PRIMARY KEY (emp_id)
;

ALTER TABLE employee MODIFY emp_id INT UNSIGNED NOT NULL AUTO_INCREMENT;

// DESCRIBE employee;

INSERT INTO employee (dept_id, emp_fname, emp_lname, emp_position, emp_salary, emp_jdate) VALUES
	(1, "Shantanu", "Wable", "CEO", 500000, "2003-04-20")
	(2, "Riya", "Wani", "Asst. Manager", 450000, "2005-05-07")
	(3, "Atharva", "Zodpe", "CTO", "480000, "2004-11-04")
;
	
SELECT * FROM employee;
