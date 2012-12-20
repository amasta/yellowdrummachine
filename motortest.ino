// LEFT TREAD MOTOR 2
// RIGHT TREAD MOTOR 1
// HEAD MOTOR 3
// US TRIG 28
// US TRIP 29


#include <AFMotor.h>

AF_DCMotor neckMotor(3, MOTOR12_64KHZ);
AF_DCMotor motor(2, MOTOR12_64KHZ); // create motor #2, 64KHz pwm
AF_DCMotor motor2(1, MOTOR12_64KHZ);

void setup() {
  Serial.begin(9600);           // set up Serial library at 9600 bps
  Serial.println("Motor test!");
  
  motor.setSpeed(255);     // set the speed to 200/255
  motor2.setSpeed(255);
  neckMotor.setSpeed(255);
}

void loop() {
  Serial.print("tick");
  
  neckMotor.run(FORWARD);
  motor.run(FORWARD);
  motor2.run(FORWARD);
  delay(2000);
  neckMotor.run(RELEASE);
  motor.run(RELEASE);
  motor2.run(RELEASE);
  delay(2000);
  neckMotor.run(BACKWARD);
  motor.run(BACKWARD);
  motor2.run(BACKWARD);
  delay(2000);  
  neckMotor.run(RELEASE);
  motor.run(RELEASE);
  motor2.run(RELEASE);
  delay(2000);
  
  ///motor.run(FORWARD);      // turn it on going forward
  //delay(2000);
  //motor.run(BACKWARD);   // turn it on going forward
  //delay(2000);
  
  //motor.run(RELEASE);
  //motor2.run(FORWARD);
//fs  delay(1000);

  Serial.print("tock");
  //motor.run(BACKWARD);     // the other way
 // delay(1000);
  
  //Serial.print("tack");
  //motor.run(RELEASE);      // stopped
  //delay(1000);
}
