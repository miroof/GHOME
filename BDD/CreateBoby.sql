grant usage on *.* to 'boby'@'localhost';
drop user 'boby'@'localhost';
create user 'boby'@'localhost' identified by 'ghome';
grant select, alter, insert, update, delete, create, drop on GHOME.* to 'boby'@'localhost';m
