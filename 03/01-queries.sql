USE 31380_db;

-- Natural Join
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

-- Left Outer Join
SELECT emp.emp_fname AS "Name",
	emp.emp_position AS "Position",
	dep.dept_loc AS "Location",
	emp.emp_jdate AS "Joining Date",
	dep.dept_name AS "Department"
	FROM employee as emp
LEFT JOIN dept as dep
ON emp.dept_id = dep.dept_id
;

-- Right Outer Join
SELECT
    emp.emp_id AS "Employee ID",
    emp.emp_fname AS "Name",
    emp.emp_lname AS "Surname",
    emp.emp_position AS "Position",
    emp.emp_salary AS "Salary",
    emp.emp_jdate AS "Joining Date",
    pr.proj_cost AS "Project Cost"
FROM employee AS emp
RIGHT JOIN project as pr
    ON (pr.proj_location != "Hyderabad") AND (emp.dept_id = pr.dept_id)
GROUP BY emp.emp_id;


SELECT
	dep.dept_name AS "Dept. Name",
	emp.emp_fname AS "Employee Name",
	emp.emp_position AS "Position"
FROM employee AS emp,
dept AS dep,
project AS pr
WHERE
	((dep.dept_id = emp.dept_id) AND
	(dep.dept_id = pr.dept_id)) AND
	pr.proj_year = 2020
; 

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
	
