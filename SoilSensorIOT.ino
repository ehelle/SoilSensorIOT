#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <dht11.h>

const int soilSensorPin = 0;
const int soilSensorVCC = 13;
int soilSensorValue = 0;

dht11 DHT11;
const int dht11pin = 2;

const int sensorIdle = 5000;

#include "params.h"

const char* ssid = _SSID;
const char* password = _PASSWORD;
const char* mqtt_server = _MQTT_SERVER;
const int mqtt_port = _MQTT_PORT;
const char* mqtt_usr = _MQTT_USER;
const char* mqtt_pwd = _MQTT_PASSWORD;

WiFiClient espClient;
PubSubClient client(espClient);
char msg[50];

void setup_wifi() {
  
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void setup() {
   Serial.begin(115200);  
   pinMode(soilSensorVCC, OUTPUT); 
   digitalWrite(soilSensorVCC, LOW);
   setup_wifi();
   client.setServer(mqtt_server, mqtt_port);
}

int i = 0;
void loop() {
  
  digitalWrite(soilSensorVCC, HIGH);
  delay(100); // make sure soilSensor is powered
  soilSensorValue = analogRead(soilSensorPin); 
  digitalWrite(soilSensorVCC, LOW);  
  Serial.print("Soil sensor: " );                       
  Serial.println(soilSensorValue);
  
  
  int chk = DHT11.read(dht11pin);
  
  switch (chk)
  {
    case DHTLIB_OK: 
      Serial.print("Humidity (%): ");
      Serial.println(DHT11.humidity);
      Serial.print("Temperature (°C): ");
      Serial.println(DHT11.temperature);
      break;
    default: 
      Serial.println("Unknown error"); 
      break;
  }

  if (client.connect("soilsensor001", mqtt_usr, mqtt_pwd)) {
    client.publish("hello/world", "Hello from esp8266 - times: " + i);
  }
  
  delay(sensorIdle);  
}
