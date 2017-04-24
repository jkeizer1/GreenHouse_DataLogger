/*
  Web Server

 A simple web server that shows the value of the analog input pins.
 using an Arduino Wiznet Ethernet shield.

 Circuit:
 * Ethernet shield attached to pins 10, 11, 12, 13
 * Analog inputs attached to pins A0 through A5 (optional)

 created 18 Dec 2009
 by David A. Mellis
 modified 9 Apr 2012
 by Tom Igoe
 modified 02 Sept 2015
 by Arturo Guadalupi
 modified: Jim Keizer, Juuly 2016. 

 */
//#define DEVELOP 1
//#define TEST_NOETHERNET 1


// DISABLE DHT #include "DHT.h"
/*
// DISABLE DHT #define DHTPIN 2     // what digital pin we're connected to
// Uncomment whatever type you're using!
//---> USE THIS ONE IF REENABLING LIBRARY #define DHTTYPE DHT11   // DHT 11
//#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
//#define DHTTYPE DHT21   // DHT 21 (AM2301)
// Connect pin 1 (on the left) of the sensor to +5V
// NOTE: If using a board with 3.3V logic like an Arduino Due connect pin 1
// to 3.3V instead of 5V!
// Connect pin 2 of the sensor to whatever your DHTPIN is
// Connect pin 4 (on the right) of the sensor to GROUND
// Connect a 10K resistor from pin 2 (data) to pin 1 (power) of the sensor
// Initialize DHT sensor.
// Note that older versions of this library took an optional third parameter to
// tweak the timings for faster processors.  This parameter is no longer needed
// as the current DHT reading algorithm adjusts itself to work on faster procs.
// DISABLE DHT DHT dht(DHTPIN, DHTTYPE);
*/


// DISABLE ANALOG
/*
#define A0 0
// #define beta 4090 // the beta of the thermistor
//#define beta 4090
// use this BETA - PRETTY ACCURATE #define beta 3700
*/

#include <SPI.h>
#include <Ethernet.h>
//#include <OneWire.h> 
#include <DallasTemperature.h>


// Data wire is plugged into port 2 on the Arduino
#define ONE_WIRE_BUS 3
// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);
// Pass our oneWire reference to Dallas Temperature. 
DallasTemperature sensors(&oneWire);


// Enter a MAC address and IP address for your controller below.
// The IP address will be dependent on your local network:
byte mac[] = {
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED
};
IPAddress ip(192, 168, 1, 177);
IPAddress ip_webserver(192, 168, 1, 207);

// Initialize the Ethernet server library
// with the IP address and port you want to use
// (port 80 is default for HTTP):
EthernetServer server(80);

unsigned long lastConnectionTime = 0; // last time posted to server
const unsigned long postingInterval = 600L * 1000L; // delay 30 seconds

void setup() {
  // Open serial communications and wait for port to open:
  
  #ifdef DEVELOP
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  #endif

// DISABLE ANALOG
/*
  pinMode(A0, INPUT);
*/

  // start the Ethernet connection and the server:
  Ethernet.begin(mac, ip);
  server.begin();

  #ifdef DEVELOP
  Serial.print("server is at ");
  Serial.println(Ethernet.localIP());
  Serial.println("Hello There");
  #endif

// DISABLE DHT
/*
  dht.begin();
*/

  sensors.begin(); // DS1B20
}


void loop() {

  bool skip = false;
  float fc; // temperature in celcius
  // listen for incoming clients
  EthernetClient client = server.available();
  if (client && !skip) {
    Serial.println("new client");
    // an http request ends with a blank line
    boolean currentLineIsBlank = true;
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();

        #ifdef DEVELOP
        Serial.write(c);
        #endif
     
        // if you've gotten to the end of the line (received a newline
        // character) and the line is blank, the http request has ended,
        // so you can send a reply
        if (c == '\n' && currentLineIsBlank) {
          // send a standard http response header
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("Connection: close");  // the connection will be closed after completion of the response
          client.println("Refresh: 5");  // refresh the page automatically every 5 sec
          client.println();
          client.println("<html>");

          client.println("<!DOCTYPE HTML>");
          client.println("<head>");
          client.println("<style>");
          client.println("h1 { font-size: 24pt; font-weight: bold; color: rgb(0,0,255) }");   
          client.println("h2 { font-size: 18pt; font-weight: bold; color: rgb(255,0,0) }"); 
          client.println("</style>");
          client.println("</head>"); 
 

          client.println("<h1 align=center><br>Hello From Heather's Greenhouse!</br><br/></h1>");
          client.print ("<h1 align=center>Solar Powered</h1><br />");

// DISABLE ANALOG 
/*
          int v_temperature = analogRead (A0);

          #ifdef DEVEOP
          Serial.print ("Temperature Voltage: ");
          Serial.println (v_temperature);
          #endif
          
          long a = 1023 - v_temperature;
          float tempC = beta / (log((1025.0 * 10 / a - 10) / 10) + beta / 298.0) - 273.0;
          client.print ("<h2 align=center>Analog Temperature Sensor1: ");
          client.print (tempC);
          client.print("C</h2>");
          client.println("<br />");

*/

// DISABLE DHT 
/*
          // Reading temperature or humidity takes about 250 milliseconds!
          // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
          float h = dht.readHumidity();
          // Read temperature as Celsius (the default)
          float t = dht.readTemperature();
          // Read temperature as Fahrenheit (isFahrenheit = true)
          float f = dht.readTemperature(true);
                      
          // Check if any reads failed and exit early (to try again).
          if (isnan(h) || isnan(t) || isnan(f)) {
            Serial.println("Failed to read from DHT sensor!");
            return;
          }
          else {
              //
              // Compute heat index in Fahrenheit (the default)
              float hif = dht.computeHeatIndex(f, h);
              //
              // Compute heat index in Celsius (isFahreheit = false)
              float hic = dht.computeHeatIndex(t, h, false);
             
              client.print ("<h2 align=center>DHT Temp. Sensor2: ");
              client.print (t);
              client.print("C</h2>");
              client.println("<br />"); 

              client.print("<h2 align=center>DHT Humidity: ");
              client.print(h);
              client.print("%</H2><br />");
                            
              client.print("<h2 align=center>DHT Heat Index: ");
              client.print (hic);
              client.print("C</h2><br />");              
          }
*/

          sensors.requestTemperatures(); // Send the command to get temperatures
          client.print ("<h2 align=center>Temperature: "); // DS18B20 Sensor
          client.print (sensors.getTempCByIndex(0));
          client.print ("C, ");
          fc = (sensors.getTempCByIndex(0) * 9/5) + 32;
          client.print (fc);
          client.print("F</h2>");
          client.println("<br />"); 
          
          /*
          // output the value of each analog input pin
          for (int analogChannel = 0; analogChannel < 6; analogChannel++) {
            int sensorReading = analogRead(analogChannel);
            client.print("analog input ");
            client.print(analogChannel);
            client.print(" is ");
            client.print(sensorReading);
            client.println("<br />");
          }
          */
          client.println("</html>");
          break;
        }
        if (c == '\n') {
          // you're starting a new line
          currentLineIsBlank = true;
        } else if (c != '\r') {
          // you've gotten a character on the current line
          currentLineIsBlank = false;
        }
      }
    }
    // give the web browser time to receive the data
    delay(1000);
    // close the connection:
    client.stop();
    #ifdef DEVELOP
    Serial.println("client disconnected");
    #endif
  }     

  if (millis() - lastConnectionTime > postingInterval) {
     log_data();
  }
}

void log_data() {
    #ifdef DEVELOP
        Serial.println("Attempting to connect to Web Server");
    #endif
    EthernetClient webclient;
    if (webclient.connect(ip_webserver, 80)) {
       sensors.requestTemperatures(); // Send the command to get temperatures
       webclient.print("GET /datalogger.php?");
       webclient.print("TEMPC=");
       webclient.print(sensors.getTempCByIndex(0));
       webclient.println(" HTTP/1.1");
       webclient.println("Host: 192.168.1.177");
       webclient.println("User-Agent: arduino-ethernet");
       webclient.println("Connection: close");
       webclient.println();
       webclient.stop();
      
       lastConnectionTime = millis();
    }
}

