#include "DHT.h"
#define DHTPIN 2
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,20,4);

void setup() {
  Serial.begin(9600);
  dht.begin();
  lcd.init();
  lcd.backlight();
}

void loop() {
  int lux = analogRead(A0);
  if ( lux >1000){
    lcd.setCursor(0,0);
    lcd.print("Light: off");
  }
  else{
    lcd.setCursor(0,0);
    lcd.print("Light: on");
  }

  float h = dht.readHumidity();
  float t = dht.readTemperature();

  lcd.setCursor(0,1);
  lcd.print("Humidity: ");
  lcd.print(h);
    
  lcd.setCursor(0,2);
  lcd.print("Temp: ");
  lcd.print(t);
  delay(2000);
  lcd.clear();

  if (Serial.available()>0){
    char c = Serial.read();

    // send humidity value
    if (c == '1'){
      Serial.println(h);
    }
    // send temp value
    else if (c == '2'){
      Serial.println(t);
    }
    // send light state
    else if (c == '3'){
      if ( lux >1000){
        Serial.println("0");
      }
      else{
        Serial.println("1"); 
      }
    }
  }
  
}
