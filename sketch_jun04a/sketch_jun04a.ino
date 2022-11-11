void setup() {
  

}

void loop() {
  Serial.begin(9600);
  if (Serial.available()>0){
    char c = Serial.read();
    
    if (c == '1'){
      digitalWrite(LED_BUILTIN, HIGH);
    }
    else{
      digitalWrite(LED_BUILTIN, LOW);
    }
    Serial.end();
  }
  delay(100);
}
