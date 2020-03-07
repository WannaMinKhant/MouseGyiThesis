#include <Fuzzy.h>

// For scope, instantiate all objects you will need to access in loop()
// It may be just one Fuzzy, but for demonstration, this sample will print
// all FuzzySet pertinence

// Fuzzy
Fuzzy *fuzzy = new Fuzzy();

// FuzzyInput
FuzzySet *near = new FuzzySet(0, 0, 40, 60);
FuzzySet *safe = new FuzzySet(50, 60, 60, 70);
FuzzySet *far = new FuzzySet(60, 80, 200, 200);

FuzzySet *near1 = new FuzzySet(0, 0, 40, 60);
FuzzySet *safe1 = new FuzzySet(50, 60, 60, 70);
FuzzySet *far1 = new FuzzySet(60, 80, 200, 200);

FuzzySet *near2 = new FuzzySet(0, 0, 40, 60);
FuzzySet *safe2 = new FuzzySet(50, 60, 60, 70);
FuzzySet *far2 = new FuzzySet(60, 80, 200, 200);


// FuzzyOutput
FuzzySet *verylow = new FuzzySet(40, 60, 60, 80);
FuzzySet *low = new FuzzySet(60, 80, 80, 100);
FuzzySet *medium = new FuzzySet(80, 100, 100, 120);
FuzzySet *big = new FuzzySet(100, 125, 125, 150);
FuzzySet *verybig = new FuzzySet(125, 163, 163, 200);

FuzzySet *verylow1 = new FuzzySet(40, 60, 60, 80);
FuzzySet *low1 = new FuzzySet(60, 80, 80, 100);
FuzzySet *medium1 = new FuzzySet(80, 100, 100, 120);
FuzzySet *big1 = new FuzzySet(100, 125, 125, 150);
FuzzySet *verybig1 = new FuzzySet(125, 163, 163, 200);


int trig1 = 2, trig2 = 3, trig3 = 4;
int echo1 = 8, echo2 = 9, echo3 = 10;
float dist1, dist2, dist3, duration1, duration2, duration3;

int m1 = 40, m2 = 42, m3 = 43, m4 = 41;
int enable1 = 44, enable2 = 46;



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

  // Every setup must occur in the function setup()

  // FuzzyInput
  FuzzyInput *distance = new FuzzyInput(1);
  FuzzyInput *distance1 = new FuzzyInput(2);
  FuzzyInput *distance2 = new FuzzyInput(3);

  distance->addFuzzySet(near);
  distance->addFuzzySet(safe);
  distance->addFuzzySet(far);
  fuzzy->addFuzzyInput(distance);

  distance1->addFuzzySet(near1);
  distance1->addFuzzySet(safe1);
  distance1->addFuzzySet(far1);
  fuzzy->addFuzzyInput(distance1);

  distance2->addFuzzySet(near2);
  distance2->addFuzzySet(safe2);
  distance2->addFuzzySet(far2);
  fuzzy->addFuzzyInput(distance2);


  // FuzzyOutput
  FuzzyOutput *left = new FuzzyOutput(1);
  left->addFuzzySet(verylow);
  left->addFuzzySet(low);
  left->addFuzzySet(medium);
  left->addFuzzySet(big);
  left->addFuzzySet(verybig);
  fuzzy->addFuzzyOutput(left);

  FuzzyOutput *right = new FuzzyOutput(2);
  right->addFuzzySet(verylow1);
  right->addFuzzySet(low1);
  right->addFuzzySet(medium1);
  right->addFuzzySet(big1);
  right->addFuzzySet(verybig1);
  fuzzy->addFuzzyOutput(right);

  // Building FuzzyRule
  FuzzyRuleAntecedent *distanceNearAnddistance1Near = new FuzzyRuleAntecedent();
  distanceNearAnddistance1Near->joinWithAND(near, near1);
  FuzzyRuleAntecedent *distance2Near = new FuzzyRuleAntecedent();
  distance2Near->joinSingle(near2);
  FuzzyRuleAntecedent *ifdistanceNearAnddistance1NearAnddistace2Near = new FuzzyRuleAntecedent();
  ifdistanceNearAnddistance1NearAnddistace2Near->joinWithAND(distanceNearAnddistance1Near, distance2Near);
  FuzzyRuleConsequent *thenLeftandRightVeryLow = new FuzzyRuleConsequent();
  thenLeftandRightVeryLow->addOutput(verylow);
  thenLeftandRightVeryLow->addOutput(medium1);
  FuzzyRule *fuzzyRule1 = new FuzzyRule(1, ifdistanceNearAnddistance1NearAnddistace2Near, thenLeftandRightVeryLow);
  fuzzy->addFuzzyRule(fuzzyRule1);


  FuzzyRuleAntecedent *distance2Meduium = new FuzzyRuleAntecedent();
  distance2Meduium->joinSingle(safe2);
  FuzzyRuleAntecedent *ifdistanceNearAnddistance1NearAnddistace2Medium = new FuzzyRuleAntecedent();
  ifdistanceNearAnddistance1NearAnddistace2Medium->joinWithAND(distanceNearAnddistance1Near, distance2Meduium);
  FuzzyRuleConsequent *thenLeftandRight2 = new FuzzyRuleConsequent();
  thenLeftandRight2->addOutput(medium);
  thenLeftandRight2->addOutput(verylow1);
  FuzzyRule *fuzzyRule2 = new FuzzyRule(2, ifdistanceNearAnddistance1NearAnddistace2Medium, thenLeftandRight2);
  fuzzy->addFuzzyRule(fuzzyRule2);


  FuzzyRuleAntecedent *distance2Far = new FuzzyRuleAntecedent();
  distance2Far->joinSingle(far2);
  FuzzyRuleAntecedent *ifdistanceNearAnddistance1NearAnddistace2Far = new FuzzyRuleAntecedent();
  ifdistanceNearAnddistance1NearAnddistace2Far->joinWithAND(distanceNearAnddistance1Near, distance2Far);
  FuzzyRuleConsequent *thenLeftandRight3 = new FuzzyRuleConsequent();
  thenLeftandRight3->addOutput(medium);
  thenLeftandRight3->addOutput(verylow1);
  FuzzyRule *fuzzyRule3 = new FuzzyRule(3, ifdistanceNearAnddistance1NearAnddistace2Far, thenLeftandRight3);
  fuzzy->addFuzzyRule(fuzzyRule3);

  //
  FuzzyRuleAntecedent *distanceNearAnddistance1Medium = new FuzzyRuleAntecedent();
  distanceNearAnddistance1Medium->joinWithAND(near, safe1);
  FuzzyRuleAntecedent *ifdistanceNearAnddistance1MediumAnddistace2Near = new FuzzyRuleAntecedent();
  ifdistanceNearAnddistance1MediumAnddistace2Near->joinWithAND(distanceNearAnddistance1Medium, distance2Near);

  FuzzyRuleConsequent *thenLeftandRight4 = new FuzzyRuleConsequent();
  thenLeftandRight4->addOutput(low);
  thenLeftandRight4->addOutput(low1);

  FuzzyRule *fuzzyRule4 = new FuzzyRule(4, ifdistanceNearAnddistance1MediumAnddistace2Near, thenLeftandRight4);
  fuzzy->addFuzzyRule(fuzzyRule4);

  FuzzyRuleAntecedent *ifdistanceNearAnddistance1MediumAnddistace2Medium = new FuzzyRuleAntecedent();
  ifdistanceNearAnddistance1MediumAnddistace2Medium->joinWithAND(distanceNearAnddistance1Medium, distance2Meduium);

  FuzzyRuleConsequent *thenLeftandRight5 = new FuzzyRuleConsequent();
  thenLeftandRight5->addOutput(low);
  thenLeftandRight5->addOutput(low1);

  FuzzyRule *fuzzyRule5 = new FuzzyRule(5, ifdistanceNearAnddistance1MediumAnddistace2Medium, thenLeftandRight5);
  fuzzy->addFuzzyRule(fuzzyRule5);

  FuzzyRuleAntecedent *ifdistanceNearAnddistance1MediumAnddistace2Far = new FuzzyRuleAntecedent();
  ifdistanceNearAnddistance1MediumAnddistace2Far->joinWithAND(distanceNearAnddistance1Medium, distance2Far);

  FuzzyRuleConsequent *thenLeftandRight6 = new FuzzyRuleConsequent();
  thenLeftandRight6->addOutput(medium);
  thenLeftandRight6->addOutput(verylow1);

  FuzzyRule *fuzzyRule6 = new FuzzyRule(6, ifdistanceNearAnddistance1MediumAnddistace2Far, thenLeftandRight6);
  fuzzy->addFuzzyRule(fuzzyRule6);


  FuzzyRuleAntecedent *distanceNearAnddistance1Far = new FuzzyRuleAntecedent();
  distanceNearAnddistance1Far->joinWithAND(near, far1);
  FuzzyRuleAntecedent *ifdistanceNearAnddistance1FarAnddistace2Near = new FuzzyRuleAntecedent();
  ifdistanceNearAnddistance1FarAnddistace2Near->joinWithAND(distanceNearAnddistance1Far, distance2Near);

  FuzzyRuleConsequent *thenLeftandRight7 = new FuzzyRuleConsequent();
  thenLeftandRight7->addOutput(medium);
  thenLeftandRight7->addOutput(medium1);

  FuzzyRule *fuzzyRule7 = new FuzzyRule(7, ifdistanceNearAnddistance1FarAnddistace2Near, thenLeftandRight7);
  fuzzy->addFuzzyRule(fuzzyRule7);

  FuzzyRuleAntecedent *ifdistanceNearAnddistance1FarAnddistace2Medium = new FuzzyRuleAntecedent();
  ifdistanceNearAnddistance1FarAnddistace2Medium->joinWithAND(distanceNearAnddistance1Far, distance2Meduium);

  FuzzyRuleConsequent *thenLeftandRight8 = new FuzzyRuleConsequent();
  thenLeftandRight8->addOutput(medium);
  thenLeftandRight8->addOutput(medium1);

  FuzzyRule *fuzzyRule8 = new FuzzyRule(8, ifdistanceNearAnddistance1FarAnddistace2Medium, thenLeftandRight8);
  fuzzy->addFuzzyRule(fuzzyRule8);

  FuzzyRuleAntecedent *ifdistanceNearAnddistance1FarAnddistace2Far = new FuzzyRuleAntecedent();
  ifdistanceNearAnddistance1FarAnddistace2Far->joinWithAND(distanceNearAnddistance1Far, distance2Far);

  FuzzyRuleConsequent *thenLeftandRight9 = new FuzzyRuleConsequent();
  thenLeftandRight9->addOutput(medium);
  thenLeftandRight9->addOutput(verylow1);

  FuzzyRule *fuzzyRule9 = new FuzzyRule(9, ifdistanceNearAnddistance1FarAnddistace2Far, thenLeftandRight9);
  fuzzy->addFuzzyRule(fuzzyRule9);


  FuzzyRuleAntecedent *distanceMediumAnddistance1Near = new FuzzyRuleAntecedent();
  distanceMediumAnddistance1Near->joinWithAND(safe, near1);
  FuzzyRuleAntecedent *ifdistanceMediumAnddistance1NearAnddistace2Near = new FuzzyRuleAntecedent();
  ifdistanceMediumAnddistance1NearAnddistace2Near->joinWithAND(distanceMediumAnddistance1Near, distance2Near);

  FuzzyRuleConsequent *thenLeftandRight10 = new FuzzyRuleConsequent();
  thenLeftandRight10->addOutput(verylow);
  thenLeftandRight10->addOutput(medium1);

  FuzzyRule *fuzzyRule10 = new FuzzyRule(10, ifdistanceMediumAnddistance1NearAnddistace2Near, thenLeftandRight10);
  fuzzy->addFuzzyRule(fuzzyRule10);

  FuzzyRuleAntecedent *ifdistanceMediumAnddistance1NearAnddistace2Medium = new FuzzyRuleAntecedent();
  ifdistanceMediumAnddistance1NearAnddistace2Medium->joinWithAND(distanceMediumAnddistance1Near, distance2Meduium);

  FuzzyRuleConsequent *thenLeftandRight11 = new FuzzyRuleConsequent();
  thenLeftandRight11->addOutput(verylow);
  thenLeftandRight11->addOutput(medium1);

  FuzzyRule *fuzzyRule11 = new FuzzyRule(11, ifdistanceMediumAnddistance1NearAnddistace2Medium, thenLeftandRight11);
  fuzzy->addFuzzyRule(fuzzyRule11);

  FuzzyRuleAntecedent *ifdistanceMediumAnddistance1NearAnddistace2Far = new FuzzyRuleAntecedent();
  ifdistanceMediumAnddistance1NearAnddistace2Far->joinWithAND(distanceMediumAnddistance1Near, distance2Far);

  FuzzyRuleConsequent *thenLeftandRight12 = new FuzzyRuleConsequent();
  thenLeftandRight12->addOutput(medium);
  thenLeftandRight12->addOutput(verylow1);

  FuzzyRule *fuzzyRule12 = new FuzzyRule(12, ifdistanceMediumAnddistance1NearAnddistace2Far, thenLeftandRight12);
  fuzzy->addFuzzyRule(fuzzyRule12);


  FuzzyRuleAntecedent *distanceMediumAnddistance1Medium = new FuzzyRuleAntecedent();
  distanceMediumAnddistance1Medium->joinWithAND(safe, safe1);
  FuzzyRuleAntecedent *ifdistanceMediumAnddistance1MediumAnddistace2Near = new FuzzyRuleAntecedent();
  ifdistanceMediumAnddistance1MediumAnddistace2Near->joinWithAND(distanceMediumAnddistance1Medium, distance2Near);

  FuzzyRuleConsequent *thenLeftandRight13 = new FuzzyRuleConsequent();
  thenLeftandRight13->addOutput(low);
  thenLeftandRight13->addOutput(low1);

  FuzzyRule *fuzzyRule13 = new FuzzyRule(13, ifdistanceMediumAnddistance1MediumAnddistace2Near, thenLeftandRight13);
  fuzzy->addFuzzyRule(fuzzyRule13);

  FuzzyRuleAntecedent *ifdistanceMediumAnddistance1MediumAnddistace2Medium = new FuzzyRuleAntecedent();
  ifdistanceMediumAnddistance1MediumAnddistace2Medium->joinWithAND(distanceMediumAnddistance1Medium, distance2Meduium);

  FuzzyRuleConsequent *thenLeftandRight14 = new FuzzyRuleConsequent();
  thenLeftandRight14->addOutput(medium);
  thenLeftandRight14->addOutput(medium1);

  FuzzyRule *fuzzyRule14 = new FuzzyRule(14, ifdistanceMediumAnddistance1MediumAnddistace2Medium, thenLeftandRight14);
  fuzzy->addFuzzyRule(fuzzyRule14);

  FuzzyRuleAntecedent *ifdistanceMediumAnddistance1MediumAnddistace2Far = new FuzzyRuleAntecedent();
  ifdistanceMediumAnddistance1MediumAnddistace2Far->joinWithAND(distanceMediumAnddistance1Medium, distance2Far);

  FuzzyRuleConsequent *thenLeftandRight15 = new FuzzyRuleConsequent();
  thenLeftandRight15->addOutput(big);
  thenLeftandRight15->addOutput(low1);

  FuzzyRule *fuzzyRule15 = new FuzzyRule(15, ifdistanceMediumAnddistance1MediumAnddistace2Far, thenLeftandRight15);
  fuzzy->addFuzzyRule(fuzzyRule15);

  FuzzyRuleAntecedent *distanceMediumAnddistance1Far = new FuzzyRuleAntecedent();
  distanceMediumAnddistance1Far->joinWithAND(safe, far1);
  FuzzyRuleAntecedent *ifdistanceMediumAnddistance1FarAnddistace2Near = new FuzzyRuleAntecedent();
  ifdistanceMediumAnddistance1FarAnddistace2Near->joinWithAND(distanceMediumAnddistance1Far, distance2Near);

  FuzzyRuleConsequent *thenLeftandRight16 = new FuzzyRuleConsequent();
  thenLeftandRight16->addOutput(medium);
  thenLeftandRight16->addOutput(medium1);

  FuzzyRule *fuzzyRule16 = new FuzzyRule(16, ifdistanceMediumAnddistance1FarAnddistace2Near, thenLeftandRight16);
  fuzzy->addFuzzyRule(fuzzyRule16);

  FuzzyRuleAntecedent *ifdistanceMediumAnddistance1FarAnddistace2Medium = new FuzzyRuleAntecedent();
  ifdistanceMediumAnddistance1FarAnddistace2Medium->joinWithAND(distanceMediumAnddistance1Far, distance2Meduium);

  FuzzyRuleConsequent *thenLeftandRight17 = new FuzzyRuleConsequent();
  thenLeftandRight17->addOutput(big);
  thenLeftandRight17->addOutput(big1);

  FuzzyRule *fuzzyRule17 = new FuzzyRule(17, ifdistanceMediumAnddistance1FarAnddistace2Medium, thenLeftandRight17);
  fuzzy->addFuzzyRule(fuzzyRule17);

  FuzzyRuleAntecedent *ifdistanceMediumAnddistance1FarAnddistace2Far = new FuzzyRuleAntecedent();
  ifdistanceMediumAnddistance1FarAnddistace2Far->joinWithAND(distanceMediumAnddistance1Far, distance2Far);

  FuzzyRuleConsequent *thenLeftandRight18 = new FuzzyRuleConsequent();
  thenLeftandRight18->addOutput(big);
  thenLeftandRight18->addOutput(low1);

  FuzzyRule *fuzzyRule18 = new FuzzyRule(18, ifdistanceMediumAnddistance1FarAnddistace2Far, thenLeftandRight18);
  fuzzy->addFuzzyRule(fuzzyRule18);

  FuzzyRuleAntecedent *distanceFarAnddistance1Near = new FuzzyRuleAntecedent();
  distanceFarAnddistance1Near->joinWithAND(far, near1);
  FuzzyRuleAntecedent *ifdistanceFarAnddistance1NearAnddistace2Near = new FuzzyRuleAntecedent();
  ifdistanceFarAnddistance1NearAnddistace2Near->joinWithAND(distanceFarAnddistance1Near, distance2Near);

  FuzzyRuleConsequent *thenLeftandRight19 = new FuzzyRuleConsequent();
  thenLeftandRight19->addOutput(verylow);
  thenLeftandRight19->addOutput(big1);

  FuzzyRule *fuzzyRule19 = new FuzzyRule(19, ifdistanceFarAnddistance1NearAnddistace2Near, thenLeftandRight19);
  fuzzy->addFuzzyRule(fuzzyRule19);

  FuzzyRuleAntecedent *ifdistanceFarAnddistance1NearAnddistace2Medium = new FuzzyRuleAntecedent();
  ifdistanceFarAnddistance1NearAnddistace2Medium->joinWithAND(distanceFarAnddistance1Near, distance2Meduium);

  FuzzyRuleConsequent *thenLeftandRight20 = new FuzzyRuleConsequent();
  thenLeftandRight20->addOutput(verylow);
  thenLeftandRight20->addOutput(big1);

  FuzzyRule *fuzzyRule20 = new FuzzyRule(20, ifdistanceFarAnddistance1NearAnddistace2Medium, thenLeftandRight20);
  fuzzy->addFuzzyRule(fuzzyRule20);

  FuzzyRuleAntecedent *ifdistanceFarAnddistance1NearAnddistace2Far = new FuzzyRuleAntecedent();
  ifdistanceFarAnddistance1NearAnddistace2Far->joinWithAND(distanceFarAnddistance1Near, distance2Far);

  FuzzyRuleConsequent *thenLeftandRight21 = new FuzzyRuleConsequent();
  thenLeftandRight21->addOutput(big);
  thenLeftandRight21->addOutput(verylow1);

  FuzzyRule *fuzzyRule21 = new FuzzyRule(21, ifdistanceFarAnddistance1NearAnddistace2Far, thenLeftandRight21);
  fuzzy->addFuzzyRule(fuzzyRule21);

  FuzzyRuleAntecedent *distanceFarAnddistance1Medium = new FuzzyRuleAntecedent();
  distanceFarAnddistance1Medium->joinWithAND(far, safe1);
  FuzzyRuleAntecedent *ifdistanceFarAnddistance1MediumAnddistace2Near = new FuzzyRuleAntecedent();
  ifdistanceFarAnddistance1MediumAnddistace2Near->joinWithAND(distanceFarAnddistance1Medium, distance2Near);

  FuzzyRuleConsequent *thenLeftandRight22 = new FuzzyRuleConsequent();
  thenLeftandRight22->addOutput(medium);
  thenLeftandRight22->addOutput(medium1);

  FuzzyRule *fuzzyRule22 = new FuzzyRule(22, ifdistanceFarAnddistance1MediumAnddistace2Near, thenLeftandRight22);
  fuzzy->addFuzzyRule(fuzzyRule22);

  FuzzyRuleAntecedent *ifdistanceFarAnddistance1MediumAnddistace2Medium = new FuzzyRuleAntecedent();
  ifdistanceFarAnddistance1MediumAnddistace2Medium->joinWithAND(distanceFarAnddistance1Medium, distance2Meduium);

  FuzzyRuleConsequent *thenLeftandRight23 = new FuzzyRuleConsequent();
  thenLeftandRight23->addOutput(verylow);
  thenLeftandRight23->addOutput(medium1);

  FuzzyRule *fuzzyRule23 = new FuzzyRule(23, ifdistanceFarAnddistance1MediumAnddistace2Medium, thenLeftandRight23);
  fuzzy->addFuzzyRule(fuzzyRule23);

  FuzzyRuleAntecedent *ifdistanceFarAnddistance1MediumAnddistace2Far = new FuzzyRuleAntecedent();
  ifdistanceFarAnddistance1MediumAnddistace2Far->joinWithAND(distanceFarAnddistance1Medium, distance2Far);

  FuzzyRuleConsequent *thenLeftandRight24 = new FuzzyRuleConsequent();
  thenLeftandRight24->addOutput(verylow);
  thenLeftandRight24->addOutput(medium1);

  FuzzyRule *fuzzyRule24 = new FuzzyRule(24, ifdistanceFarAnddistance1MediumAnddistace2Far, thenLeftandRight24);
  fuzzy->addFuzzyRule(fuzzyRule24);


  FuzzyRuleAntecedent *distanceFarAnddistance1Far = new FuzzyRuleAntecedent();
  distanceFarAnddistance1Far->joinWithAND(far, far1);
  FuzzyRuleAntecedent *ifdistanceFarAnddistance1FarAnddistace2Near = new FuzzyRuleAntecedent();
  ifdistanceFarAnddistance1FarAnddistace2Near->joinWithAND(distanceFarAnddistance1Far, distance2Near);

  FuzzyRuleConsequent *thenLeftandRight25 = new FuzzyRuleConsequent();
  thenLeftandRight25->addOutput(medium);
  thenLeftandRight25->addOutput(big1);

  FuzzyRule *fuzzyRule25 = new FuzzyRule(25, ifdistanceFarAnddistance1FarAnddistace2Near, thenLeftandRight25);
  fuzzy->addFuzzyRule(fuzzyRule25);

  FuzzyRuleAntecedent *ifdistanceFarAnddistance1FarAnddistace2Medium = new FuzzyRuleAntecedent();
  ifdistanceFarAnddistance1FarAnddistace2Medium->joinWithAND(distanceFarAnddistance1Far, distance2Meduium);

  FuzzyRuleConsequent *thenLeftandRight26 = new FuzzyRuleConsequent();
  thenLeftandRight26->addOutput(medium);
  thenLeftandRight26->addOutput(big1);

  FuzzyRule *fuzzyRule26 = new FuzzyRule(26, ifdistanceFarAnddistance1FarAnddistace2Medium, thenLeftandRight26);
  fuzzy->addFuzzyRule(fuzzyRule26);

  FuzzyRuleAntecedent *ifdistanceFarAnddistance1FarAnddistace2Far = new FuzzyRuleAntecedent();
  ifdistanceFarAnddistance1FarAnddistace2Far->joinWithAND(distanceFarAnddistance1Far, distance2Far);

  FuzzyRuleConsequent *thenLeftandRight27 = new FuzzyRuleConsequent();
  thenLeftandRight27->addOutput(verybig);
  thenLeftandRight27->addOutput(verybig1);

  FuzzyRule *fuzzyRule27 = new FuzzyRule(27, ifdistanceFarAnddistance1FarAnddistace2Far, thenLeftandRight27);
  fuzzy->addFuzzyRule(fuzzyRule27);

}

void loop()
{
  // get random entrances

  dist1 = aKwarAway(trig1, echo1);
  dist2 = aKwarAway(trig2, echo2);
  dist3 = aKwarAway(trig3, echo3);

  int input1 = dist1;
  int input2 = dist2;
  int input3 = dist3;
  
  Serial.println("\n\n\nEntrance: ");
  Serial.print("\t\t\tDistance: ");
  Serial.print(input1);
  Serial.print("\t\t\tDistance1: ");
  Serial.print(input2);
  Serial.print("\t\t\tDistance2: ");
  Serial.println(input3);

  fuzzy->setInput(1, input1);
  fuzzy->setInput(2, input2);
  fuzzy->setInput(3, input3);

  fuzzy->fuzzify();

  Serial.println("Input: ");
  Serial.print("\tDistance: Near-> ");
  Serial.print(near->getPertinence());
  Serial.print(", Safe-> ");
  Serial.print(safe->getPertinence());
  Serial.print(", Distant-> ");
  Serial.println(far->getPertinence());

  Serial.println("Input: ");
  Serial.print("\tDistance: Near-> ");
  Serial.print(near1->getPertinence());
  Serial.print(", Safe-> ");
  Serial.print(safe1->getPertinence());
  Serial.print(", Distant-> ");
  Serial.println(far1->getPertinence());

  Serial.println("Input: ");
  Serial.print("\tDistance: Near-> ");
  Serial.print(near2->getPertinence());
  Serial.print(", Safe-> ");
  Serial.print(safe2->getPertinence());
  Serial.print(", Distant-> ");
  Serial.println(far2->getPertinence());


  float output1 = fuzzy->defuzzify(1);
  float output2 = fuzzy->defuzzify(2);


  Serial.println("Result: ");
  Serial.print("\t\t\t Left: ");
  Serial.print(output1);
  Serial.print(", and Right: ");
  Serial.println(output2);

  Drive(output1, output2);
  // wait 12 seconds
}

void Drive(int left, int right) {
  digitalWrite(m1, LOW);
  digitalWrite(m2, HIGH);
  digitalWrite(m3, LOW);
  digitalWrite(m4, HIGH);
  analogWrite(enable1, right);
  analogWrite(enable2, left);
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
