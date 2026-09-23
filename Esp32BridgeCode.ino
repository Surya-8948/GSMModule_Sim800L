/*
  ESP32 GPIO16 (RX2) <----- SIM800 TX
  ESP32 GPIO17 (TX2) -----> SIM800 RX
*/
HardwareSerial sim800(2);   // UART2
void setup()
{
  Serial.begin(115200);                         // USB Serial Monitor
  sim800.begin(9600, SERIAL_8N1, 16, 17);       // RX2, TX2 ( 8 Data Bits ,No Parity, 1 Stop Bit)
  delay(3000);
  Serial.println("ESP32 SIM800 Bridge Ready");
}

void loop()
{
  // PC -> SIM800
  while (Serial.available())
  {
    sim800.write(Serial.read());
  }
  // SIM800 -> PC
  while (sim800.available())
  {
    Serial.write(sim800.read());
  }
}
