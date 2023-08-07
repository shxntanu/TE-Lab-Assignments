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
	
