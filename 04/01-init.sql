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
