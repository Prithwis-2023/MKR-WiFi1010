#include <WiFiNINA.h>
#include <utility/wifi_drv.h>

void setup() 
{
  for (int i = 25; i < 28; i++)
  {
    WiFiDrv::pinMode(i, OUTPUT); // Set RGB pins as output
  }  
}

void loop() 
{
  WiFiDrv::analogWrite(25, 0);   
  WiFiDrv::analogWrite(26, 255); 
  WiFiDrv::analogWrite(27, 255); 
  delay(1000);

  WiFiDrv::analogWrite(25, 255);
  WiFiDrv::analogWrite(26, 0);  
  WiFiDrv::analogWrite(27, 255);

  delay(1000);

  WiFiDrv::analogWrite(25, 255); 
  WiFiDrv::analogWrite(26, 255); 
  WiFiDrv::analogWrite(27, 0);  

  delay(1000);

  WiFiDrv::analogWrite(25, 255);
  WiFiDrv::analogWrite(26, 255);
  WiFiDrv::analogWrite(27, 255); 

  delay(1000);
}
