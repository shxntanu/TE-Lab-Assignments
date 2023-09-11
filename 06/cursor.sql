USE 31380_db;

DELIMITER $$
CREATE PROCEDURE mergeEMP () 
BEGIN
	DECLARE done INT DEFAULT 0;
	DECLARE eno INT;
	DECLARE old_cursor CURSOR FOR SELECT emp_id FROM O_EmpID;
	DECLARE CONTINUE HANDLER FOR NOT FOUND SET done = TRUE;
	OPEN old_cursor;
	
	getEmpID: LOOP
		IF done = TRUE THEN
			LEAVE getEmpID;
		END IF;
		FETCH old_cursor INTO eno;
		
		IF NOT EXISTS (SELECT 1 FROM N_EmpID where emp_id = eno) THEN 
			INSERT INTO N_EmpID 
			SELECT * FROM O_EmpID
			WHERE O_EmpID.emp_id = eno;
		END IF;
	END LOOP;
	
	CLOSE old_cursor;
END $$
DELIMITER ;
		
CALL mergeEMP();
