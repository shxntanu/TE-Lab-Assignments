USE 31380_db;

DELIMITER $$
CREATE TRIGGER update_trig
	BEFORE UPDATE ON Library
	FOR EACH ROW
	BEGIN
	
	INSERT INTO Library_Audit (book_id, old_book_name, old_isbn, old_page_count, old_author, old_year,old_copies_sold) VALUES 
		(OLD.book_id, OLD.book_name, OLD.isbn, OLD.page_count, OLD.author, OLD.year, OLD.copies_sold);
	
END $$
DELIMITER ;

-- Testing the trigger

UPDATE Library
SET book_name = 'haha totam' WHERE book_id = 1;

DELIMITER $$
CREATE TRIGGER error_trig
BEFORE UPDATE ON Library
FOR EACH ROW
BEGIN
	IF NEW.book_name = OLD.book_name THEN
	SIGNAL SQLSTATE '45000'
	SET message_text = 'Same value of updated book';
	END IF;
END $$
DELIMITER ; 

UPDATE Library
SET book_name = 'quae' WHERE book_id = 3;
