#include <WiFiNINA.h>
#include "arduino_secrets.h"

char ssid[] = SECRET_SSID;
char pass[] = SECRET_PASS;
int status = WL_IDLE_STATUS;  // the Wifi radio's status

void setup() 
{
  Serial.begin(9600);
  
  while(!Serial);

  while (status != WL_CONNECTED)
  {
    Serial.print("Attempting to connect to network: ");
    Serial.print(ssid);
    Serial.println();
    status = WiFi.begin(ssid, pass);  // Connect to WPA/WPA2 network

    delay(10000);
  }

  Serial.println("You're connected to the network!");
  Serial.println("----------------------------------------");
  printData();
  Serial.println("----------------------------------------");
}

void loop() 
{
  delay(10000);
  printData();
  Serial.println("----------------------------------------");
}

void printData()
{
  Serial.println("Board Information: ");
  IPAddress ip = WiFi.localIP();  // board's IP address
  Serial.print("Board IP Address: ");
  Serial.println(ip);
  Serial.println();
  Serial.print("Network Information: ");
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  long rssi = WiFi.RSSI();
  Serial.print("Signal Strength (RSSI): ");
  Serial.println(rssi);

  byte encryptionType = WiFi.encryptionType();
  Serial.print("Encrpytion Type: ");
  Serial.println(encryptionType, HEX);
  Serial.println();
}