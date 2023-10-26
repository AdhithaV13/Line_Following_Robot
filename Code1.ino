#include "Motion.h"
#include "IR.h"
#include "Gripper.h"
#include "lcd.h"

long duration;
int distance;

int left;
int center;
int right;
int distanceLower;
int distanceUpper;


Motion motion;
Ir ir;
Grip gripperOpenClose;
Grip gripperUp;

LiquidCrystalDisplay LCD;
bool flag = true;
bool flagObj = true;

void setup() {
  Serial.begin(9600);
  motion.init();
  ir.init();
  gripperOpenClose.init(10);
  gripperUp.initUp(11);
  LCD.init();
  pinMode(7, OUTPUT); 
  pinMode(6, INPUT); 
  pinMode(8, OUTPUT);
  pinMode(9, INPUT); 


}

void loop() {

  distanceLower = getDistance(7, 6);
  Serial.print("Distance lower: ");
  Serial.println(distanceLower);

  distanceUpper = getDistance(8, 9);

  Serial.print("Distance upper: ");
  Serial.println(distanceUpper);

  if (distanceLower < 18 && distanceUpper < 18 && flag) {
    Serial.println("catch");
    LCD.writeonLCD("grap");
    motion.Stop();
    delay(100);
    motion.backward();
    delay(200);
    motion.Stop();
    gripperUp.openGripperUp();
    delay(100);
    gripperOpenClose.openGripper();
    while (distanceLower > 9 ) {
      checkLine();
      distanceLower = getDistance(7, 6);
      distanceUpper = getDistance(8, 9);
    }
    motion.Stop();
    gripperOpenClose.closeGripper();
    delay(1000);
    gripperUp.closeGripperUp();
    flag = false;

  }
  else if (distanceLower < 10 && flagObj) {
    //avoid
    LCD.writeonLCD("avoid");
    motion.avoid();
    motion.rightfesa();
    while (ir.getLeftReadings() == LOW && ir.getCenterReadings() == LOW && ir.getRightReadings() == LOW) {
      checkLine();
      motion.rightfesa();
    }
    motion.forward();
    delay(200);
    motion.left();
    delay(300);
    flagObj = false;
  }
  else {
    checkLine();

  }
}

void checkLine() {
  left = ir.getLeftReadings();
  center = ir.getCenterReadings();
  right = ir.getRightReadings();

  if (left == LOW && center == HIGH && right == LOW) {
    motion.forward();
    LCD.writeonLCD("forward");
  }
  else if (left == LOW && center == HIGH && right == HIGH) {
    motion.right();
    LCD.writeonLCD("right");

  }
  else if (left == HIGH && center == HIGH && right == LOW) {
    motion.left();
    LCD.writeonLCD("left");

  }
  else if (left == HIGH && center == HIGH && right == HIGH) {
    if (distanceLower < 10) {
      LCD.writeonLCD("Leave object");
      motion.Stop();
      delay(100);
      motion.backward();
      delay(700);
      motion.Stop();
      gripperUp.openGripperUp();
      gripperOpenClose.openGripper();
      motion.backward();
      delay(200);
      motion.Stop();
      delay(100000000);
    }
    else {
      motion.forward();
      LCD.writeonLCD("stop");
    }
  }
  else if (left == LOW && center == LOW && right == LOW) {
    motion.forward();
    LCD.writeonLCD("forward");

  }
  else if (left == LOW && center == LOW && right == HIGH) {
    motion.right();
    delay(50);
    LCD.writeonLCD("right");

  }
  else if (left == HIGH && center == LOW && right == LOW) {
    motion.left();
    delay(50);
    LCD.writeonLCD("left");

  }
  else if (left == HIGH && center == LOW && right == HIGH) {
    motion.forward();
  }


}

int getDistance(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;
  return distance;
}
