// use voltage divider between Arduino Tx ----------------> gsm rx 
#include <SoftwareSerial.h>
// SIM800 setup
SoftwareSerial sim800(7, 8); // RX, TX
String incomingSMS = "";
String phoneNumber = "";

// Add authorized numbers here (with country code, no spaces)
const int MAX_USERS = 5;
String authorizedUsers[MAX_USERS] = {
  "+919876543210",   // Mom
  "+919812345678",   // Dad
  "+919900112233",   // Me
  "",                // empty slot
  ""                 // empty slot
};

void setup() 
{
  Serial.begin(9600);
  sim800.begin(9600);
  delay(4000);
  sim800.println("AT"); 
  delay(1000);
  sim800.println("AT+CMGF=1");           
  delay(1000);                           // Text mode
  sim800.println("AT+CNMI=2,2,0,0,0");   
  delay(1000);                           // New SMS alert
  sim800.println("AT+CIPGSMLOC=1,1");    
  delay(1000);                           // Warm up LBS
  Serial.println("Ready! Only authorized users will get a reply.");
}

void loop()
 {
  if (sim800.available()) 
  {
    char c = sim800.read();
    incomingSMS += c;
    
    if (incomingSMS.indexOf("+CMT:") >= 0 && incomingSMS.indexOf("\n") > 0) 
    {
      delay(500);
      
      // Extract sender number
      int quoteStart = incomingSMS.indexOf("\"") + 1;
      int quoteEnd = incomingSMS.indexOf("\"", quoteStart);
      phoneNumber = incomingSMS.substring(quoteStart, quoteEnd);
      phoneNumber.trim();
      
      Serial.println("SMS from: " + phoneNumber);
      
      //  Only reply to authorized users
      if (isAuthorized(phoneNumber)) 
      {
        Serial.println(" Authorized. Sending location...");
        getLocationAndReply();
      }
       else
        {
        Serial.println(" Unauthorized. Ignoring.");
        // Optional: silently ignore, or send "Access denied"
        // sendSMS(phoneNumber, "Access denied.");
      }
      
      incomingSMS = "";
    }
  }
}

//  Check if number is in whitelist
bool isAuthorized(String number) 
{
  number.trim();
  for (int i = 0; i < MAX_USERS; i++) 
  {
    if (authorizedUsers[i].length() > 0 && number == authorizedUsers[i]) 
    {
      return true;
    }
  }
  return false;
}

void getLocationAndReply() 
{
  while (sim800.available())
   sim800.read();
  sim800.println("AT+CIPGSMLOC=1,1");
  delay(3000);
  String response = "";
  while (sim800.available()) 
  {
    response += (char)sim800.read();
  }
  
  Serial.println("Response: " + response);
  
  String lat = "0", lng = "0";
  int locStart = response.indexOf("+CIPGSMLOC: ");
  
  if (locStart >= 0) 
  {
    String data = response.substring(locStart + 11);
    
    int comma1 = data.indexOf(',');
    int comma2 = data.indexOf(',', comma1 + 1);
    int comma3 = data.indexOf(',', comma2 + 1);
    
    if (comma1 > 0 && comma2 > 0) 
    {
      lng = data.substring(comma1 + 1, comma2);
      lat = data.substring(comma2 + 1, comma3);
    }
  }
  
  // If location failed, tell user
  if (lat == "0" || lng == "0")
   {
    sendSMS(phoneNumber, "Sorry, couldn't get location. Try again.");
    return;
  }
  
  String mapsLink = "https://maps.google.com/?q=" + lat + "," + lng;
  sendSMS(phoneNumber, "My Location: " + mapsLink);
}

void sendSMS(String number, String message) 
{
  sim800.println("AT+CMGF=1");
  delay(1000);
  
  sim800.print("AT+CMGS=\"");
  sim800.print(number);
  sim800.println("\"");
  delay(1000);
  
  sim800.print(message);
  delay(100);
  sim800.write(26); // Ctrl+Z to send
  delay(5000);
  
  Serial.println("SMS sent to " + number);
}
