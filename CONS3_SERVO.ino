#include <Servo.h>

const int PRX = 2, IR = 3, SM = 4;
int dust = 0, angle=0,angle1= 90;
Servo myservo; 
 // create servo object to control a servo

void setup() {
  myservo.attach(12);  // attaches the servo on pin 12 to the servo object
  pinMode(PRX, INPUT_PULLUP);
  pinMode(IR, INPUT_PULLUP);
  pinMode(SM, INPUT);
  Serial.begin(9600);
}

void loop() {
  if (digitalRead(IR) == 1) {
    while (digitalRead(IR) == 1) {}
    Serial.println("Dust Present\n");
    dust = 1;
    delay(1000);
  }

  if (dust == 1) {
    if (digitalRead(PRX) == 0) {
      angle = 240;  // bin 3
      Serial.println(" METAL WASTE Bin 3 angle 240\n");
      rotateServo(angle1);
    }
    else if (digitalRead(SM) == 0) {
      angle = 0;  // bin 1
      Serial.println(" WET WASTE Bin 1 angle 0\n");
      rotateServo(angle1);
    }
    else {
      angle = 120; // bin 2
      Serial.println(" DRY Bin 2 angle 120\n");
      rotateServo(angle1);
    }

    dust = 0;
  }
  else {
    Serial.println("Dust empty\n");
    delay(1000);
  }
}

void rotateServo(int targetAngle) {
  int currentAngle = myservo.read();
  if (currentAngle < targetAngle) {
    for (int pos = currentAngle; pos <= targetAngle; pos += 1) {
      myservo.write(pos);
      delay(15);
    }
  }
  else if (currentAngle > targetAngle) {
    for (int pos = currentAngle; pos >= targetAngle; pos -= 1) {
      myservo.write(pos);
      delay(15);
    }
  }
  delay(1000); // Pause for stability
}