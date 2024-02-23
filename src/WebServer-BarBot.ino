
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <Arduino.h>

#ifndef APSSID
#define APSSID "ESPap"
#define APPSK "thereisnospoon"
#endif

#include "secrets.h"  // add WLAN Credentials in here.

// TRACE output simplified, can be deactivated here
#define TRACE(...) Serial.printf(__VA_ARGS__)

// name of the server. You reach it using http://barbot
#define HOSTNAME "barbot"

// local time zone definition (Berlin)
#define TIMEZONE "CET-1CEST,M3.5.0,M10.5.0/3"

// need a WebServer for http access on port 80.
ESP8266WebServer server(80);

// The text of builtin files are in this header file
#include "builtinfiles.h"

void setup(void) {
  delay(3000);
  Serial.begin(115200);
  Serial.setDebugOutput(false);

  TRACE("Starting Barbot server...\n");

  //start WiFI
  WiFi.mode(WIFI_STA);
  if (strlen(ssid) == 0) {
    WiFi.begin();
  } else {
    WiFi.begin(ssid, passPhrase);
  }

  // // allow to address the device by the given name e.g. http://barbot
  WiFi.setHostname(HOSTNAME);

  // Serial.print("Configuring access point...");
  // /* You can remove the password parameter if you want the AP to be open. */
  // WiFi.softAP(ssid);

  // IPAddress myIP = WiFi.softAPIP();
  // Serial.print("AP IP address: ");
  // Serial.println(myIP);
  // Serial.println("HTTP server started");

  TRACE("Connect to WiFi...\n");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    TRACE(".");
  }
  TRACE("connected.\n");

  // Ask for the current time using NTP request builtin into ESP firmware.
  TRACE("Setup ntp...\n");
  configTime(TIMEZONE, "pool.ntp.org");

  // enable CORS header in webserver results
  server.enableCORS(true);

  TRACE("Register service handlers...\n");
  server.on("/", []() {
    server.send(200, "text/html", FPSTR(indexPage));
  });

  server.on("/cocktails", HTTP_POST, cocktailHandler);
  
  // handle cases when file is not found
  server.onNotFound([]() {
    // standard not found in browser.
    server.send(404, "text/html", FPSTR(notFoundContent));
  });

  server.begin();
  TRACE("hostname=%s\n", WiFi.getHostname());
}

void cocktailHandler(){
  if(server.args()==0)
  {
    server.send(400, "text/plain", "Cocktail id is required");
    return;
  }
  TRACE("Making Cocktail: %s",server.arg(0));
  server.send(200, "text/plain", "Making Cocktail: "+server.arg(0));
}

void loop(void) {
  server.handleClient();
}