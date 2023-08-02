USE 31380_db;

SELECT * FROM dept;
SELECT * FROM project;
SELECT * FROM employee;

INSERT INTO employee VALUES 
	(19,1,'sunt','et','Operations Manager',500406,'2020-09-02'),
	(54,3,'omnis','quidem','exercitationem',241123,'2013-02-24'),
	(78,2,'velit','ab','Operations Analyst',394047,'1985-11-16'),
	(80,1,'accusamus','qui','Operations Manager',622295,'2012-08-28'),
	(84,1,'et','ad','Auditor',801070,'2020-05-01'),
	(121,3,'architecto','qui','Auditor',803625,'2018-08-15'),
	(124,3,'dolorum','non','Financial Analyst',913504,'1977-12-26'),
	(129,1,'aspernatur','magni','Credit Authorizer',864120,'1985-12-08'),
	(132,2,'quia','tempora','Continuous Improvement Lead',751516,'2022-02-18'),
	(144,2,'aut','eveniet','Continuous Improvement Consultant',664481,'1986-01-11')
;

INSERT INTO project VALUES 
	(11,1,'voluptatum','New Karen',2212462,2003),
	(17,1,'odio','New Samantha',3031102,1997),
	(43,3,'debitis','East Marjoryfort',2621647,2003),
	(46,2,'beatae','New Abdiel',4670329,2019),
	(47,2,'explicabo','South Gladys',4373152,1991),
	(108,3,'sunt','Kreigerville',1252457,1991),
	(115,3,'maiores','West Ike',2387308,1983),
	(141,1,'quis','Kariside',2332175,2005),
	(143,2,'rerum','East Reinhold',1199693,2015),
	(150,1,'est','Reingerstad',3076611,1972)
;

SELECT * FROM employee 
WHERE (dept_id IN (SELECT dept_id FROM dept WHERE (dept_name='Computer' OR dept_name='IT'))) 
AND (emp_fname LIKE 'p%' OR emp_fname LIKE 'h%'); 

SELECT emp_position FROM employee GROUP BY emp_position HAVING COUNT(emp_position) = 1;

UPDATE employee
SET emp_salary = emp_salary*1.1
WHERE emp_jdate < '1985-01-01';

DELETE FROM dept WHERE dept_loc = 'Mumbai';

SELECT proj_name FROM project WHERE proj_location = 'Pune';

SELECT * FROM project WHERE proj_cost BETWEEN 1000000 AND 5000000;

SELECT proj_name, MAX(proj_cost) AS "Maximum Cost", AVG(proj_cost) AS "Average Project Cost"
FROM project;

SELECT emp_id, emp_fname, emp_lname 
FROM employee 
ORDER BY emp_lname DESC;

SELECT proj_name AS "Name", proj_location AS "Location", proj_cost AS "Cost" 
FROM project
WHERE proj_year = 2004 OR proj_year = 2005 OR proj_year = 2007;
