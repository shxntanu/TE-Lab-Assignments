USE 31380_db;

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

SELECT emp.emp_fname AS "Name",
	emp.emp_position AS "Position",
	dep.dept_loc AS "Location",
	emp.emp_jdate AS "Joining Date",
	dep.dept_name AS "Department"
	FROM employee AS emp
	NATURAL JOIN dept AS dep
	WHERE emp.dept_id = dep.dept_id
;

SELECT emp.emp_id AS "Employee ID",
	emp.emp_fname AS "Name",
	emp.emp_lname AS "Surname",
	emp.emp_position AS "Position",
	emp.emp_salary AS "Salary",
	emp.emp_jdate AS "Joining Date",
	pr.proj_id AS "Project ID",
	pr.proj_cost AS "Project Cost"
	FROM employee AS emp
	NATURAL JOIN project as pr
	WHERE (pr.proj_location != "Hyderabad") AND (emp.dept_id = pr.dept_id)
;
