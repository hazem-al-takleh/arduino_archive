#define gas_sensor A5
#define flame_sensor A4
#define fan 3

int gas_value = 0;
int flame_value = 0;

void setup() {
  Serial.begin(9600);
  pinMode(gas_sensor, INPUT);
  pinMode(flame_sensor, INPUT);
  pinMode(fan, OUTPUT);
}

void loop() {
  if (Serial.available()>0){
    char c = Serial.read();
    if (c == '0'){
      analogWrite(fan, 0);
    }
    else if (c == '1'){
      analogWrite(fan, 127);
    }
     else if (c == '2'){
      analogWrite(fan, 255);
    }
    else if (c == '3'){
      gas_value = analogRead(gas_sensor);
      flame_value  = analogRead(flame_sensor);
      
      Serial.print("gas value: ");
      Serial.print(gas_value);
      Serial.print(",flame value: ");
      Serial.print(flame_value);
    }
    else if (c == '4'){
      gas_value = analogRead(gas_sensor);
      flame_value  = analogRead(flame_sensor);
        if (gas_value > 100 || flame_value < 100) {
        digitalWrite(fan, HIGH);
      }
      else{
      digitalWrite(fan,LOW);
      }
      delay(200);
    }
  }
}
