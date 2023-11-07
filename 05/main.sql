USE 31380_db;

CREATE TABLE stud_marks(
	name VARCHAR(50),
	total_marks INT
);

CREATE TABLE result (
	roll INT PRIMARY KEY NOT NULL AUTO_INCREMENT,
	class VARCHAR(25) DEFAULT NULL,
	name VARCHAR(50)
);

INSERT INTO stud_marks VALUES 
	('aliquid',756),
	('et',1253),
	('ab',755),
	('hic',1285),
	('sunt',877),
	('suscipit',696),
	('eos',1404),
	('necessitatibus',873),
	('praesentium',1353),
	('et',1154),
	('officia',619),
	('asperiores',871),
	('illum',808),
	('quis',1108),
	('incidunt',1306),
	('nemo',1595),
	('et',705),
	('soluta',783),
	('ratione',821),
	('ut',753)
;

DELIMITER $$
CREATE PROCEDURE proc_grade (IN studmarks INT, IN name VARCHAR(50), IN roll INT)
BEGIN
	DECLARE clss VARCHAR(25);
	IF studmarks BETWEEN 990 AND 1500 THEN
		SET clss := 'Distinction';
	ELSEIF studmarks BETWEEN 900 AND 989 THEN
		SET clss := 'First Class';
	ELSEIF studmarks BETWEEN 825 AND 899 THEN
		SET clss := 'Higher Second Class';
	ELSE
		SET clss := 'Pass';
	END IF;
	INSERT INTO result VALUES (roll, clss, name);
END $$
DELIMITER ;

CALL proc_grade(900, 'Shantanu', 31380);
CALL proc_grade(1000, 'Riya', 31381);
CALL proc_grade(1490, 'Atharva', 31382);
CALL proc_grade(799, 'Durvesh', 31379);
CALL proc_grade(750, 'Rhea', 31364);
CALL proc_grade(869, 'Ridhima', 31372);
CALL proc_grade(500, 'Piyush', 31466);
CALL proc_grade(1005, 'Riddhi', 31470);

SELECT * FROM result;

/*
+-------+-------------+----------+
| roll  | class       | name     |
+-------+-------------+----------+
| 31364 | Pass        | Rhea     |
| 31379 | Pass        | Durvesh  |
| 31380 | First Class | Shantanu |
| 31381 | Distinction | Riya     |
| 31382 | Distinction | Atharva  |
| 31466 | Pass        | Piyush   |
| 31470 | Distinction | Riddhi   |
+-------+-------------+----------+
7 rows in set (0.001 sec)
*/
