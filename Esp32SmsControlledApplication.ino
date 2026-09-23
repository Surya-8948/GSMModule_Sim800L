#include <HardwareSerial.h>
HardwareSerial gsm(2);
#define CH1 2
#define CH2 4
#define CH3 5
#define CH4 18
const String USER = "+919876543210";   // Authorized Mobile Number
String msg;
void setup()
{
  Serial.begin(115200);
  gsm.begin(9600, SERIAL_8N1,16,17);
  pinMode(CH1,OUTPUT);
  pinMode(CH2,OUTPUT);
  pinMode(CH3,OUTPUT);
  pinMode(CH4,OUTPUT);
  gsm.println("AT");
  delay(1000);
  gsm.println("AT+CMGF=1");
  gsm.println("AT+CNMI=2,2,0,0,0");
}
void loop() 
{
  if(gsm.available())
  {
    msg = gsm.readString();
    Serial.println(msg);
    // Ignore SMS from unknown numbers
    if(msg.indexOf(USER) == -1) // most imp line if auth number is not detected  then it will return -1 ,
      return;
    if(msg.indexOf("CH1 ON")!=-1) digitalWrite(CH1,HIGH);
    if(msg.indexOf("CH1 OFF")!=-1) digitalWrite(CH1,LOW);
    if(msg.indexOf("CH2 ON")!=-1) digitalWrite(CH2,HIGH);
    if(msg.indexOf("CH2 OFF")!=-1) digitalWrite(CH2,LOW);
    if(msg.indexOf("CH3 ON")!=-1) digitalWrite(CH3,HIGH);
    if(msg.indexOf("CH3 OFF")!=-1) digitalWrite(CH3,LOW);
    if(msg.indexOf("CH4 ON")!=-1) digitalWrite(CH4,HIGH);
    if(msg.indexOf("CH4 OFF")!=-1) digitalWrite(CH4,LOW);
    if(msg.indexOf("ALL ON")!=-1)
    {
      digitalWrite(CH1,HIGH);
      digitalWrite(CH2,HIGH);
      digitalWrite(CH3,HIGH);
      digitalWrite(CH4,HIGH);
    }

    if(msg.indexOf("ALL OFF")!=-1)
    {
      digitalWrite(CH1,LOW);
      digitalWrite(CH2,LOW);
      digitalWrite(CH3,LOW);
      digitalWrite(CH4,LOW);
    }
  }
}
