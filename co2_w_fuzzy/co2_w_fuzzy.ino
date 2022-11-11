#include <Fuzzy.h>
Fuzzy *fuzzy = new Fuzzy();

#include "CO2Sensor.h"  
CO2Sensor co2Sensor(A0, 0.99, 100);

void setup() {
  Serial.begin(9600);
  pinMode(A0, INPUT);
  co2Sensor.calibrate();
  
  FuzzyInput *co2ppm = new FuzzyInput(1);
  FuzzySet *low = new FuzzySet(0, 0, 300, 400);
  co2ppm->addFuzzySet(low);
  FuzzySet *high = new FuzzySet(300, 400, 500, 500);
  co2ppm->addFuzzySet(high);
  fuzzy->addFuzzyInput(co2ppm);

  FuzzyOutput *co2tox = new FuzzyOutput(1);
  FuzzySet *safe = new FuzzySet(0, 10, 10, 20);
  co2tox->addFuzzySet(safe);
  FuzzySet *dan = new FuzzySet(10, 20, 30, 40);
  co2tox->addFuzzySet(dan);
  fuzzy->addFuzzyOutput(co2tox);

  // Building FuzzyRule "IF distance = small THEN speed = slow"
  // Instantiating a FuzzyRuleAntecedent objects
  FuzzyRuleAntecedent *ifCO2Low = new FuzzyRuleAntecedent();
  // Creating a FuzzyRuleAntecedent with just a single FuzzySet
  ifCO2Low->joinSingle(low);
  // Instantiating a FuzzyRuleConsequent objects
  FuzzyRuleConsequent *thenRoomSafe = new FuzzyRuleConsequent();
  // Including a FuzzySet to this FuzzyRuleConsequent
  thenRoomSafe->addOutput(safe);
  // Instantiating a FuzzyRule objects
  FuzzyRule *fuzzyRule01 = new FuzzyRule(1, ifCO2Low, thenRoomSafe);
  // Including the FuzzyRule into Fuzzy
  fuzzy->addFuzzyRule(fuzzyRule01);

  // Building FuzzyRule "IF distance = small THEN speed = slow"
  // Instantiating a FuzzyRuleAntecedent objects
  FuzzyRuleAntecedent *ifCO2High = new FuzzyRuleAntecedent();
  // Creating a FuzzyRuleAntecedent with just a single FuzzySet
  ifCO2Low->joinSingle(high);
  // Instantiating a FuzzyRuleConsequent objects
  FuzzyRuleConsequent *thenRoomDan = new FuzzyRuleConsequent();
  // Including a FuzzySet to this FuzzyRuleConsequent
  thenRoomDan->addOutput(dan);
  // Instantiating a FuzzyRule objects
  FuzzyRule *fuzzyRule02 = new FuzzyRule(2, ifCO2High, thenRoomDan);
  // Including the FuzzyRule into Fuzzy
  fuzzy->addFuzzyRule(fuzzyRule02);
}

void loop() {
  int CO2val = co2Sensor.read();
  Serial.print("CO2 ppm: ");
  Serial.print(CO2val);
  fuzzy->setInput(1, CO2val);
  // Running the Fuzzification
  fuzzy->fuzzify();
  // Running the Defuzzification
  float output = fuzzy->defuzzify(1);
  // Printing something
  Serial.print("\tRoom safe: ");
  Serial.println(output);
  delay(5000);

}
