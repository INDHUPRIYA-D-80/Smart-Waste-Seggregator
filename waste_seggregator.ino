#include <Servo.h>
const int PRX = 2;
const int IR = 3;
const int SM = 4;
const int STEPPER_PIN_1 = 8;
const int STEPPER_PIN_2 = 9;
const int STEPPER_PIN_3 = 10;
const int STEPPER_PIN_4 = 11;
const int STEPS_PER_REVOLUTION = 200;
int dust = 0;
int angle = 0;
Servo myservo;
int pos = 0;
void setup() {
  Serial.begin(9600);
  myservo.attach(12);
  pinMode(PRX, INPUT_PULLUP);
  pinMode(IR, INPUT_PULLUP);
  pinMode(SM, INPUT);
  pinMode(STEPPER_PIN_1, OUTPUT);
  pinMode(STEPPER_PIN_2, OUTPUT);
  pinMode(STEPPER_PIN_3, OUTPUT);
  pinMode(STEPPER_PIN_4, OUTPUT);
}
void loop() {
  if (digitalRead(IR) == 1) {
    while (digitalRead(IR) == 1) {} 
    Serial.println("Dust Present");
    dust = 1;
    delay(1000);
  }
  if (dust == 1) {
    if (digitalRead(PRX) == 0) {
      angle = 240;  
      Serial.println("Bin 3 angle 240");
    }
    else if (digitalRead(SM) == 0) {
      angle = 0;  
      Serial.println("Bin 1 angle 0");
    }
    else {
      angle = 120; 
      Serial.println("Bin 2 angle 120");
    }
    myservo.write(angle);
    delay(1000);
    int stepperSteps = angle * (STEPS_PER_REVOLUTION / 360);
    rotateStepper(stepperSteps);
    dust = 0;
  }
  else {
    Serial.println("Dust empty");
    delay(1000);
  }
}
void rotateStepper(int steps) {
  const int stepSequence[][4] = {
    {HIGH, LOW, LOW, HIGH},
    {HIGH, HIGH, LOW, LOW},
    {LOW, HIGH, HIGH, LOW},
    {LOW, LOW, HIGH, HIGH}
  };
  int currentStep = 0;
  unsigned long previousMillis = 0;
  const long stepInterval = 2;
  for (int i = 0; i < steps; i++) {
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis >= stepInterval) {
      digitalWrite(STEPPER_PIN_1, stepSequence[currentStep][0]);
      digitalWrite(STEPPER_PIN_2, stepSequence[currentStep][1]);
      digitalWrite(STEPPER_PIN_3, stepSequence[currentStep][2]);
      digitalWrite(STEPPER_PIN_4, stepSequence[currentStep][3]);
      currentStep++;
      if (currentStep == 4) {
        currentStep = 0;
      }
      previousMillis = currentMillis;
    }
  }
}