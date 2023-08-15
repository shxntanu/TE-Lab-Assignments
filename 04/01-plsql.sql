USE 31380_db;

-- 	DECLARE exitHandler HANDLER FOR NOT FOUND dbms_output.put_line('No such entry!');

DELIMITER $$
CREATE PROCEDURE library (IN r_no INT, IN bk VARCHAR(50), IN dt DATE)
BEGIN
	DECLARE fine INT;
	DECLARE dt2 INT;
	
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
		INSERT INTO fine (fk_br_id, dt, amount) VALUES (r_no, dt, fine);
		UPDATE borrower 
			SET status = True
			WHERE (pk_br_id = r_no AND bk_name = bk);
	END IF;
END $$
DELIMITER ;

	
	
	
	
	
