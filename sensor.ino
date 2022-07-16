#include <dht.h>/* Change these values based on your calibration values */
#define soilWet 500   // Define max value we consider soil 'wet'
#define soilDry 750   // Define min value we consider soil 'dry'
#define dht_apin A1

// Sensor pins
#define sensorPower 5
#define sensorPin A0
int motorPin = 8;


dht DHT;
float mois_percent;
int ledPin1 = 11;//red
int ledPin2 = 12;//yellow
int ledPin3 = 13;//green
void setup() {
   pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin3, OUTPUT);
  pinMode(sensorPower, OUTPUT);
 
  // Initially keep the sensor OFF
  digitalWrite(sensorPower, LOW);
 
  pinMode(motorPin, OUTPUT);
  digitalWrite(motorPin, LOW);
 
 
  Serial.begin(9600);
  delay(1000);
}

void loop() {
  //get the reading from the function below and print it
  int moisture = readSensor();
   Serial.print("Analog Output(moisture): ");
   Serial.println(moisture);

   mois_percent = map(moisture,1023,681,0,100);
   

  // Determine status of our soil
  if (moisture < soilWet) {
    Serial.println("Status: Soil is too wet");
    digitalWrite(motorPin,HIGH);
    digitalWrite(ledPin1,LOW);
   
    Serial.println("PUMP IS OFF");
    delay(1000);
  } else if (moisture >= soilWet && moisture < soilDry) {
    Serial.println("Status: Soil moisture is perfect");
   
    digitalWrite(motorPin,HIGH);
    digitalWrite(ledPin1,LOW);
   
    Serial.println("Pump is OFF");
    delay(1000);
  } else {
   
    Serial.println("Status: Soil is too dry - time to water!");
    digitalWrite(motorPin,LOW);
   
    digitalWrite(ledPin1,HIGH);
   
    Serial.println("Pump is ON");
    delay(1000);
   
  }
//Serial.println("DHT11 Humidity & temperature Sensor\n");
    DHT.read11(dht_apin);
   
    Serial.print("*Current humidity = ");
    Serial.print(DHT.humidity);
    Serial.print("%  ");
    Serial.print("*Temperature = ");
    Serial.print(DHT.temperature);
    Serial.println("°C");
  if(DHT.humidity>=60&&DHT.humidity <=80)
  {
    Serial.println("Humidity is optimum");
  }
  else if(DHT.humidity<60)
  {
    Serial.println("Humidity is low ");
  }
  else
  {
   Serial.println("Humidity is high ");
  }
 
  if(DHT.temperature>=21&&DHT.temperature<=37)
  {
    Serial.println("Temperature is optimum ");
   
   
  }
  else if(DHT.temperature<21)
  {
    Serial.println("Temperature is less ");
   
    digitalWrite(ledPin2,HIGH);
   
  }
  else
  {
    Serial.println("Temperature is high !!! It's time to water your field !");
    digitalWrite(motorPin,LOW);
    delay(1000);
   
    digitalWrite(ledPin2,HIGH);
  }
  if((DHT.temperature>=21&&DHT.temperature<=37)&&(moisture >= soilWet && moisture < soilDry)&&(DHT.humidity>=60&&DHT.humidity <=80))
  {
    digitalWrite(ledPin3,HIGH);
   
  }
  else
  {
    digitalWrite(ledPin3,LOW);
  }
  Serial.println("_");
  delay(1000);  // Take a reading every second for testing
          // Normally you should take reading perhaps once or twice a day
  Serial.println("");
}

 


//  This function returns the analog soil moisture measurement
int readSensor() {
  digitalWrite(sensorPower, HIGH);  // Turn the sensor ON
  delay(10);              // Allow power to settle
  int val = analogRead(sensorPin);  // Read the analog value form sensor
  digitalWrite(sensorPower, LOW);   // Turn the sensor OFF
  return val;             // Return analog moisture value
}
