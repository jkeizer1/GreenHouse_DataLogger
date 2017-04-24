# GreenHouse_DataLogger
Arduino based temperature logging and graphing for Greenhouses.  The Arduino uses an Ethernet shield for connectivity.
Includes:
1. Arduino .ino source which i) provides a simple web server site to report current the sensor temperature, ii) periodically logs data to a remote web server (passing the sensor data in the URI parameters).
2. A PHP data logger URI on a remote web server to receive the data from the Arduino periodically and append it as a new XML record in a data file (datalog.txt)
3. HTML and JavaScript files which present the current temperature, and a line graph of all readings to date
Please see jknotes.com for additional information (Arduino blog)
