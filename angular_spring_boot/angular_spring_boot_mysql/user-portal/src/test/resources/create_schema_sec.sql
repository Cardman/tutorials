create table user(
id IDENTITY NOT NULL PRIMARY KEY,
first_name varchar(64),
last_name varchar(64),
last_modif timestamp default CURRENT_TIMESTAMP,
email varchar(64));