USE 31380_db;

CREATE TABLE borrower (
	pk_br_id INT PRIMARY KEY NOT NULL AUTO_INCREMENT,
	br_name VARCHAR(50) DEFAULT NULL,
	issuedate DATE DEFAULT NULL,
	bk_name VARCHAR(50) DEFAULT NULL,
	status BOOL DEFAULT NULL
);

CREATE TABLE fine (
	pk_f_id INT PRIMARY KEY NOT NULL AUTO_INCREMENT,
	fk_br_id INT DEFAULT NULL,
	finedate DATE DEFAULT NULL,
	amount INT DEFAULT NULL,
	FOREIGN KEY (fk_br_id) REFERENCES borrower(pk_br_id) ON DELETE CASCADE
);

INSERT INTO borrower VALUES 
	(1,'deleniti','2012-07-03','enim',0),
	(2,'harum','1998-02-27','magnam',1),
	(3,'velit','1993-10-19','minus',0),
	(4,'ullam','2002-09-10','incidunt',0),
	(5,'totam','1992-01-23','tempora',0),
	(6,'eos','2023-03-03','dolor',0),
	(7,'ut','1979-10-08','nostrum',1),
	(8,'debitis','1981-08-09','quae',0),
	(9,'harum','2014-11-25','voluptate',1),
	(10,'doloremque','1988-11-30','quo',1)
;
