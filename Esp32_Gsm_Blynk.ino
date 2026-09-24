/*************************************************************
   ESP32 + SIM800L + Blynk IoT
   Relay Control Example
*************************************************************/

// ---------- Select Modem ----------
#define TINY_GSM_MODEM_SIM800

// ---------- Blynk ----------
#define BLYNK_TEMPLATE_ID "TMPLxxxx"
#define BLYNK_TEMPLATE_NAME "SIM800"
#define BLYNK_AUTH_TOKEN "YourAuthToken"

// ---------- Libraries ----------
#include <TinyGsmClient.h>
#include <BlynkSimpleTinyGSM.h>

// ---------- Serial ----------
HardwareSerial SerialAT(1);

// ESP32 RX = GPIO16
// ESP32 TX = GPIO17
#define MODEM_RX 16
#define MODEM_TX 17

// ---------- APN ----------
char apn[]  = "airtelgprs.com";
char user[] = "";
char pass[] = "";

// ---------- Objects ----------
TinyGsm modem(SerialAT);
TinyGsmClient client(modem);

// ---------- Relay ----------
#define RELAY1 23

//--------------------------------------------------
void setup()
{
  Serial.begin(115200);
  pinMode(RELAY1, OUTPUT);
  digitalWrite(RELAY1, LOW);

  // Start UART
  SerialAT.begin(9600, SERIAL_8N1, MODEM_RX, MODEM_TX);
  Serial.println("Restarting Modem...");
  modem.restart();
  //------------------------------------------------
  // SIM Ready
  //------------------------------------------------
  if (!modem.getSimStatus())
  {
    Serial.println("SIM Not Ready");
    while (1);
  }
  //------------------------------------------------
  // Wait Network
  //------------------------------------------------
  Serial.println("Waiting Network...");

  if (!modem.waitForNetwork())
  {
    Serial.println("Network Failed");
    while (1);
  }
  Serial.println("Network Connected");
  //------------------------------------------------
  // GPRS Connect
  //------------------------------------------------
  if (!modem.gprsConnect(apn, user, pass))
  {
    Serial.println("GPRS Failed");
    while (1);
  }
  Serial.println("GPRS Connected");
  //------------------------------------------------
  // Connect Blynk
  //------------------------------------------------
  Blynk.config(modem, BLYNK_AUTH_TOKEN);

  if (Blynk.connect())
  {
    Serial.println("Blynk Connected");
  }
  else
  {
    Serial.println("Blynk Failed");
  }
}
//--------------------------------------------------
// Blynk Button V0
//--------------------------------------------------
BLYNK_WRITE(V0)
{
  int value = param.asInt();
  digitalWrite(RELAY1, value);
  Serial.print("Relay = ");
  Serial.println(value);
}
//--------------------------------------------------
void loop()
{
  // Maintain Blynk Connection
  Blynk.run();
  // Auto Reconnect
  if (!modem.isGprsConnected())
  {
    Serial.println("Reconnect GPRS...");
    modem.gprsConnect(apn, user, pass);
  }
  if (!Blynk.connected())
  {
    Serial.println("Reconnect Blynk...");
    Blynk.connect();
  }
}
