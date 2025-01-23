#include <ArduinoBLE.h>

BLEService newService("180A"); // creating the service

BLEUnsignedCharCharacteristic randomReading("2A58", BLERead | BLENotify); // creating the analog value characteristic
BLEByteCharacteristic switchChar("2A57", BLERead | BLEWrite);  // create the digital output characteristic

const int ledPin = 2;
long previousMillis = 0;

void setup() 
{
  Serial.begin(9600);
  while(!Serial);
  pinMode(LED_BUILTIN, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);

  if (!BLE.begin())
  {
    Serial.println("starting Bluetooth Low Energy failed!");
    while(1);
  }

  BLE.setLocalName("MKR WiFi 1010");
  BLE.setAdvertisedService(newService);

  newService.addCharacteristic(switchChar);
  newService.addCharacteristic(randomReading);

  BLE.addService(newService);

  switchChar.writeValue(0);
  randomReading.writeValue(0);

  BLE.advertise();
  Serial.println("Bluetooth device active, waiting for connections...");
}

void loop() 
{
  BLEDevice central = BLE.central();
  if (central)
  {
    Serial.print("Connected to central: ");
    Serial.println(central.address());
    digitalWrite(LED_BUILTIN, HIGH);

    while(central.connected())
    {
      long currentMillis = millis();
      if (currentMillis - previousMillis >= 200)
      {
        previousMillis = currentMillis;
        
        int randomVal = analogRead(A1);
        randomReading.writeValue(randomVal);

        if (switchChar.written())
        {
          if (switchChar.value())
          {
            Serial.println("LED on");
            digitalWrite(ledPin, HIGH);
          }
          else
          {
            Serial.println(F("LED off"));
            digitalWrite(ledPin, LOW);
          }
        }
      }
    }
    digitalWrite(LED_BUILTIN, LOW);
    Serial.print("Disconnected from central: ");
    Serial.println(central.address());
  }
}
