USE 31380_db;

CREATE TABLE N_EmpID ( 
	emp_id INT,
	dept_id INT,
	emp_fname VARCHAR(20),
	emp_lname VARCHAR(20),
	emp_position VARCHAR(50),
	emp_salary INT,
	emp_jdate DATE,
	PRIMARY KEY (emp_id)
);

CREATE TABLE O_EmpID ( 
	emp_id INT,
	dept_id INT,
	emp_fname VARCHAR(20),
	emp_lname VARCHAR(20),
	emp_position VARCHAR(50),
	emp_salary INT,
	emp_jdate DATE,
	PRIMARY KEY (emp_id)
);

INSERT INTO O_EmpID VALUES 
	(19,2,'molestiae','nostrum','quisquam',850067,'1990-02-16'),
	(23,2,'aut','quis','harum',313554,'1976-09-16'),
	(32,2,'et','et','architecto',942122,'1972-03-16'),
	(33,3,'voluptatem','at','rerum',731520,'1990-06-28'),
	(34,2,'fugit','harum','omnis',477917,'1985-08-06'),
	(36,1,'provident','voluptatem','at',145306,'1995-07-06'),
	(55,3,'suscipit','et','et',481782,'2011-05-10'),
	(59,1,'ea','temporibus','qui',861072,'1988-07-26'),
	(60,3,'fuga','quia','placeat',393128,'1988-10-12'),
	(63,1,'voluptatem','nihil','reiciendis',856496,'1986-10-27'),
	(67,3,'amet','expedita','similique',720147,'2000-11-24'),
	(69,1,'dolore','magni','eius',414471,'1972-11-21'),
	(70,2,'quos','veritatis','ex',938067,'1997-04-13'),
	(81,2,'sequi','aut','voluptatibus',120184,'1987-12-17'),
	(84,3,'ipsum','sunt','nemo',446727,'1977-03-24'),
	(91,1,'tempore','qui','quia',338584,'1992-07-24'),
	(110,1,'consequatur','ipsam','est',576805,'2001-04-22'),
	(111,2,'eveniet','assumenda','rerum',526825,'2006-04-23'),
	(123,3,'optio','esse','est',730407,'1989-06-18'),
	(138,2,'nihil','rerum','eum',311204,'2009-03-02');


INSERT INTO N_EmpID VALUES 
	(19,2,'molestiae','nostrum','quisquam',850067,'1990-02-16'),
	(23,2,'aut','quis','harum',313554,'1976-09-16'),
	(32,2,'et','et','architecto',942122,'1972-03-16'),
	(33,3,'voluptatem','at','rerum',731520,'1990-06-28'),
	(34,2,'fugit','harum','omnis',477917,'1985-08-06'),
	(36,1,'provident','voluptatem','at',145306,'1995-07-06'),
	(55,3,'suscipit','et','et',481782,'2011-05-10'),
	(165,1,'molestiae','itaque','dolorem',948514,'1975-08-09'),
	(168,2,'id','et','ut',771819,'2003-08-17'),
	(172,1,'iure','omnis','ut',486159,'2006-09-16'),
	(173,1,'perferendis','omnis','veniam',845958,'1990-07-14'),
	(174,2,'alias','debitis','aut',679066,'2014-04-10'),
	(179,2,'doloremque','voluptate','voluptate',148700,'1989-03-13'),
	(184,1,'sed','error','reiciendis',993787,'1971-11-13'),
	(186,1,'voluptas','eum','et',940556,'1983-09-08'),
	(195,2,'nesciunt','non','autem',215182,'2011-04-22'),
	(198,1,'pariatur','autem','deserunt',974698,'1972-04-24');

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


DELIMITER $$
CREATE PROCEDURE mergeEMPwithinBounds (IN lb INT, IN ub INT) 
BEGIN
	DECLARE done INT DEFAULT 0;
	DECLARE eno INT;
	DECLARE old_cursor1 CURSOR FOR SELECT emp_id FROM O_EmpID WHERE emp_id BETWEEN lb AND ub;
	DECLARE CONTINUE HANDLER FOR NOT FOUND SET done = TRUE;
	OPEN old_cursor1;
	
	getEmpID: LOOP
		IF done = TRUE THEN
			LEAVE getEmpID;
		END IF;
		FETCH old_cursor1 INTO eno;
		
		IF NOT EXISTS (SELECT 1 FROM N_EmpID where emp_id = eno) THEN 
			INSERT INTO N_EmpID 
			SELECT * FROM O_EmpID
			WHERE O_EmpID.emp_id = eno;
		END IF;
	END LOOP;
	
	CLOSE old_cursor1;
END $$
DELIMITER ;
