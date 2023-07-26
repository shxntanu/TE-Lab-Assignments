USE 31380_db;

CREATE VIEW BasicDeets AS
   	SELECT emp_id, emp_jdate, emp_position
	FROM employee
;

SELECT * FROM BasicDeets;

INSERT INTO BasicDeets VALUES 
	(119, "2012-02-10", "Manager"),
	(120, "2013-04-20", "Vice Manager"),
	(121, "2010-03-17", "Peon")
;

SELECT * FROM employee;

// All columns that are not in the view get set default value as NULL
