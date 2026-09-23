// Blynk details
#define BLYNK_TEMPLATE_ID "TMPLxxxxxx"
#define BLYNK_TEMPLATE_NAME "GSM Automation"
#define BLYNK_AUTH_TOKEN "xxxxxxxxxxxxxxxx"
#define BLYNK_PRINT Serial

// Libraries
#define TINY_GSM_MODEM_SIM800
#include <TinyGsmClient.h>
#include <BlynkSimpleTinyGSM.h>
#include <DHT.h>

// ESP32 Hardware Serial 2 (SIM800L)
HardwareSerial gsmSerial(2);  // UART2

// Pins
#define GSM_RX 16
#define GSM_TX 17
#define DHT_PIN 4
#define RELAY1 5
#define RELAY2 18
#define PIR 19

DHT dht(DHT_PIN, DHT11);

// APN - apna SIM daalo
char apn[] = "airtelgprs.com";

TinyGsm modem(gsmSerial);
BlynkTimer timer;

// ============ BLYNK CONTROL ============
BLYNK_WRITE(V3) {
  digitalWrite(RELAY1, param.asInt());
}

BLYNK_WRITE(V4) {
  digitalWrite(RELAY2, param.asInt());
}

// ============ SETUP ============
void setup() {
  Serial.begin(115200);
  delay(1000);

  // GSM init - ESP32 Hardware Serial
  gsmSerial.begin(9600, SERIAL_8N1, GSM_RX, GSM_TX);
  dht.begin();

  pinMode(RELAY1, OUTPUT);
  pinMode(RELAY2, OUTPUT);
  pinMode(PIR, INPUT);

  digitalWrite(RELAY1, LOW);
  digitalWrite(RELAY2, LOW);

  delay(3000);

  Serial.println("Modem start...");
  modem.restart();

  Serial.println("Blynk connect...");
  Blynk.begin(BLYNK_AUTH_TOKEN, modem, apn);

  // Har 10 second me data bhejo
  timer.setInterval(10000L, sendData);

  Serial.println("Ready!");
}

// ============ LOOP ============
void loop()
{
  Blynk.run();
  timer.run();
}

// ============ SEND ALL DATA ============
void sendData()
{
  if (!Blynk.connected()) 
    return;

  // Temperature & Humidity
  float t = dht.readTemperature();
  float h = dht.readHumidity();
  if (!isnan(t)) 
  {
    Blynk.virtualWrite(V5, t);
    Blynk.virtualWrite(V6, h);
    Serial.print("Temp: "); Serial.println(t);
  }

  // Motion
  int motion = digitalRead(PIR);
  Blynk.virtualWrite(V7, motion);
  if (motion) 
    Serial.println("Motion detected!");

  // Location
  float lat, lng;
  if (getLocation(lat, lng)) {
    Blynk.virtualWrite(V1, lat);
    Blynk.virtualWrite(V2, lng);
    Serial.print("Location: ");
    Serial.print(lat); Serial.print(", "); Serial.println(lng);
  }
}

// ============ GET LOCATION ============
bool getLocation(float &lat, float &lng) {
  while (gsmSerial.available()) gsmSerial.read();

  gsmSerial.println("AT+CIPGSMLOC=1,1");
  delay(3000);

  String res = "";
  while (gsmSerial.available()) res += (char)gsmSerial.read();

  int start = res.indexOf("+CIPGSMLOC: ");
  if (start < 0) return false;

  String data = res.substring(start + 12);
  int c1 = data.indexOf(',');
  int c2 = data.indexOf(',', c1 + 1);
  int c3 = data.indexOf(',', c2 + 1);

  if (c1 < 0 || c2 < 0 || c3 < 0) return false;

  lng = data.substring(c1 + 1, c2).toFloat();
  lat = data.substring(c2 + 1, c3).toFloat();

  return (lat != 0 && lng != 0);
}
