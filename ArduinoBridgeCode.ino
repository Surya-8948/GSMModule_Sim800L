// for Arduino Use Voltage Divider Between  Arduino Tx ----------->GSM Rx 
// For Esp8266 change pin Accordingly , Use D before write pin number 
#include<SoftwareSerial.h>
SoftwareSerial sim800(7,8); //rx, tx
void setup() 
{
Serial.begin(115200);
sim800.begin(9600);
delay(3000);

}

void loop()
 {
  if(Serial.available()>0)
  {
    sim800.write(Serial.read());
  }
  if(sim800.available()>0)
  {
    sim800.write(F("AT"));// F is a Arduino marco that store AT in flash memory instead of Ram 
    Serial.write(sim800.read());
  }
}
/* Responce
SerialMonitor > AT
Responce      > ok 
*/
