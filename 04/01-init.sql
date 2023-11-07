USE 31380_db;

CREATE TABLE borrower (
    roll_no INT,
    name VARCHAR(50),
    doi DATE,
    book_name VARCHAR(50),
    status VARCHAR(1) DEFAULT 'I'
);

CREATE TABLE fine (
    roll_no INT,
    date DATE,
    amt INT
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
CREATE PROCEDURE library (IN roll INT, IN book VARCHAR(50), IN dt DATE)
BEGIN 
    DECLARE fine INT;
    DECLARE dt2 INT;
    DECLARE EXIT HANDLER FOR 1452 SELECT 'Primary Key Not Found' ErrorMessage;
    
    SELECT @idt := doi
        FROM borrower 
        WHERE (roll_no = roll AND book_name = book);
        
    SELECT @stt := status
        FROM borrower
        WHERE (roll_no = roll AND book_name = book);
        
    SET dt2 := DATEDIFF(dt, @idt);
        
    IF @stt = False THEN
        IF dt2 BETWEEN 0 and 14 THEN
            SET fine := 0;
    
        ELSEIF dt2 BETWEEN 15 AND 30 THEN
            SET fine := dt2 * 5;
            
        ELSE 
        	SET fine := dt2 * 50;
        END IF;
        
        INSERT INTO fine VALUES (roll, dt, fine);
        
        UPDATE borrower 
        	SET status = True
        	WHERE (roll_no = roll AND book_name = book);
        	
   	 ELSE 
   	 	SELECT "Book has already been returned" AS Message;
   	 END IF;
   	 
END $$
DELIMITER ;


call library(5, "tempora", '2000-03-20');
