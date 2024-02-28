CREATE DATABASE school;

USE school;

CREATE TABLE students_info (
    stud_id INT PRIMARY KEY AUTO_INCREMENT,
    stud_name VARCHAR(50),
    class VARCHAR(10),
    division VARCHAR(10),
    city VARCHAR(50)
);

INSERT INTO students_info (stud_name, class, division, city) VALUES
('John Doe', '10', 'A', 'New York'),
('Jane Smith', '9', 'B', 'Los Angeles'),
('Alice Johnson', '11', 'C', 'Chicago');
