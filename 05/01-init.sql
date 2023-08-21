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
