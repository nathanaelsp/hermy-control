/*
 * Hermit Crab Inspired Crawling Soft Robot
 * RC Transmitter Control
 * 
 * By: Group 6
 * 
 * This program is developed as part of:
 * ME4242 Soft Robotics Group Project
 * Semester 2 AY 2020/21
 * 
 * Department of Mechanical Engineering
 * Faculty of Engineering
 * National University of Singapore
 */

#define THROTTLE_MID 1400
#define STEER_MID 1368
#define BUFFER 400

// Define valve pin outs
int left = 2;
int right = 3;
int enable = 5;
int pump = 12;

// Declare and initialize variables for valve states
int enableState = HIGH;
int leftState = LOW;
int rightState = LOW;

// Declare channel pin outs and variables for RC transmitter control
int interruptSteerPin = 20;
int interruptThrottlePin = 21;
unsigned long start1;
int throttle;
unsigned long start2;
int steer;

void setup() {
  pinMode(left, OUTPUT);
  pinMode(right, OUTPUT);
  pinMode(enable, OUTPUT);
  pinMode(pump, OUTPUT);
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);

  digitalWrite(enable, enableState);
  digitalWrite(left, leftState);
  digitalWrite(right, leftState);
  digitalWrite(pump, HIGH);

  attachInterrupt(2, timeit1, CHANGE);
  attachInterrupt(3, timeit2, CHANGE);

  Serial.begin(9600);
}

void loop() {
  Move();
  digitalWrite(enable, enableState);
  digitalWrite(left, leftState);
  digitalWrite(right, rightState);
}


void Move() {
  if (throttle >= THROTTLE_MID + BUFFER) {
    digitalWrite(pump, HIGH);
    if (steer <= STEER_MID - BUFFER) {
      MoveLeft();           // Move left leg
    } else if (steer >= STEER_MID + BUFFER) {
      MoveRight();          // Move right leg
    } else {
      Stop();
    }
  } else {
    digitalWrite(pump, LOW);
    Stop();
  }
}

void MoveLeft() {
  enableState = HIGH;
  leftState = HIGH;
  rightState = LOW;
}

void MoveRight() {
  enableState = HIGH;
  rightState = HIGH;
  leftState = LOW;
}

void Stop() {
  enableState = LOW;
  leftState = LOW;
  rightState = LOW;
}

// timer functions timeit1() and timeit2()
void timeit1() {
  if (digitalRead(interruptThrottlePin) == HIGH) {
    start1 = micros();
  } else {
    throttle = micros() - start1;
  }
}

void timeit2() {
  if (digitalRead(interruptSteerPin) == HIGH) {
    start2 = micros();
  } else {
    steer = micros() - start2;
  }
}
