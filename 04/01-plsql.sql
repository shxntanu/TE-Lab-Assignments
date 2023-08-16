USE 31380_db;

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

	-- DATEDIFF is an inbuilt function which returns the number of days between two dates.
	SET dt2 := DATEDIFF(dt, @idt);

	-- If book has not been returned
	IF @stt = False THEN
		-- Set Fine
		IF dt2 BETWEEN 0 AND 14 THEN
			SET fine := 0;
		ELSEIF dt2 BETWEEN 15 AND 30 THEN
			SET fine := 5 * dt2;
		ELSE
			SET fine := 50 * dt2;
		END IF;

		-- Insert into the fine table
		INSERT INTO fine (fk_br_id, finedate, amount) VALUES (r_no, dt, fine);

		-- Update the status of the same in the borrower table
		UPDATE borrower 
			SET status = True
			WHERE (pk_br_id = r_no AND bk_name = bk);

	-- Else print status message
	ELSE 
		SELECT "Book has already been returned" AS Message;
	END IF;
END $$
DELIMITER ;
