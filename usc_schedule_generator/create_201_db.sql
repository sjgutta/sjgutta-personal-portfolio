DROP DATABASE IF EXISTS schedget;
CREATE DATABASE schedget;

USE schedget;
CREATE TABLE users (
	user_id INT(11) PRIMARY KEY AUTO_INCREMENT,
    username VARCHAR(20) NOT NULL,
    email VARCHAR(50) NOT NULL,
    password CHAR(64) NOT NULL
);

CREATE TABLE study_rooms (
	room_id INT(11) PRIMARY KEY AUTO_INCREMENT,
    name VARCHAR(20) NOT NULL,
    description VARCHAR(240) NOT NULL
);

CREATE TABLE courses (
    course_id INT(11) PRIMARY KEY AUTO_INCREMENT,
    prefix VARCHAR(5) NOT NULL,
    code VARCHAR(7) NOT NULL,
    professor_name VARCHAR(64) NOT NULL,
    classroom VARCHAR(10) NOT NULL,
    days VARCHAR(20) NOT NULL,
    start_time TIME NOT NULL,
    end_time TIME NOT NULL,
    course_type VARCHAR(20) NOT NULL
);

CREATE TABLE reservations (
	reservation_id INT(11) PRIMARY KEY AUTO_INCREMENT,
    user INT(11) NOT NULL,
    study_room INT(11) NOT NULL,
    start_time TIME NOT NULL,
    end_time TIME NOT NULL,
    reservation_date DATE NOT NULL,
    FOREIGN KEY fk1(user) REFERENCES users(user_id),
    FOREIGN KEY fk2(study_room) REFERENCES study_rooms(room_id)
);

CREATE TABLE schedules (
    schedule_id INT(11) PRIMARY KEY AUTO_INCREMENT,
    user INT(11) NOT NULL,
    schedule_data JSON NOT NULL,
    FOREIGN KEY fk1(user) REFERENCES users(user_id)
);
