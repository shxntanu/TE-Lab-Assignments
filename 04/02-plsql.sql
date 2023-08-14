USE 31380_db;

CREATE TABLE area (
	id INT PRIMARY KEY NOT NULL AUTO_INCREMENT,
	radius INT,
	area FLOAT
);

DELIMITER $$
CREATE PROCEDURE area_proc (IN rad INT)
BEGIN
	DECLARE a FLOAT DEFAULT 0.0;
	SET a = 3.14 * rad * rad;
	INSERT INTO area (radius, area) VALUES (rad, a);
END $$
DELIMITER ;
	
-- Calling the procedure 

CALL area_proc(5);

-- Viewing inserted data

SELECT * FROM area;

/*
+----+--------+------+
| id | radius | area |
+----+--------+------+
|  1 |      5 | 78.5 |
+----+--------+------+
*/

-- Modified Procedure

DELIMITER $$
CREATE PROCEDURE mod_area (IN rad INT)
BEGIN
	DECLARE a FLOAT DEFAULT 0.0;
	WHILE rad <= 9 DO
		SET a = 3.14 * rad * rad;
		INSERT INTO area (radius, area) VALUES (rad, a);
		SET rad = rad + 1;
	END WHILE;
END $$
DELIMITER ;

-- Calling modified procedure

CALL mod_area (2);

-- Viewing inserted data

SELECT * FROM area;

/*
+----+--------+--------+
| id | radius | area   |
+----+--------+--------+
|  1 |      5 |   78.5 |
|  2 |      2 |  12.56 |
|  3 |      3 |  28.26 |
|  4 |      4 |  50.24 |
|  5 |      5 |   78.5 |
|  6 |      6 | 113.04 |
|  7 |      7 | 153.86 |
|  8 |      8 | 200.96 |
|  9 |      9 | 254.34 |
+----+--------+--------+
*/
