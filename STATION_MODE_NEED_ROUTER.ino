/*
   Copyright (c) 2023, Muks Robotics LLP
   All rights reserved.
   Steps to connect with MuksOS AI Launcher
   1. Install MuksOS launcher App to your mobile phone
   2. Flash this code to NodeMCU device and connect LEDs to D0, D1, D2, D3 and D7 PINS
   3. Connect wifi and NODEMCU with same Network of your Router.
   4. You will get IP ADDRESS and which will help you to Create Action
   5. Then go to MuksOS App in create action Tab. In input add your voice command eg. Turn on light. 
      select 'http request' in action type then add one of the below links as per desirable output.
	  - your_connected_router_ip/D1_ON
	  - your_connected_router_ip/D1_OFF
	  - your_connected_router_ip/D2_ON
	  - your_connected_router_ip/D2_OFF
	  - your_connected_router_ip/D3_ON
	  - your_connected_router_ip/D3_OFF
	  - your_connected_router_ip/D4_ON
	  - your_connected_router_ip/D4_OFF
	  - your_connected_router_ip/D5_ON
	  - your_connected_router_ip/D5_OFF
	  - your_connected_router_ip/ALL_ON
	  - your_connected_router_ip/ALL_OFF
	5. Then try voice commands. Dont forget to check, Mobiles wifi must be connect with Muks SSID.
	
/* Create a WiFi access point and provide a web server on it.*/

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

#ifndef STASSID
#define STASSID "MuksWifi"
#define STAPSK  "00000000"
#endif


#define led1 D0
#define led2 D1
#define led3 D2
#define led4 D3
#define led5 D7


const char* ssid = STASSID;
const char* password = STAPSK;

ESP8266WebServer server(80);
const int led = 13;
void handleRoot() {
  server.send(200, "text/plain", "speak connected to MuksOS");
}

void handleNotFound() {
  digitalWrite(led, 1);
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i = 0; i < server.args(); i++) {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
  digitalWrite(led, 0);
}
void setup(void) {
  pinMode(led1, OUTPUT);// send D11 ON send D10 OFF
  pinMode(led2, OUTPUT);// send D21 ON send D20 OFF
  pinMode(led3, OUTPUT);// send D31 ON send D30 OFF
  pinMode(led4, OUTPUT);// send D41 ON send D40 OFF
  pinMode(led5, OUTPUT);// send D51 ON send D50 OFF
  digitalWrite(led, 0);
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("This IP address need to use for http request: ");
  Serial.println(WiFi.localIP());

  if (MDNS.begin("esp8266")) {
    Serial.println("MDNS responder started");
  }
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
    Serial.println("4th LED off");
    server.send(200, "text/plain", "speak sir FOURTH L E D is turning off");
  });
  server.on("/D5_ON", []()                           
  {
    digitalWrite(led5, HIGH);
    Serial.println("5th LED on");
    server.send(200, "text/plain", "speak sir FIFTH L E D is turning on");
  });
  server.on("/D5_OFF", []()                                 
  { digitalWrite(led5, LOW);
    Serial.println("5th LED off");
    server.send(200, "text/plain", "speak sir FIFTH L E D is turning off");
  });
  server.on("/ALL_ON", []()                                
  { digitalWrite(led1, HIGH);
    digitalWrite(led2, HIGH);
    digitalWrite(led3, HIGH);
    digitalWrite(led4, HIGH);
    digitalWrite(led5, HIGH);
    Serial.println("all LED on");
    server.send(200, "text/plain", "speak sir ALL LIGHTS ARE turning on");
  });
  server.on("/ALL_OFF", []()                               
  { digitalWrite(led1 , LOW);
    digitalWrite(led2 , LOW);
    digitalWrite(led3 , LOW);
    digitalWrite(led4 , LOW);
    digitalWrite(led5 , LOW);
    Serial.println("all LED off");
    server.send(200, "text/plain", "speak sir ALL LIGHTS ARE turning off");
  });
  server.onNotFound(handleNotFound);
  server.begin();
  Serial.println("HTTP server started");
}
void loop(void) {
  server.handleClient();
  MDNS.update();
}
