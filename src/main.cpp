#include "heltec.h"
#include "esp_system.h"

#define BAND 433E6 //you can se\t band here directly,e.g. 868E6,915E6
#define SPREADING_FACTOR 11

#define SERVICE_UUID "4fafc201-1fb5-459e-8fcc-c5c9c331914b"
#define CHARACTERISTIC_UUID "beb5483e-36e1-4688-b7f5-ea07361b26a8"

#define INTERVAL 50

int xs [100] = {64, 28, 65, 0, 20, 51, 40, 53, 72, 88, 0, 116, 121, 50, 110, 35, 125, 118, 79, 89, 80, 30, 16, 67, 124, 85, 44, 11, 17, 37, 79, 53, 113, 61, 114, 108, 112, 16, 19, 103, 109, 42, 74, 11, 38, 39, 55, 120, 50, 107, 117, 28, 69, 87, 41, 78, 55, 103, 62, 38, 103, 67, 120, 86, 112, 41, 103, 65, 127, 90, 45, 104, 76, 19, 57, 99, 99, 13, 111, 84, 107, 75, 68, 87, 65, 57, 0, 73, 45, 97, 120, 127, 40, 38, 16, 113, 91, 24, 32, 75 };
int ys [100] = {53 ,52 ,56 ,19 ,53 ,32 ,28 ,59 ,45 ,24 ,39 ,55 ,57 ,41 ,26 ,4 ,31 ,38 ,58 ,24 ,17 ,6 ,12 ,42 ,57 ,56 ,53 ,52 ,39 ,57 ,27 ,27 ,40 ,45 ,60 ,57 ,36 ,59 ,52 ,39 ,52 ,29 ,32 ,62 ,34 ,56 ,3 ,30 ,11 ,39 ,4 ,26 ,59 ,12 ,15 ,42 ,52 ,36 ,44 ,10 ,22 ,35 ,61 ,16 ,17 ,56 ,9 ,16 ,42 ,63 ,50 ,62 ,13 ,44 ,6 ,59 ,49 ,13 ,15 ,15 ,25 ,18 ,57 ,0 ,29 ,9 ,1 ,20 ,12 ,41 ,34 ,45 ,18 ,10 ,21 ,11 ,25 ,45 ,23 ,58};

long lastSendTime = 0; // last send time
int msgCount = 0;

void initScreen()
{
  Heltec.display->init();
  Heltec.display->flipScreenVertically();
  Heltec.display->setFont(ArialMT_Plain_10);
  Heltec.display->display();
}

void sendLora() {
  Serial.println("sendLora [" + String(xs[msgCount]) + "," + String(ys[msgCount]) + "]");
  digitalWrite(LED, HIGH);
  LoRa.beginPacket();
  LoRa.write(-1);
  LoRa.write(xs[msgCount]);
  LoRa.write(ys[msgCount]);
  LoRa.write(0);
  LoRa.endPacket();
  digitalWrite(LED, LOW);
  msgCount++;
}

void setup()
{
  setCpuFrequencyMhz(80);
  Heltec.begin(true /*DisplayEnable Enable*/, true /*Heltec.LoRa Disable*/, true /*Serial Enable*/, true /*PABOOST Enable*/, BAND /*long BAND*/);
  LoRa.setSpreadingFactor(SPREADING_FACTOR);
  LoRa.setTxPowerMax(20);
  lastSendTime = millis();
}

void loop()
{
  if (msgCount > 99) return;
  if (millis() < (lastSendTime + INTERVAL)) return;

  lastSendTime = millis();
  sendLora(); 
}

