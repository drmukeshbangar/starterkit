/*
   Copyright (c) 2023, Muks Robotics LLP
   All rights reserved.
   Steps to connect with MuksOS AI Launcher
   1. Install MuksOS launcher App to your mobile phone
   2. Flash this code to NodeMCU device and connect LEDs to D0, D1, D2, D3 and D7 PINS
   3. Open wifi Tab and search for MuksWifi SSID and put password 12345678 and connect to access point
   4. Then go to MuksOS App in create action Tab. In input add your voice command eg. Turn on light. 
      select 'http request' in action type then add one of the below links as per desirable output.
	  - 192.168.4.1/D1_ON
	  - 192.168.4.1/D1_OFF
	  - 192.168.4.1/D2_ON
	  - 192.168.4.1/D2_OFF
	  - 192.168.4.1/D3_ON
	  - 192.168.4.1/D3_OFF
	  - 192.168.4.1/D4_ON
	  - 192.168.4.1/D4_OFF
	  - 192.168.4.1/D5_ON
	  - 192.168.4.1/D5_OFF
	  - 192.168.4.1/ALL_ON
	  - 192.168.4.1/ALL_OFF
	5. Then try voice commands. Dont forget to check, Mobiles wifi must be connect with Muks SSID.
	
/* Create a WiFi access point and provide a web server on it.*/

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

#ifndef APSSID
#define APSSID "MuksWifi"
#define APPSK  "12345678"
#endif

#define led1 D0
#define led2 D1
#define led3 D2
#define led4 D3
#define led5 D7

/* Set these to your desired credentials. */
const char *ssid = APSSID;
const char *password = APPSK;

ESP8266WebServer server(80);

/* Just a little test message.  Go to http://192.168.4.1 in a web browser
   connected to this access point to see it.
*/
void handleRoot() {
  server.send(200, "text/plain", "speak connected to MuksOS");
}

void setup() {
  pinMode(led1, OUTPUT);// send D11 ON send D10 OFF
  pinMode(led2, OUTPUT);// send D21 ON send D20 OFF
  pinMode(led3, OUTPUT);// send D31 ON send D30 OFF
  pinMode(led4, OUTPUT);// send D41 ON send D40 OFF
  pinMode(led5, OUTPUT);// send D51 ON send D50 OFF
  delay(1000);
  Serial.begin(115200);
  Serial.println();
  Serial.print("Configuring access point...");
  /* You can remove the password parameter if you want the AP to be open. */
  WiFi.softAP(ssid, password);

  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
  server.on("/", handleRoot);

 server.on("/D1_ON", []()                                   
  {
    digitalWrite(led1, HIGH);
    Serial.println("1st LED on");
    server.send(200, "text/plain", "speak sir FIRST L E D is turning on");
  });
  
  server.on("/D1_OFF", []()                                 
  {
    digitalWrite(led1, LOW);
    Serial.println(" 1st LED off");
    server.send(200, "text/plain", "speak sir FIRST L E D is turning off");
  });

  server.on("/D2_ON", []()                                
  {
    digitalWrite(led2, HIGH);
    Serial.println("2nd LED ON");
    server.send(200, "text/plain", "speak sir SECOND L E D is turning on");
  });

  server.on("/D2_OFF", []()                               
  {
    digitalWrite(led2, LOW);
    Serial.println("2nd LED off");
    server.send(200, "text/plain", "speak sir SECOND L E D is turning off");
  });

  server.on("/D3_ON", []()                            
  {
    digitalWrite(led3, HIGH);
    Serial.println("3rd LED on");
    server.send(200, "text/plain", "speak sir THIRD L E D is turning on");
  });

  server.on("/D3_OFF", []()                            
  {
    digitalWrite(led3, LOW);
    Serial.println("3rd LED off");
    server.send(200, "text/plain", "speak sir THIRD L E D is turning off");
  });

  server.on("/D4_ON", []()
  {
    digitalWrite(led4, HIGH);
    Serial.println("4th LED on");
    server.send(200, "text/plain", "speak sir FOURTH L E D is turning on");
  });

  server.on("/D4_OFF", []()
  {
    digitalWrite(led4, LOW);
    Serial.println(" 4th LED off");
    server.send(200, "text/plain", "speak sir FOURTH L E D is turning off");
  });

  server.on("/D5_ON", []()                       
  {
    digitalWrite(led5, HIGH);
    Serial.println("5th LED on");
    server.send(200, "text/plain", "speak sir FIFTH L E D is turning on");
  });

  server.on("/D5_OFF", []()                               
  {
    digitalWrite(led5, LOW);
    Serial.println("5th LED off");
    server.send(200, "text/plain", "speak sir FIFTH L E D is turning off");
  });
  
  server.on("/ALL_ON", []()
  {
    digitalWrite(led1, HIGH);
    digitalWrite(led2, HIGH);
    digitalWrite(led3, HIGH);
    digitalWrite(led4, HIGH);
    digitalWrite(led5, HIGH);
    Serial.println("all LED on");
    server.send(200, "text/plain", "speak sir ALL LIGHTS ARE turning on");
  });
  
  server.on("/ALL_OFF", []()
  {
    digitalWrite(led1 , LOW);
    digitalWrite(led2 , LOW);
    digitalWrite(led3 , LOW);
    digitalWrite(led4 , LOW);
    digitalWrite(led5 , LOW);
    Serial.println("all LED off");
    server.send(200, "text/plain", "speak sir ALL LIGHTS ARE turning off");
  });
  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();
}
