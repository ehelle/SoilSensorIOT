#include <dht11.h>

int soilSensorPin = 0;
int soilSensorValue = 0;
int soilSensorVCC = 13;

dht11 DHT11;

int dht11pin = 2;

int sensorIdle = 5000;
 
void setup() {
   Serial.begin(9600);  
   pinMode(soilSensorVCC, OUTPUT); 
   digitalWrite(soilSensorVCC, LOW);
}
 
void loop() {
  
  digitalWrite(soilSensorVCC, HIGH);
  delay(100); // make sure soilSensor is powered
  soilSensorValue = analogRead(soilSensorPin); 
  digitalWrite(soilSensorVCC, LOW);  
  Serial.print("sensor = " );                       
  Serial.println(soilSensorValue);
  
  
  int chk = DHT11.read(DHT11PIN);

  Serial.print("Read sensor: ");
  switch (chk)
  {
    case DHTLIB_OK: 
		Serial.println("OK"); 
		break;
    case DHTLIB_ERROR_CHECKSUM: 
		Serial.println("Checksum error"); 
		break;
    case DHTLIB_ERROR_TIMEOUT: 
		Serial.println("Time out error"); 
		break;
    default: 
		Serial.println("Unknown error"); 
		break;
  }

  Serial.print("Humidity (%): ");
  Serial.println((float)DHT11.humidity, 2);

  Serial.print("Temperature (°C): ");
  Serial.println((float)DHT11.temperature, 2);
  
  delay(sensorIdle);  
}
