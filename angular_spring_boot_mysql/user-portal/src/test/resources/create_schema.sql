create table user(
--id int not null,
id int not null auto_increment,
first_name varchar(64),
last_name varchar(64),
email varchar(64),
last_modif timestamp,
primary key(id));