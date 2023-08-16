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
	fk_br_id INT,
	finedate DATE,
	amount INT,
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

DELIMITER $$
CREATE PROCEDURE library (IN r_no INT, IN bk VARCHAR(50), IN dt DATE)
BEGIN
	DECLARE fine INT;
	DECLARE dt2 INT;
	DECLARE EXIT HANDLER FOR 1452 SELECT 'Primary Key not Found' ErrorMessage;
	-- 1452 is the error code for "ERROR 1452 (23000): Cannot add or update a child row: a foreign key constraint fails"
	
	SELECT @idt := issuedate 
		FROM borrower 
		WHERE (pk_br_id = r_no AND bk_name = bk);
	SELECT @stt := status 
		FROM borrower 
		WHERE (pk_br_id = r_no AND bk_name = bk);
	SET dt2 := DATEDIFF(dt, @idt);
	IF @stt = False THEN
		IF dt2 BETWEEN 0 AND 14 THEN
			SET fine := 0;
		ELSEIF dt2 BETWEEN 15 AND 30 THEN
			SET fine := 5 * dt2;
		ELSE
			SET fine := 50 * dt2;
		END IF;
		INSERT INTO fine (fk_br_id, finedate, amount) VALUES (r_no, dt, fine);
		UPDATE borrower 
			SET status = True
			WHERE (pk_br_id = r_no AND bk_name = bk);
	END IF;
END $$
DELIMITER ;
