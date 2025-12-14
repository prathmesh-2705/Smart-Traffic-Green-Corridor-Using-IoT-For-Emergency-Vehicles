CREATE DATABASE IF NOT EXISTS smart_traffic;
USE smart_traffic;

-- Table to store live GPS logs from the ambulance
CREATE TABLE IF NOT EXISTS gps_data (
    id INT AUTO_INCREMENT PRIMARY KEY,
    device_id VARCHAR(10) NOT NULL,
    latitude DOUBLE NOT NULL,
    longitude DOUBLE NOT NULL,
    speed DOUBLE DEFAULT 0.0,
    timestamp TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);

-- Table to store fixed locations of traffic lights
CREATE TABLE IF NOT EXISTS static_device (
    device_id VARCHAR(10) PRIMARY KEY,
    location_name VARCHAR(50),
    latitude DOUBLE NOT NULL,
    longitude DOUBLE NOT NULL
);

-- Insert Default Location (St. Vincent Pallotti College)
INSERT INTO static_device (device_id, location_name, latitude, longitude) 
VALUES ('TL_01', 'College_Gate', 21.096076, 79.054276)
ON DUPLICATE KEY UPDATE latitude=VALUES(latitude);
