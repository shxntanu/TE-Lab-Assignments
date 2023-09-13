USE 31380_db;

CREATE TABLE Library (
	book_id INT UNIQUE PRIMARY KEY NOT NULL AUTO_INCREMENT,
	book_name VARCHAR(100) DEFAULT '',
	isbn INT UNIQUE NOT NULL,
	page_count INT,
	author VARCHAR(100),
	year DATE,
	copies_sold INT
);
	
CREATE TABLE Library_Audit (
	update_id INT UNIQUE PRIMARY KEY NOT NULL AUTO_INCREMENT,
	book_id INT,
	old_book_name VARCHAR(100) DEFAULT '',
	old_isbn INT UNIQUE NOT NULL,
	old_page_count INT,
	old_author VARCHAR(100),
	old_year DATE,
	old_copies_sold INT
);
	
	
