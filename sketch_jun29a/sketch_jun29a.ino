#include "CO2Sensor.h"
CO2Sensor co2Sensor(A0, 0.99, 100);

void setup() {
  Serial.begin(9600);
  pinMode(A0, INPUT);
  
  co2Sensor.calibrate();
}

void loop() {
  int CO2Val = co2Sensor.read();
  Serial.println(CO2Val);
}
