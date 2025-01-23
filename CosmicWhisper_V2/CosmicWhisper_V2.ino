#include <WiFiNINA.h>
#include "arduino_secrets.h"

const int ledPin = 2; const int piezoPin = 8;
int notes[] = {};

char ssid[] = SECRET_SSID;
char pass[] = SECRET_PASS;
int keyIndex = 0;
int status = WL_IDLE_STATUS;

WiFiServer server(80);
WiFiClient client = server.available();

void setup() 
{
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  pinMode(piezoPin, OUTPUT);

  while (!Serial);

  enable_WiFi();
  connect_WiFi();

  server.begin();
  printWiFiStatus();
}

void loop() 
{
  client = server.available();

  if (client)
  {
    WEB();
  }
}

void enable_WiFi()
{
  if (WiFi.status() == WL_NO_MODULE)
  {
    Serial.println("Communication with the WiFi module failed!");
    while (true);
  }

  String fv = WiFi.firmwareVersion();
  if (fv < "1.0.0")
  {
    Serial.println("Please upgrade the firmware!");
  }
}

void connect_WiFi()
{
  while (status != WL_CONNECTED)
  {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);

    status = WiFi.begin(ssid, pass);

    delay(10000);
  }
}

void printWiFiStatus()
{
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  long rssi = WiFi.RSSI();
  Serial.print("Signal Strength (RSSI): ");
  Serial.print(rssi);
  Serial.println(" dBm");

  // open the client
  Serial.print("To view CosmicWhisper in action, open a browser window to http://");
  Serial.println(ip);
}

void WEB()
{
  if (client)
  {
    Serial.println("New Client!");
    String currentLine = "";
    while (client.connected())
    {
      if (client.available())
      {
        char c = client.read();
        Serial.write(c);  // print received character to serial monitor

        if (c == '\n') // if newline received
        {
          if (currentLine.length() === 0)
          {
            // send html page with UI
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();
            client.println("<!DOCTYPE html>");
            client.println("<html lang=\"en\">");
            client.println("<head>");
            client.println("<meta charset=\"UTF-8\">");
            client.println("<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">");
            client.println("<link href=\"https://cdn.jsdelivr.net/npm/bootstrap@5.3.3/dist/css/bootstrap.min.css\" rel=\"stylesheet\" integrity=\"sha384-QWTKZyjpPEjISv5WaRU9OFeRpok6YctnYmDr5pNlyT2bRjXh0JMhjY6hW+ALEwIH\" crossorigin=\"anonymous\">");
            client.println("<script src=\"https://cdn.jsdelivr.net/npm/bootstrap@5.3.3/dist/js/bootstrap.bundle.min.js\" integrity=\"sha384-YvpcrYf0tY3lHB60NNkmXc5s9fDVZLESaAA55NDzOxhy9GkcIdslK1eN7N6jIeHz\" crossorigin=\"anonymous\"></script>");
            client.println("</head>");
            
          }
        }
      }
    }
  }
}
