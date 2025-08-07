#include <AFMotor.h>   // Import library to control motor shield
#include <Servo.h>     // Import library to control the servo

AF_DCMotor rightBack(1);   // Create an object to control each motor
AF_DCMotor rightFront(2);
AF_DCMotor leftFront(3);
AF_DCMotor leftBack(4);
Servo servoLook;           // Create an object to control the servo

byte trig = A0;            // Assign the ultrasonic sensor pins
byte echo = A1;
byte maxDist = 150;        // Maximum sensing distance (Objects farther than this are ignored)
byte stopDist = 50;        // Minimum distance from an object to stop (in cm)
float timeOut = 2 * (maxDist + 10) / 100.0 / 340 * 1000000; // Max time to wait for a return signal
byte motorSpeed = 55;      // Base motor speed
int motorOffset = 10;      // Offset to account for motor imbalance
int turnSpeed = 50;        // Speed increment when turning

void setup() {
  Serial.begin(9600);  // Initialize serial communication
  rightBack.setSpeed(motorSpeed);
  rightFront.setSpeed(motorSpeed);
  leftFront.setSpeed(motorSpeed + motorOffset);
  leftBack.setSpeed(motorSpeed + motorOffset);

  rightBack.run(RELEASE);
  rightFront.run(RELEASE);
  leftFront.run(RELEASE);
  leftBack.run(RELEASE);

  servoLook.attach(10);  // Assign the servo pin

  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
}

void loop() {
  servoLook.write(115);  // Look straight
  delay(750);

  int distance = getDistance();

  if (distance >= stopDist) {
    moveForward();
  }

  while (distance >= stopDist) {
    distance = getDistance();
    delay(250);
  }

  stopMove();

  int turnDir = checkDirection();  // 0 = left, 1 = reverse, 2 = right
  Serial.print("Turn direction: ");
  Serial.println(turnDir);

  switch (turnDir) {
    case 0:
      turnLeft(400);
      break;
    case 1:
      turnLeft(700);
      break;
    case 2:
      turnRight(400);
      break;
  }
}

void accelerate() {
  for (int i = 0; i < motorSpeed; i++) {
    rightBack.setSpeed(i);
    rightFront.setSpeed(i);
    leftFront.setSpeed(i + motorOffset);
    leftBack.setSpeed(i + motorOffset);
    delay(10);
  }
}

void decelerate() {
  for (int i = motorSpeed; i != 0; i--) {
    rightBack.setSpeed(i);
    rightFront.setSpeed(i);
    leftFront.setSpeed(i + motorOffset);
    leftBack.setSpeed(i + motorOffset);
    delay(10);
  }
}

void moveForward() {
  rightBack.run(FORWARD);
  rightFront.run(FORWARD);
  leftFront.run(FORWARD);
  leftBack.run(FORWARD);
}

void stopMove() {
  rightBack.run(RELEASE);
  rightFront.run(RELEASE);
  leftFront.run(RELEASE);
  leftBack.run(RELEASE);
}

void turnLeft(int duration) {
  rightBack.setSpeed(motorSpeed + turnSpeed);
  rightFront.setSpeed(motorSpeed + turnSpeed);
  leftFront.setSpeed(motorSpeed + motorOffset + turnSpeed);
  leftBack.setSpeed(motorSpeed + motorOffset + turnSpeed);

  rightBack.run(FORWARD);
  rightFront.run(FORWARD);
  leftFront.run(BACKWARD);
  leftBack.run(BACKWARD);

  delay(duration);

  resetMotorSpeed();
  stopMove();
}

void turnRight(int duration) {
  rightBack.setSpeed(motorSpeed + turnSpeed);
  rightFront.setSpeed(motorSpeed + turnSpeed);
  leftFront.setSpeed(motorSpeed + motorOffset + turnSpeed);
  leftBack.setSpeed(motorSpeed + motorOffset + turnSpeed);

  rightBack.run(BACKWARD);
  rightFront.run(BACKWARD);
  leftFront.run(FORWARD);
  leftBack.run(FORWARD);

  delay(duration);

  resetMotorSpeed();
  stopMove();
}

void resetMotorSpeed() {
  rightBack.setSpeed(motorSpeed);
  rightFront.setSpeed(motorSpeed);
  leftFront.setSpeed(motorSpeed + motorOffset);
  leftBack.setSpeed(motorSpeed + motorOffset);
}

int getDistance() {
  unsigned long pulseTime;
  int distance;

  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);

  pulseTime = pulseIn(echo, HIGH, timeOut);
  distance = (float)pulseTime * 340 / 2 / 10000;

  return distance;
}

int checkDirection() {
  int distances[2] = {0, 0}; // [left, right]
  int turnDir = 1; // 0 = left, 1 = reverse, 2 = right

  servoLook.write(180); // Look left
  delay(500);
  distances[0] = getDistance();

  servoLook.write(0);   // Look right
  delay(1000);
  distances[1] = getDistance();

  if (distances[0] >= 200 && distances[1] >= 200) {
    turnDir = 0;  // both directions clear → turn left
  } else if (distances[0] <= stopDist && distances[1] <= stopDist) {
    turnDir = 1;  // both directions blocked → reverse
  } else if (distances[0] >= distances[1]) {
    turnDir = 0;  // more space on left → turn left
  } else {
    turnDir = 2;  // more space on right → turn right
  }

  return turnDir;
}