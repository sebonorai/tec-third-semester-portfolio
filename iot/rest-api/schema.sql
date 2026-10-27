-- Esquema minimo deducido de las consultas de index.js (INSERT/SELECT sobre SensorData).
CREATE DATABASE IF NOT EXISTS iot_data;
USE iot_data;

CREATE TABLE IF NOT EXISTS SensorData (
    id       INT AUTO_INCREMENT PRIMARY KEY,
    reading  VARCHAR(50) NOT NULL,
    reg_date TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);
