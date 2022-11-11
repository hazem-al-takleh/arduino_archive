#include "DHT.h"
  
//  DHT object
#define DHTPIN 27    // Digital pin connected to the DHT sensor
#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
DHT dht(DHTPIN, DHTTYPE);

//  analog pins of the sensors
#define co2_pin 26
#define relay1
#define relay2
#define relay3
#define relay4

int co2_val = 0;
int temp_val = 0;
int humidity_val = 0;

void setup() {
  Serial.begin(115200);
  dht.begin();
  pinMode(relay1, OUTPUT);
  pinMode(relay2, OUTPUT);
  pinMode(relay3, OUTPUT);
  pinMode(relay4, OUTPUT);  
}

void loop() {
  //  data acquisition
  co2_val = analogRead(co_pin);
  temp_val = dht.readTemperature();
  humidity_val = dht.readHumidity();  
  
  //  converting data to strings (text) to send them through HTTP
  String co2_str = String(co_val, DEC);
  String temp_str =  String(temp_val, DEC);
  String humidity_str =  String(humidity_val, DEC);

  //  printing the sensor values to the serial monitor for debugging means
  String sens_vals = "CO2 PPM = " + co2_str +"\nTemperature = " + temp_str + " C\nHumidity = " + humidity_str + " %";

  Serial.println(sens_vals);
  Serial.println("-----------------------");

  delay(5000);
}
