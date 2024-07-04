#include <Servo.h>
Servo servo1;
Servo servo2;
#define echoPin 2
#define trigPin 3

int Moisture_val;
int limitswitch_ind=10;
int limitswitch_ir=7;
int state1_ind=HIGH;
int value1_ind;
int state2_cap=HIGH;
int value2_cap;
int servoPin1= 9;
int servoPin2= 11;
long duration;
int distance;


void setup()
{
     Serial.begin(19200);
     servo1.attach(servoPin1);
     servo2.attach(servoPin2);
     pinMode(limitswitch_ind,INPUT);
     pinMode(limitswitch_ir,INPUT);
     pinMode(trigPin,OUTPUT);
     pinMode(echoPin,INPUT);

}
void loop()
{
    
    Serial.println("Moisture value:");
    Serial.println(Moisture_val);
    digitalWrite(trigPin,LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin,HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin,LOW);
    duration=pulseIn(echoPin,HIGH);
    distance=(duration*0.034/2);
    // Serial.println("Ultrasonic value:");
    Serial.print(distance);

if(distance<6)
{
  delay(8000);
  value1_ind = digitalRead(limitswitch_ind);
  value2_cap = digitalRead(limitswitch_cap);
  Moisture_val=analogRead(A0);

if(value1_ind!=state1_ind)
{
    Serial.println("METAL DETECTED");
    servo2.write(72);
    delay(2000);
    servo1.write(180); 
    delay(3000);
    servo1.write(70);
    delay(1000);
    servo2.write(0);
    delay(5000);  
 }
else if(value2_cap==HIGH)
{
  if(Moisture_val >600)
{
  // Serial.println("PLASTIC DETECTED");
    servo2.write(0);
    delay(2000);
    servo1.write(180); 
    delay(3000);
    servo1.write(70);
    delay(1000);
    servo2.write(0);
    delay(5000);
}
}
if(Moisture_val<540)
{
  // Serial.println("Wet material detected");
    servo2.write(180);
    delay(2000);
    servo1.write(0);
    delay(3000);
    servo1.write(70);
    delay(1000);
    servo2.write(0);
    delay(5000);
}   
}
}