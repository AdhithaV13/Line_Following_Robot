#include <AFMotor.h>
#include <Servo.h>
#include <Wire.h>

#define Trigpin 5
#define Echopin 6
  
AF_DCMotor motor1(1, MOTOR12_1KHZ);
AF_DCMotor motor2(2, MOTOR12_1KHZ);
AF_DCMotor motor3(3, MOTOR34_1KHZ);
AF_DCMotor motor4(4, MOTOR34_1KHZ);

Servo myservo;
Servo myservo2;
Servo myservo3;
Servo myservo4;
  
int var;
int var2;

int val;
int Speeed = 255;

float distance;
int duration;
int x = 700;

void setup(){
  
  pinMode(Trigpin,OUTPUT);
  pinMode(Echopin,INPUT);

  pinMode(A0,INPUT);
  pinMode(A1,INPUT);

  myservo.attach(10);
  myservo2.attach(11);
  myservo3.attach(3);
  myservo4.attach(5);

}

void loop(){
  if((digitalRead(A0) == HIGH) && (digitalRead(A1) == HIGH)){
    motor1.setSpeed(Speeed);
    motor2.setSpeed(Speeed);
    motor1.run(RELEASE);
    motor2.run(RELEASE);
  }
  
  if(digitalRead(A0) == HIGH){
    motor2.setSpeed(Speeed);
    motor1.setSpeed(0);
    motor2.run(FORWARD);
    motor1.run(RELEASE);
  }
  
  if(digitalRead(A1) == HIGH){
    motor1.setSpeed(Speeed);
    motor2.setSpeed(0);
    motor1.run(FORWARD);
    motor2.run(RELEASE);
  }

  if((digitalRead(A0) == LOW) && (digitalRead(A1) == LOW)){
    motor1.setSpeed(0);
    motor2.setSpeed(0);
    motor1.run(FORWARD);
    motor2.run(FORWARD);
  }

  digitalWrite(Trigpin,LOW);
  delayMicroseconds(2);
  digitalWrite(Trigpin,HIGH);
  delayMicroseconds(10);
  digitalWrite(Trigpin,LOW);
  duration = pulseIn(Echopin,HIGH);
  distance = duration*0.034/2;
  delay(x);
  
  if(distance == 19){

    motor1.setSpeed(0);
    motor2.setSpeed(0);
    motor1.run(RELEASE);
    motor2.run(RELEASE);

    myservo3.write(180);
    myservo4.write(180);

    myservo.write(0);
    myservo2.write(0);

    motor1.setSpeed(Speeed);
    motor2.setSpeed(Speeed);
    motor1.run(FORWARD);
    motor2.run(FORWARD);

    delay(100);

    motor1.setSpeed(0);
    motor2.setSpeed(0);
    motor1.run(RELEASE);
    motor2.run(RELEASE);

    myservo.write(100);
    myservo2.write(100);

    myservo3.write(0);
    myservo4.write(0);

  }else if(distance > 19){

    myservo.write(100);
    myservo2.write(100);

  }
}