
#include <Servo.h>
const int PRX=2,IR=3,SM=4;
int dust=0,angle=0;
Servo myservo;
  // create servo object to control a servo
// twelve servo objects can be created on most boards

int pos = 0;    // variable to store the servo position

void setup() {
  myservo.attach(6);
  pinMode(PRX,INPUT_PULLUP);
  pinMode(IR,INPUT_PULLUP);
  pinMode(SM,INPUT);
  
  Serial.begin(9600);
}

void loop() {

if(digitalRead(IR)==1)
{  while (digitalRead(IR)==1)
    {}
    Serial.println("Dust Present\n");
    dust=1;
    delay(1000);
}

if(dust==1)
{
   if(digitalRead(PRX)==0)
   {
    angle = 240;  // bin 3
    Serial.println("Bin 3 angle 240\n");
    myservo.write(90);  // rotates the servo to 90 degrees
    delay(1000);        // waits for a second
   }
   else if(digitalRead(SM)==0)  //Soil moisture is 0 when detected
   {
    angle = 0;  // bin 1
    Serial.println("Bin 1 angle 0\n");
    myservo.write(90);  // rotates the servo to 90 degrees
    delay(1000);        // waits for a second
   }
   else
   {
    angle = 120; // bin 2
    Serial.println("Bin 2 angle 120\n");
    myservo.write(90);  // rotates the servo to 90 degrees
    delay(1000);        // waits for a second
   }

//stepper motor rotation code based on angle


  for (pos = 0; pos <= 90; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15 ms for the servo to reach the position
  }
delay(3000);
  for (pos = 90; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15 ms for the servo to reach the position
  }
delay(1000);
dust=0;
}
else
{
   Serial.println("Dust empty\n");
   delay(1000);
}

}