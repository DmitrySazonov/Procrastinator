#include <ServoSmooth.h>

ServoSmooth servo;

uint32_t servoTimer;
uint32_t turnTimer;

int position1 = 10;   // first servo position
int position2 = 160;  // second servo position
boolean flag;

void setup() {
  //see ServoSmooth docs
  servo.attach(3);
  servo.setSpeed(20);
  servo.setAccel(0.5);

  pinMode(5, INPUT_PULLUP);
  pinMode(A1, OUTPUT);
}

void loop() {

  bool btnState = !digitalRead(5);

  if (btnState) {

    digitalWrite(A1, HIGH);

    if (millis() - servoTimer >= 20) {  
      servoTimer += 20;
      servo.tickManual();  
    }

    // change position every 2 min
    if (millis() - turnTimer >= 120000) {
      turnTimer = millis();
      flag = !flag;
      if (flag) servo.setTargetDeg(position1);
      else servo.setTargetDeg(position2);
    }
  } else {
    digitalWrite(A1, LOW);
  }
}
