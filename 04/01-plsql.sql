USE 31380_db;

CREATE TABLE borrower (
	pk_br_id INT PRIMARY KEY NOT NULL AUTO_INCREMENT,
	br_name VARCHAR(50),
	issuedate DATE,
	bk_name VARCHAR(50),
	status BOOL
);

CREATE TABLE fine (
	pk_f_id INT PRIMARY KEY NOT NULL AUTO_INCREMENT,
	fk_br_id INT,
	finedate DATE,
	amount INT,
	FOREIGN KEY (fk_br_id) REFERENCES borrower(pk_br_id) ON DELETE CASCADE
);

--ACCEPT roll INT PROMPT 'Enter Roll Number: ';
--ACCEPT book VARCHAR(50) PROMPT 'Enter book name: ';
--ACCEPT doi DATE PROMPT 'Enter date of issue (YYYY-MM-DD): ';
-- INSERT INTO fine (fk_br_id, dt, amount) VALUES (r_no, dt, fine);

DECLARE
	r_no borrower.pk_br_id%type;
	bk borrower.bk_name%type;
	dt borrower.issuedate%type;
	fine fine.amount%type;
	status fine.status%type;
	dt2 INT;
BEGIN
	r_no := :r_no;
	bk := :bk;
	dt := :dt;
	dt2 := DATEDIFF(dt, SELECT issuedate FROM borrower WHERE (pk_br_id = r_no AND bk_name = bk));
	status := SELECT status FROM borrower WHERE (pk_br_id = r_no AND bk_name = bk);
	IF status = False THEN
		IF dt2 BETWEEN 0 AND 14 THEN
			fine := 0;
		ELSEIF dt2 BETWEEN 15 AND 30 THEN
			fine := 5 * dt2;
		ELSEIF 
			fine := 50 * dt2;
		END IF;
		INSERT INTO fine (fk_br_id, dt, amount) VALUES (r_no, dt, fine);
		UPDATE borrower 
			SET status = True
			WHERE (pk_br_id = r_no AND bk_name = bk);
	END IF;
	EXCEPTION  
	   	WHEN no_data_found THEN  
			dbms_output.put_line('No such entry!');  
	   	WHEN others THEN  
		  	dbms_output.put_line('Error!');  
END;
/
