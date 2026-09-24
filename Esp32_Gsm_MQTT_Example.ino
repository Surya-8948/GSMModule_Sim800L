/************************************************************
   ESP32 + SIM800L + MQTT Example
   Broker : broker.hivemq.com
   Topic  : home/relay

   Payload:
   ON  -> Relay ON
   OFF -> Relay OFF
************************************************************/

// ---------- Select GSM Module ----------
#define TINY_GSM_MODEM_SIM800

// ---------- Libraries ----------
#include <TinyGsmClient.h>   // SIM800L communication
#include <PubSubClient.h>    // MQTT Library

// ---------- UART1 for SIM800 ----------
HardwareSerial SerialAT(1);

// ---------- Create Objects ----------
TinyGsm modem(SerialAT);          // SIM800 Modem Object
TinyGsmClient gsmClient(modem);   // Internet Client using SIM800
PubSubClient mqtt(gsmClient);     // MQTT Client

// ---------- APN Settings ----------
const char apn[]  = "airtelgprs.com";   // SIM APN
const char user[] = "";                 // APN Username
const char pass[] = "";                 // APN Password

// ---------- MQTT Broker ----------
const char* broker = "broker.hivemq.com"; // MQTT Server Address
const int port = 1883;                   // MQTT Port (Non SSL)

// ---------- Relay Pin ----------
#define RELAY 23

//============================================================
// Callback Function
// Broker se jab bhi koi message aayega,
// ye function automatically call hoga.
//============================================================
void callback(char* topic, byte* payload, unsigned int length)
{
  String msg = "";

  // Payload ko Byte Array se String me Convert karo
  for (int i = 0; i < length; i++)
    msg += (char)payload[i];

  // Serial Monitor par Print karo
  Serial.println(msg);

  // Relay ON
  if (msg == "ON")
  {
    digitalWrite(RELAY, HIGH);
  }
  // Relay OFF
  if (msg == "OFF")
  {
    digitalWrite(RELAY, LOW);
  }
}

//============================================================
// MQTT Connect Function
// Agar MQTT Disconnect ho jaye
// to dubara Connect karega
//============================================================
void mqttConnect()
{
  // Jab tak MQTT Connect na ho
  while (!mqtt.connected())
  {
    Serial.println("Connecting MQTT...");

    // Client ID = ESP32_SIM800
    if (mqtt.connect("ESP32_SIM800"))
    {
      Serial.println("MQTT Connected");

      // Topic Subscribe
      mqtt.subscribe("home/relay");
    }
    else
    {
      Serial.println("Retry After 3 Seconds");
      delay(3000);
    }
  }
}

//============================================================
// Setup
// Sirf ek baar chalta hai
//============================================================
void setup()
{
  // Serial Monitor Start
  Serial.begin(115200);

  // Relay Pin Output
  pinMode(RELAY, OUTPUT);

  // SIM800 UART Start
  // RX = GPIO16
  // TX = GPIO17
  SerialAT.begin(9600, SERIAL_8N1, 16, 17);

  // Restart SIM800
  modem.restart();

  // GSM Network ka Wait
  modem.waitForNetwork();

  // Internet (GPRS) Connect
  modem.gprsConnect(apn, user, pass);

  // MQTT Broker Address & Port
  mqtt.setServer(broker, port);

  // Callback Register
  mqtt.setCallback(callback);
}

//============================================================
// Loop
// Baar Baar Chalta Hai
//============================================================
void loop()
{
  // Agar MQTT Disconnect ho gaya
  if (!mqtt.connected())
      mqttConnect();

  // MQTT Messages Receive Karega
  // Aur Keep Alive Packet Send Karega
  mqtt.loop();
}
