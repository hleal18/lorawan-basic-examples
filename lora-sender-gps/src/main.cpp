#include <TinyGPS++.h>                       
#include <SPI.h>
#include <Wire.h>
#include <LoRa.h>

#define SCK     5    // GPIO5  -- SX1278's SCK
#define MISO    19   // GPIO19 -- SX1278's MISnO
#define MOSI    27   // GPIO27 -- SX1278's MOSI
#define SS      18   // GPIO18 -- SX1278's CS
#define RST     14   // GPIO14 -- SX1278's RESET
#define DI0     26   // GPIO26 -- SX1278's IRQ(Interrupt Request)
#define BAND  915E6

int counter = 0;

TinyGPSPlus gps;        
                    
static void smartDelay(unsigned long ms);

void setup()
{
  Serial.begin(9600);
  Serial1.begin(9600, SERIAL_8N1, 12, 15);   //17-TX 18-RX

  SPI.begin(SCK,MISO,MOSI,SS);
  LoRa.setPins(SS, RST, DI0);
  Serial.println("LoRa Sender");

  
  if (!LoRa.begin(915E6)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
  LoRa.enableCrc();
  LoRa.setSpreadingFactor(7);
}

void loop()
{
  Serial.print("Latitude  : ");
  Serial.println(gps.location.lat(), 5);
  Serial.print("Longitude : ");
  Serial.println(gps.location.lng(), 4);
  Serial.print("Satellites: ");
  Serial.println(gps.satellites.value());
  Serial.print("Altitude  : ");
  Serial.print(gps.altitude.feet() / 3.2808);
  Serial.println("M");
  Serial.print("Time      : ");
  Serial.print(gps.time.hour());
  Serial.print(":");
  Serial.print(gps.time.minute());
  Serial.print(":");
  Serial.println(gps.time.second());
  Serial.println("**********************");

  smartDelay(1000);                                      

  if (millis() > 5000 && gps.charsProcessed() < 10)
    Serial.println(F("No GPS data received: check wiring"));

  Serial.print("Sending packet: ");
  Serial.print("Latitude  : ");
  Serial.println(gps.location.lat(), 5);
  Serial.print("Longitude : ");
  Serial.println(gps.location.lng(), 4);
  Serial.print("Satellites: ");
  Serial.println(gps.satellites.value());

  // send packet
  LoRa.beginPacket();
  LoRa.print("Node: ");
  LoRa.print(2);
  LoRa.print("Latitude  : ");
  LoRa.print(gps.location.lat(), 5);
  LoRa.print("Longitude  : ");
  LoRa.print(gps.location.lng(), 4);
  LoRa.print("Satellites: ");
  LoRa.print(gps.satellites.value());
  LoRa.endPacket();

  delay(5000);
}

static void smartDelay(unsigned long ms)                
{
  unsigned long start = millis();
  do
  {
    while (Serial1.available())
      gps.encode(Serial1.read());
  } while (millis() - start < ms);
}