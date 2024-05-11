CREATE DATABASE IF NOT EXISTS DNS;

USE DNS;

CREATE TABLE IF NOT EXISTS data (
    indirizzo_ip VARCHAR(15) NOT NULL,
    hostname VARCHAR(255) NOT NULL,
    type VARCHAR(50) NOT NULL, 
    PRIMARY KEY (indirizzo_ip)
);

INSERT INTO data (indirizzo_ip, hostname, type) VALUES
    ('192.168.1.1', 'host1.example.com', 'A'),
    ('192.168.1.2', 'host2.example.com', 'A'),
    ('192.168.1.3', 'host3.example.com', 'A'),
    ('192.168.1.4', 'host4.example.com', 'A'),
    ('192.168.1.5', 'host5.example.com', 'A'),
    ('192.168.1.6', 'host6.example.com', 'A'),
    ('192.168.1.7', 'host7.example.com', 'A'),
    ('192.168.1.8', 'host8.example.com', 'A'),
    ('192.168.1.9', 'host9.example.com', 'A'),
    ('192.168.1.10', 'host10.example.com', 'A');
