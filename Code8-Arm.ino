#include <Servo.h>
#include <Wire.h>

#define Trigpin 8
#define Echopin 9

Servo myservo;
Servo myservo2;
Servo myservo3;
Servo myservo4;

float distance;
int duration;
int x = 100;
int pos = 50;

void setup(){
  Serial.begin(9600);

  pinMode(Trigpin, OUTPUT);
  pinMode(Echopin, INPUT);

  myservo.attach(10);
  myservo2.attach(11);
  myservo3.attach(3);
  myservo4.attach(5);
}

void loop(){
  
  digitalWrite(Trigpin, LOW);
  delayMicroseconds(2);
  digitalWrite(Trigpin, HIGH);
  delayMicroseconds(10);
  digitalWrite(Trigpin, LOW);
  duration = pulseIn(Echopin, HIGH);
  distance = duration * 0.034 / 2;
  delay(x);
  Serial.println("");
  Serial.print("Distance :- ");
  Serial.print(distance);
  Serial.print(" cm");

  if(distance <= 19){

    myservo3.write(180);
    myservo4.write(180);

    myservo.write(0);
    myservo2.write(0);

    delay(100);

    myservo.write(100);
    myservo2.write(100);

    myservo3.write(0);
    myservo4.write(0);

  }else if(distance > 19){

    myservo.write(100);
    myservo2.write(100);

  }
}