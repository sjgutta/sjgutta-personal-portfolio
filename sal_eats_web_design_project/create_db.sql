DROP DATABASE IF EXISTS sal_eats;
CREATE DATABASE sal_eats;

USE sal_eats;
CREATE TABLE users(
	user_id INT(11) PRIMARY KEY AUTO_INCREMENT,
	username VARCHAR(20) NOT NULL,
    email VARCHAR(50) NOT NULL,
    password CHAR(64) NOT NULL
);

CREATE TABLE favorites(
	favorite_id INT(11) PRIMARY KEY AUTO_INCREMENT,
    user INT(11) NOT NULL,
    yelp_id VARCHAR(25),
    FOREIGN KEY fk1(user) REFERENCES users(user_id)
);