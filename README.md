# LoRaWAN Examples

Simple and basic examples to test LoRa/LoraWAN functionality on ESP32 sensor nodes. Examples were compiled while surfing on the web.

## Sketches:


- lora-receiver: receives messages over lora (not lorawan).
- lora-sender: sends messages over lora (not lorawan).
- lora-sender-gps: sends a messages with gps data over lora.
- lorawan-node-test: implementation of a LoRa/LoRaWAN node with configuration and transmission of GPS data. **Requires /src/config.h file for TTN connection**.
- ttn-server-client-test: nodejs server that connects to ttn app and receives and saves lorawan packets to mongodb.


