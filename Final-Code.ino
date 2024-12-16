//https://github.com/zakirahmedzas
//DROBAN

// For blynk App
#define BLYNK_PRINT Serial
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
char auth[] = "kvLp1lIXncXkx6c_3jG8qTSJMQZZzWgi";
char ssid[] = "DIPF_Guest";
char pass[] = "Dipfoundation";

// For DHT22 Sensor
#include <DHT.h>
#define DHT22_PIN  18 // ESP32 pin GPIO21 connected to DHT22 sensor
DHT dht22(DHT22_PIN, DHT22);

// For DS18B20 Sensor
#include <OneWire.h>
#include <DallasTemperature.h>
#define ONE_WIRE_BUS 5
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

void setup() {
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);
  dht22.begin(); // For DHT22 Sensor
  sensors.begin(); // For DS18b20 Sensor
  
  
}

void loop() {
Blynk.run();

  // For DHT22 Sensor
  float humi  = dht22.readHumidity();
  // read temperature in Celsius
  float tempR = dht22.readTemperature();
  Serial.print("Hum: ");
  Serial.print(humi);
  Serial.print("%");
  Serial.print("  ");
  Serial.print("TempR: ");
  Serial.print(tempR);
  Serial.println("°C  ~  ");
  Blynk.virtualWrite(V3, humi);
  Blynk.virtualWrite(V4, tempR);

  // For DS18B20 Sensor
  sensors.requestTemperatures(); // Send the command to get temperatures
  float tempB = sensors.getTempCByIndex(0);
  Serial.print("TempB: ");
  Serial.println(tempB);
  Blynk.virtualWrite(V5, tempB);
}
