USE 31380_db;

CREATE TABLE area (
	id INT PRIMARY KEY NOT NULL AUTO_INCREMENT,
	radius INT,
	area FLOAT
);

DELIMITER $$
CREATE PROCEDURE area_proc (IN rad INT)
BEGIN
	DECLARE a FLOAT DEFAULT 0.0;s
	SET a = 3.14 * rad * rad;
	INSERT INTO area (radius, area) VALUES (rad, a);
END $$
DELIMITER ;
	
-- Calling the procedure 

CALL area_proc(5);

-- Viewing inserted data

SELECT * FROM area;
