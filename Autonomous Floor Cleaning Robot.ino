#include <AFMotor.h>
#include <Servo.h>
#include <NewPing.h>

const int trigPin = 9; // Define trigPin, assuming you want to use pin 9
const int echoPin = 10; // Define echoPin, using pin 10 for the ultrasonic sensor
const int m1 = 2; 
const int m2 = 3; 
const int m3 = 4; 
const int m4 = 5; 
const int m5 = 6; 
const int m6 = 7; 

AF_DCMotor motor1(1, MOTOR12_1KHZ); 
AF_DCMotor motor2(2, MOTOR12_1KHZ);
AF_DCMotor motor3(3, MOTOR34_1KHZ); 
AF_DCMotor motor4(4, MOTOR34_1KHZ);
Servo myservo;   

boolean goesForward = false;
int distance = 100;
int speedSet = 0;
int distanceR, distanceL;
long duration;
const int MAX_SPEED = 255;

NewPing sonar(trigPin, echoPin, 200); // Initialize NewPing library for the ultrasonic sensor

void setup() { 
  myservo.attach(11);  // Change the servo pin to 11 to avoid conflict with echoPin
  myservo.write(115); 
  delay(2000);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT);
  pinMode(m1, OUTPUT);
  pinMode(m2, OUTPUT); 
  pinMode(m3, OUTPUT);
  pinMode(m4, OUTPUT);
  pinMode(m5, OUTPUT);
  pinMode(m6, OUTPUT);
  pinMode(13, OUTPUT);
}

void loop() { 
  distance = readPing();
  motor();
}

void motor() {
  if (distance <= 15) {
    moveStop();
    delay(100);
    moveBackward();
    delay(300);
    moveStop();
    delay(200);
    distanceR = lookRight();
    delay(200);
    distanceL = lookLeft();
    delay(200);

    if (distanceR >= distanceL) {
      turnRight();
      moveStop();
    } else { 
      turnLeft();
      moveStop();
    }
  } else {
    moveForward();
  }
  distance = readPing();
}

int lookRight() {
  myservo.write(50); 
  delay(500);
  int distance = readPing();
  delay(100);
  myservo.write(115); 
  return distance;
}

int lookLeft() {
  myservo.write(170); 
  delay(500);
  int distance = readPing();
  delay(100);
  myservo.write(115); 
  return distance;
}

int readPing() { 
  delay(70);
  int cm = sonar.ping_cm();
  if (cm == 0) {
    cm = 250;
  }
  return cm;
}

void moveStop() {
  motor1.run(RELEASE); 
  motor2.run(RELEASE);
  motor3.run(RELEASE);
  motor4.run(RELEASE);
} 

void moveForward() {
  if (!goesForward) {
    goesForward = true;
    motor1.run(FORWARD);      
    motor2.run(FORWARD);
    motor3.run(FORWARD); 
    motor4.run(FORWARD);     
    for (speedSet = 0; speedSet < MAX_SPEED; speedSet += 2) { // slowly bring the speed up to avoid loading down the batteries too quickly
      motor1.setSpeed(speedSet);
      motor2.setSpeed(speedSet);
      motor3.setSpeed(speedSet);
      motor4.setSpeed(speedSet);
      delay(5);
    }
  }
}

void moveBackward() {
  goesForward = false;
  motor1.run(BACKWARD);      
  motor2.run(BACKWARD);
  motor3.run(BACKWARD);
  motor4.run(BACKWARD);  
  for (speedSet = 0; speedSet < MAX_SPEED; speedSet += 2) { // slowly bring the speed up to avoid loading down the batteries too quickly
    motor1.setSpeed(speedSet);
    motor2.setSpeed(speedSet);
    motor3.setSpeed(speedSet);
    motor4.setSpeed(speedSet);
    delay(5);
  }
}

void turnRight() {
  motor1.run(FORWARD);
  motor2.run(BACKWARD);
  motor3.run(FORWARD);
  motor4.run(BACKWARD);
  delay(500);
}

void turnLeft() {
  motor1.run(BACKWARD);
  motor2.run(FORWARD);
  motor3.run(BACKWARD);
  motor4.run(FORWARD);
  delay(500);
}
