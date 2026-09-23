// For Esp32 
#include <HardwareSerial.h>
HardwareSerial gsm(2);
const char *USER = "+919876543210";   // Authorized Number
bool relay = true;

void setup() {
  Serial.begin(115200);
  gsm.begin(9600, SERIAL_8N1, 16, 17);// rx2 , tx2
  pinMode(2, OUTPUT);
  digitalWrite(2, HIGH);
  delay(3000);
  gsm.println("AT");
  delay(500);
  gsm.println("AT+CLIP=1");   // Enable Caller ID ,CLIP = Calling Line Identification Presentation
}
void loop() 
{
  if (gsm.available())
  {
    String data = gsm.readStringUntil('\n');
    Serial.println(data);
    if (data.indexOf(USER) != -1) {
      gsm.println("ATH");                 // Reject Call
      relay = !relay;                     // Toggle Relay
      digitalWrite(2, relay);
      Serial.println(relay ? "Relay ON" : "Relay OFF");
      delay(1500);                        // Ignore duplicate CLIP
    }
  }
}
