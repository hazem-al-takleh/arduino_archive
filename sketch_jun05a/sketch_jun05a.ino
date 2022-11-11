#include "DHT.h"
#define DHTPIN 2
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);

#define led 4

void setup() {
  pinMode(led, OUTPUT);
  Serial.begin(9600);
  dht.begin();
  lcd.init();
  lcd.backlight();
}

void loop() {
  int x = analogRead(A0);
  if ( x >1020){
    
    digitalWrite( led, HIGH);
    lcd.setCursor(0,0);
    lcd.print("Light: No");
    delay(1000);
    lcd.clear();
  }
  else{
    digitalWrite( led, LOW);
    lcd.setCursor(0,0);
    lcd.print("Light: Yes");
    delay(1000);
    lcd.clear();
  }

  float h = dht.readHumidity();
  float t = dht.readTemperature();

  lcd.setCursor(0,0);
  lcd.print("Humidity: ");
  lcd.print(h);
    
  lcd.setCursor(0,1);
  lcd.print("Temp: ");
  lcd.print(t);
  delay(1000);
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
      if ( x >1020){
        Serial.println("1");
      }
      else{
        Serial.println("0"); 
      }
    }
  }
  
}
