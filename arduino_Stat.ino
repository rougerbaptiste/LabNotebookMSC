// Example testing sketch for various DHT humidity/temperature sensors
// Written by ladyada, public domain

#include "DHT.h"
#include <Adafruit_Sensor.h>
#include <Time.h>

#define DHTPIN 3     // what pin we're connected to
#define RELTEMP 4 // relai 1 est connecte a pin 4
#define RELHUM 5 // relai 2 est connecté a pin 5
#define RELLAMP1 6 // relai 3 est connecté a pin 6
#define RELLAMP2 7 // relai 4 est connecté a pin 7
#define RELEXTRA 8 // relai 4 est connecté a pin 8


#define DHTTYPE DHT22   // DHT 22  (AM2302)

// Initialize DHT sensor for normal 16mhz Arduino
DHT dht(DHTPIN, DHTTYPE);


void setup() {
  Serial.begin(9600); 
  Serial.println("DHTxx test!");

  pinMode(RELTEMP, OUTPUT);
  digitalWrite(RELTEMP, LOW);

  pinMode(RELHUM, OUTPUT);
  digitalWrite(RELHUM, LOW);

  pinMode(RELLAMP1, OUTPUT);
  digitalWrite(RELLAMP1, HIGH);

  pinMode(RELLAMP2, OUTPUT);
  digitalWrite(RELLAMP2, HIGH);

  setTime(13,29,30,29,01,2018);
 
  dht.begin();
}



void loop() {
  // Wait a few seconds between measurements.
  // delay(30000); // En ms
  time_t time = now();

  if (second(time)%1 == 0) { //// This will need to be change to minute
    float h = dht.readHumidity();
    float t = dht.readTemperature();

    if (t <= 25 and minute(time)%5==0) {
      digitalWrite(RELTEMP, LOW);
    }
    else {
      digitalWrite(RELTEMP, HIGH);
    }

    if (h <= 60 and minute(time)%5==0) {
      digitalWrite(RELHUM, LOW);
    }
    else {
      digitalWrite(RELHUM, HIGH);
    }

    
  }

  if (hour(time) > 7 and hour(time) < 20) { // Pour la lampe 1, on veut entre 8 et 20h
    digitalWrite(RELLAMP1, LOW);
//    Serial.println("Light");
  }
  else {
    digitalWrite(RELLAMP1, HIGH);
//    Serial.println("No Light");
  }

  if (hour(time) > 7 and hour(time) < 20) { // Pour la lampe 2, on veut entre 8 et 20h
    digitalWrite(RELLAMP2, LOW);
//    Serial.println("Light2");
  }
  else {
    digitalWrite(RELLAMP2, HIGH);
//    Serial.println("No Light2");
  }

  
  
//  // Check if any reads failed and exit early (to try again).
//  if (isnan(h) || isnan(t)) {
//    Serial.println("Failed to read from DHT sensor!");
//    return;
//  }
//
//  if (t >= 25) {
//    digitalWrite(REL1, HIGH); //On allume le relai
//    delay(1000);
//    digitalWrite(REL1, LOW); //On éteint le relai
//    delay(2000);
//  }
//  else {
//    delay(3000);
//  }
//  digitalWrite(REL1, HIGH); //On allume le relai
//  delay(1000);
//  digitalWrite(REL1, LOW); //On éteint le relai
//  delay(2000);
////
//  time_t time = now();
  Serial.print(hour(time));
  Serial.print(":");
  Serial.print(minute());
  Serial.print(":");
  Serial.println(second());
////  
//  float h = dht.readHumidity();
//  float t = dht.readTemperature();
//  Serial.print(h);
//  Serial.print(" ");
//  Serial.println(t);

  delay(1000);
}
