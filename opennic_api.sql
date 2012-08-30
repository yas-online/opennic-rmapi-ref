CREATE TABLE oz_domains (
domain VARCHAR(64) PRIMARY KEY,
name VARCHAR(20) NOT NULL,
email VARCHAR(50) NOT NULL,
ns1 VARCHAR(30) NOT NULL,
ns2 VARCHAR(30) NOT NULL,
ns1_ip VARCHAR(16),
ns2_ip VARCHAR(16),
registered DATE NOT NULL,
expires DATE,
updated DATE NOT NULL,
userid INT NOT NULL);

create table users (
userid INTEGER PRIMARY KEY,
username VARCHAR(20) NOT NULL,
password VARHCAR(32) NOT NULL,
name VARCHAR(50) NOT NULL,
email VARCHAR(50) NOT NULL,
country VARCHAR(2),
registered DATE NOT NULL,
verified INT NOT NULL);

create table registrars (
r_userid INTEGER PRIMARY KEY,
r_user VARCHAR(10) NOT NULL,
r_userkey VARCHAR(16) NOT NULL,
r_name VARCHAR(20) NOT NULL,
r_contact VARCHAR(20) NOT NULL,
r_email VARCHAR(50) NOT NULL,
r_url VARCHAR(50) NOT NULL);

INSERT INTO registrars (r_user, r_userkey, r_name, r_contact, r_email, r_url) VALUES('OZTLD', '1234567890abcdef', 'TLD Manager', 'Martin C', 'hostmaster@opennic.oz', 'http://opennic.oz');
INSERT INTO oz_domains(domain, name, email, ns1, ns2, registered, updated, userid) VALUES('opennic', 'Martin C', 'martin@opennic.oz', 'ns1.opennic.oz', 'ns2.opennic.oz', '2012-08-30', '2012-08-30', 0);
