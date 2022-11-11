

void setup() {
  Serial.begin(9600);

}

void loop() {
  if(Serial.available()>0){
    char distanceString = Serial.read();
    distance = int(distanceString);
  }
  // your code
}
