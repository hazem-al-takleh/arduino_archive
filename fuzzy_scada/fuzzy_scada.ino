#define lightSensor A0
int lightState = 0;

#include "DHT.h"
#define DHTPIN 2     // Digital pin connected to the DHT sensor
#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
DHT dht(DHTPIN, DHTTYPE);

#include "CO2Sensor.h"  
#define CO2Sens A0
int CO2Val = 0;
CO2Sensor co2Sensor(CO2Sens, 0.99, 100);

#define relay1 4
#define relay2 5
#define relay3 6
#define relay4 7

void setup() {
  Serial.begin(9600);
  dht.begin();
  pinMode(lightSensor, INPUT);
  pinMode(CO2Sens, INPUT);
  pinMode(relay1, OUTPUT);
  pinMode(relay2, OUTPUT);
  pinMode(relay3, OUTPUT);
  pinMode(relay4, OUTPUT);
  digitalWrite(relay1, HIGH);
  digitalWrite(relay2, HIGH);
  digitalWrite(relay3, HIGH);
  digitalWrite(relay4, HIGH);
    
    co2Sensor.calibrate();
}

void loop() {
  if(Serial.available()>0){
    String comc = Serial.readString();
    
    if (comc == "r1 off")
      digitalWrite(relay1, HIGH);
    if (comc == "r1 on")
      digitalWrite(relay1, LOW);

    if (comc == "r2 off")
      digitalWrite(relay2, HIGH);
    if (comc == "r2 on")
      digitalWrite(relay2, LOW);

    if (comc == "r3 off")
      digitalWrite(relay3, HIGH);
    if (comc == "r3 on")
      digitalWrite(relay3, LOW);

    if (comc == "r4 off")
      digitalWrite(relay4, HIGH);
    if (comc == "r4 on")
      digitalWrite(relay4, LOW);

    if (comc == "all r off"){
      digitalWrite(relay1, HIGH);
      digitalWrite(relay2, HIGH);
      digitalWrite(relay3, HIGH);
      digitalWrite(relay4, HIGH);
    }
    if (comc == "all r on"){
      digitalWrite(relay1, LOW);
      digitalWrite(relay2, LOW);
      digitalWrite(relay3, LOW);
      digitalWrite(relay4, LOW);
    }

    if (comc == "init")
      Serial.println("0"); 
      
    if (comc == "co2"){
      int CO2Val = co2Sensor.read();
      Serial.println(CO2Val);  
    }

    if (comc == "temp"){
      int t = dht.readTemperature();
      Serial.println(t);  
    }

    if (comc == "hum"){
      int h = dht.readHumidity();
      Serial.println(h);  
    }

    if (comc == "light"){
      lightState = analogRead(lightSensor);
      if(lightState > 1000)
        Serial.println("0");
      else
        Serial.println("1");
    }
      
  }
}
