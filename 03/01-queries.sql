USE 31380_db;

-- Find Employee details and Department details using NATURAL JOIN.

SELECT emp.emp_id AS "Employee ID",
	emp.emp_fname AS "Name",
	emp.emp_lname AS "Surname",
	emp.emp_position AS "Position",
	dep.dept_name AS "Department",
	dep.dept_loc AS "Dept. Location",
	emp.emp_salary AS "Salary",
	emp.emp_jdate AS "Joining Date"
FROM employee AS emp
NATURAL JOIN dept AS dep
;


-- Find the emp_fname,Emp_position,location, Emp_JoinDate who have same Dept id.

SELECT emp.emp_fname AS "Name",
	emp.emp_position AS "Position",
	dep.dept_loc AS "Location",
	emp.emp_jdate AS "Joining Date",
	dep.dept_name AS "Department"
	FROM employee as emp
LEFT JOIN dept as dep
ON emp.dept_id = dep.dept_id
;


-- Find the Employee details ,Proj_id,Project cost who does not have Project location as ‘Hyderabad’.

SELECT DISTINCT
    e.emp_id, 
	e.emp_fname,
	e.emp_lname,
	e.emp_position,
	e.emp_salary,
	e.emp_jdate,
    p.proj_id, 
    p.proj_cost
FROM 
    employee e
INNER JOIN 
    project p ON e.dept_id = p.dept_id
WHERE 
    p.proj_location <> 'Hyderabad';


-- Find Department Name ,employee name, Emp_position for which project year is 2020

SELECT
	edj.dept_name AS "Dept. Name",
	edj.emp_fname AS "Employee Name",
	edj.emp_position AS "Position"
FROM (
	SELECT 
		employee.dept_id,
		employee.emp_fname,
		employee.emp_position,
		dept.dept_name
	FROM employee
	LEFT JOIN dept
	ON 
		employee.dept_id = dept.dept_id
) AS edj
RIGHT JOIN project AS pr
ON 
	edj.dept_id = pr.dept_id
WHERE
	pr.proj_year = 2020
; 

-- OR

SELECT dept_name, emp_fname, emp_position FROM 
employee LEFT JOIN dept USING (dept_id) RIGHT JOIN project USING (dept_id) 
WHERE proj_year = 2005
ORDER BY emp_id ASC;


-- Display emp_position, dept_name who have Project cost >30000

SELECT 
	edj.emp_position AS "Position",
	edj.dept_name AS "Dept. Name"
FROM (
	SELECT *
	FROM employee
	NATURAL JOIN dept
	WHERE employee.dept_id = dept.dept_id
) AS edj
RIGHT JOIN project AS pr
ON 
	edj.dept_id = pr.dept_id
WHERE 
	pr.proj_cost > 30000
;


-- Find the names of all the Projects that started in the year 2015.

SELECT 
	pr.proj_name AS "Project Name"
FROM
	project AS pr
WHERE 
	pr.proj_year = 2015
;

-- List the Dept_name having no_of_emp =  10

SELECT 
	edj1.dept_name
FROM (
	SELECT
		COUNT(EDJ.emp_id) AS "CNT", EDJ.dept_name
	FROM (
		SELECT 
			dept.dept_id,
			dept.dept_name,
			employee.emp_id
		FROM dept
		LEFT JOIN employee
		ON 
			dept.dept_id = employee.dept_id
		) as EDJ
	GROUP BY EDJ.dept_id
	) AS edj1
WHERE CNT = 10;


-- Display the total number of employee who have joined any project before 2009
-- (Used complex view)

CREATE VIEW edv AS
	SELECT d.dept_id, e.emp_fname, p.proj_name, p.proj_year
	FROM employee AS e, dept AS d, project AS p
	WHERE d.dept_id = e.dept_id = p.dept_id
	ORDER BY dept_id
;

SELECT DISTINCT emp_fname 
FROM edv 
WHERE proj_year < 2009
;

-- Create a view showing employee and dept details

CREATE VIEW ed_deets AS
	SELECT 
		e.dept_id,
		e.emp_fname,
		e.emp_lname,
		e.emp_position,
		e.emp_salary,
		e.emp_jdate,
		d.dept_name,
		d.dept_loc
	FROM
		employee AS e,
		dept AS d
	WHERE
		e.dept_id = d.dept_id
	ORDER BY
		dept_id
;

SELECT * FROM ed_deets;

-- Perform manipulation on simple view - insert, update, delete, drop

ALTER TABLE employee
MODIFY emp_id INT PRIMARY KEY NOT NULL AUTO_INCREMENT,
MODIFY dept_id INT DEFAULT 1,
MODIFY emp_fname VARCHAR(20) DEFAULT NULL,
MODIFY emp_lname VARCHAR(20) DEFAULT NULL,
MODIFY emp_position VARCHAR(50) DEFAULT NULL,
MODIFY emp_salary INT DEFAULT NULL,
MODIFY emp_jdate DATE DEFAULT NULL
;

CREATE VIEW sv AS
	SELECT
		emp_fname,
		emp_lname,
		emp_position
	FROM
		employee
	ORDER BY 
		dept_id
;

SELECT * FROM sv;

INSERT INTO
	sv
VALUES
	("Shantanu", "Wable", "CTO"),
	("Riya", "Wani", "CFO"),
	("Atharva", "Zodpe", "GM")
;

DELETE FROM sv
WHERE emp_fname = 'dolores';

UPDATE sv
SET emp_lname = 'UPDATE'
WHERE emp_fname = 'vero'
;
