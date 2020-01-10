#include <Fuzzy.h>
#include<LiquidCrystal_I2C_Hangul.h>
#include<Wire.h>

LiquidCrystal_I2C_Hangul lcd(0x3F, 16, 2); //LCD 클래스 초기화

int trig1 = 2, trig2 = 3, trig3 = 4;
int echo1 = 5, echo2 = 6, echo3 = 7;
float dist1, dist2, dist3, duration1, duration2, duration3;

int m1 = 47, m2 = 45, m3 = 43, m4 = 41;
int enable1 = 44, enable2 = 46;

// Instantiating a Fuzzy object
Fuzzy *fuzzy = new Fuzzy();

void setup()
{
  // Set the Serial output
  Serial.begin(9600);
  pinMode(trig1, OUTPUT);
  pinMode(trig2, OUTPUT);
  pinMode(trig3, OUTPUT);
  pinMode(echo1, INPUT);
  pinMode(echo2, INPUT);
  pinMode(echo3, INPUT);

  pinMode(m1, OUTPUT);
  pinMode(m2, OUTPUT);
  pinMode(m3, OUTPUT);
  pinMode(m4, OUTPUT);
  pinMode(enable1, OUTPUT);
  pinMode(enable2, OUTPUT);

  lcd.init();
  lcd.backlight();

  // Instantiating a FuzzyInput object
  FuzzyInput *distance = new FuzzyInput(1);
  // Instantiating a FuzzySet object
  FuzzySet *small = new FuzzySet(0, 20, 20, 50);
  // Including the FuzzySet into FuzzyInput
  distance->addFuzzySet(small);
  // Instantiating a FuzzySet object
  FuzzySet *safe = new FuzzySet(40, 60, 60, 90);
  // Including the FuzzySet into FuzzyInput
  distance->addFuzzySet(safe);
  // Instantiating a FuzzySet object
  FuzzySet *big = new FuzzySet(80, 100, 100, 150);
  // Including the FuzzySet into FuzzyInput
  distance->addFuzzySet(big);
  // Including the FuzzyInput into Fuzzy
  fuzzy->addFuzzyInput(distance);

  // Instantiating a FuzzyOutput objects
  FuzzyOutput *speed = new FuzzyOutput(1);
  // Instantiating a FuzzySet object
  FuzzySet *slow = new FuzzySet(0, 50, 50, 70);
  // Including the FuzzySet into FuzzyOutput
  speed->addFuzzySet(slow);
  // Instantiating a FuzzySet object
  FuzzySet *average = new FuzzySet(50, 70, 70, 100);
  // Including the FuzzySet into FuzzyOutput
  speed->addFuzzySet(average);
  // Instantiating a FuzzySet object
  FuzzySet *fast = new FuzzySet(90, 110, 110, 150);
  // Including the FuzzySet into FuzzyOutput
  speed->addFuzzySet(fast);
  // Including the FuzzyOutput into Fuzzy
  fuzzy->addFuzzyOutput(speed);

  // Building FuzzyRule "IF distance = small THEN speed = slow"
  // Instantiating a FuzzyRuleAntecedent objects
  FuzzyRuleAntecedent *ifDistanceSmall = new FuzzyRuleAntecedent();
  // Creating a FuzzyRuleAntecedent with just a single FuzzySet
  ifDistanceSmall->joinSingle(small);
  // Instantiating a FuzzyRuleConsequent objects
  FuzzyRuleConsequent *thenSpeedSlow = new FuzzyRuleConsequent();
  // Including a FuzzySet to this FuzzyRuleConsequent
  thenSpeedSlow->addOutput(slow);
  // Instantiating a FuzzyRule objects
  FuzzyRule *fuzzyRule01 = new FuzzyRule(1, ifDistanceSmall, thenSpeedSlow);
  // Including the FuzzyRule into Fuzzy
  fuzzy->addFuzzyRule(fuzzyRule01);

  // Building FuzzyRule "IF distance = safe THEN speed = average"
  // Instantiating a FuzzyRuleAntecedent objects
  FuzzyRuleAntecedent *ifDistanceSafe = new FuzzyRuleAntecedent();
  // Creating a FuzzyRuleAntecedent with just a single FuzzySet
  ifDistanceSafe->joinSingle(safe);
  // Instantiating a FuzzyRuleConsequent objects 
  FuzzyRuleConsequent *thenSpeedAverage = new FuzzyRuleConsequent();
  // Including a FuzzySet to this FuzzyRuleConsequent
  thenSpeedAverage->addOutput(average);
  // Instantiating a FuzzyRule objects
  FuzzyRule *fuzzyRule02 = new FuzzyRule(2, ifDistanceSafe, thenSpeedAverage);
  // Including the FuzzyRule into Fuzzy
  fuzzy->addFuzzyRule(fuzzyRule02);

  // Building FuzzyRule "IF distance = big THEN speed = high"
  // Instantiating a FuzzyRuleAntecedent objects
  FuzzyRuleAntecedent *ifDistanceBig = new FuzzyRuleAntecedent();
  // Creating a FuzzyRuleAntecedent with just a single FuzzySet
  ifDistanceBig->joinSingle(big);
  // Instantiating a FuzzyRuleConsequent objects
  FuzzyRuleConsequent *thenSpeedFast = new FuzzyRuleConsequent();
  // Including a FuzzySet to this FuzzyRuleConsequent
  thenSpeedFast->addOutput(fast);
  // Instantiating a FuzzyRule objects
  FuzzyRule *fuzzyRule03 = new FuzzyRule(3, ifDistanceBig, thenSpeedFast);
  // Including the FuzzyRule into Fuzzy
  fuzzy->addFuzzyRule(fuzzyRule03);
}

void loop()
{
  // Getting a random value
  int input = random(1, 200);

  dist2 = aKwarAway(trig2, echo2);

  //  Serial.println("\n\n\nEntrance: ");
  //  Serial.print("\t\t\tDistance: ");
  //  Serial.println(dist2);

  // Set the random value as an input
  fuzzy->setInput(1, dist2);
  // Running the Fuzzification
  fuzzy->fuzzify();
  // Running the Defuzzification
  float output = fuzzy->defuzzify(1);
  DriveCar((int)output);
  
  // Printing something
  //  Serial.println("Result: ");
  //  Serial.print("\t\t\tSpeed: ");
  //  Serial.println(output);

  lcd.print(dist2);
  lcd.setCursor(0, 1);
  lcd.print(output);
  // wait 12 seconds
}

float aKwarAway(int Tx, int Rx)
{
  float distance = 0;
  float duration;
  digitalWrite(Tx, LOW);
  delayMicroseconds(2);
  digitalWrite(Tx, HIGH);
  delayMicroseconds(5);

  duration = pulseIn(Rx, HIGH);
  distance = (duration / 2) / 28.57;
  return distance;
}

void DriveCar(int Speed)
{
  digitalWrite(m1, 1);
  digitalWrite(m2, 0);
  digitalWrite(m3, 0);
  digitalWrite(m4, 1);
  analogWrite(enable2, Speed);
  analogWrite(enable1, Speed);
}
