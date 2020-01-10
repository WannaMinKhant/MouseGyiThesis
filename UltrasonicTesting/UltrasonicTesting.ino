#include<LiquidCrystal_I2C_Hangul.h>
#include<Wire.h>

LiquidCrystal_I2C_Hangul lcd(0x3F, 16, 2); //LCD 클래스 초기화

int trig1 = 2, trig2 = 3, trig3 = 4;
int echo1 = 5, echo2 = 6, echo3 = 7;
float dist1, dist2, dist3,duration1,duration2,duration3;

int m1 = 47, m2 = 45, m3 = 43, m4 = 41;
int enable1 = 44, enable2 = 46;


void setup() {
  // put your setup code here, to run once:
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

}

void loop() {
  // put your main code here, to run repeatedly:
    dist1 = aKwarAway(trig1, echo1);
    dist2 = aKwarAway(trig2, echo2);
    dist3 = aKwarAway(trig3, echo3);

//  float distance = 0;
//  float duration;
//  digitalWrite(trig1, LOW);
//  digitalWrite(trig2, LOW);
//  digitalWrite(trig3, LOW);
//  delayMicroseconds(2);
//  digitalWrite(trig1, HIGH);
//  digitalWrite(trig2, HIGH);
//  digitalWrite(trig3, HIGH);
//  delayMicroseconds(2);
//
//  duration1 = pulseIn(echo1, HIGH);
//  duration2 = pulseIn(echo2, HIGH);
//  duration3 = pulseIn(echo3, HIGH);

//  dist1 = (duration1 / 2) / 28.57;
//  dist2 = (duration2 / 2) / 28.57;
//  dist3 = (duration3 / 2) / 28.57;



  if (dist2 > 25 && dist2 < 35)
  {
    digitalWrite(m1, 1);
    digitalWrite(m2, 0);
    digitalWrite(m3, 0);
    digitalWrite(m4, 1);
    analogWrite(enable2, 100);
    analogWrite(enable1, 100);
  } else if (dist2 > 50 && dist2 < 150 )
  {
    digitalWrite(m1, 1);
    digitalWrite(m2, 0);
    digitalWrite(m3, 0);
    digitalWrite(m4, 0);
    analogWrite(enable2, 180);
    analogWrite(enable1, 180);
  }
  else if (dist3 > 20 && dist3 < 50 )
  {
    digitalWrite(m1, 1);
    digitalWrite(m2, 0);
    digitalWrite(m3, 0);
    digitalWrite(m4, 0);
    analogWrite(enable2, 60);
    analogWrite(enable1, 60);
  } 
  else if (dist1 < 50 && dist1 > 20)
  {
    digitalWrite(m1, 0);
    digitalWrite(m2, 0);
    digitalWrite(m3, 0);
    digitalWrite(m4, 1);
    analogWrite(enable2, 60);
    analogWrite(enable1, 60);
  } 
  else if (dist2 > 30 && dist2 < 50)
  {
    digitalWrite(m1, 1);
    digitalWrite(m2, 0);
    digitalWrite(m3, 0);
    digitalWrite(m4, 1);
    analogWrite(enable2, 120);
    analogWrite(enable1, 120);
  }
  else if (dist2 > 15 && dist2 < 25)
  {
    digitalWrite(m1, 1);
    digitalWrite(m2, 0);
    digitalWrite(m3, 0);
    digitalWrite(m4, 1);
    analogWrite(enable2, 60);
    analogWrite(enable1, 60);
  }
  else if(dist1 > 70 || dist3 > 70)
  {
    analogWrite(enable1, 0);
    analogWrite(enable2, 0);
  }else{
    analogWrite(enable1, 0);
    analogWrite(enable2, 0);
  }
  
  lcd.setCursor(0, 0);
  lcd.print(dist1);
  lcd.setCursor(0, 1);
  lcd.print(dist2);
  lcd.setCursor(8, 1);
  lcd.print(dist3);

//  Serial.print(dist1);
//  Serial.println("  cm");
//  Serial.print(dist2);
//  Serial.println("  cm");
//  Serial.print(dist3);
//  Serial.println("  cm");
//  Serial.println();


}

float aKwarAway(int Tx, int Rx)
{
  float distance = 0;
  float duration;
  digitalWrite(Tx, LOW);
  delayMicroseconds(2);
  digitalWrite(Tx, HIGH);
  delayMicroseconds(2);

  duration = pulseIn(Rx, HIGH);
  distance = (duration / 2) / 28.57;
  return distance;
}
