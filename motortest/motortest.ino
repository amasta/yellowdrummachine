#include <AFMotor.h>

// right tread constants
#define MOTOR_TREAD_RIGHT 1
#define MOTOR_TREAD_RIGHT_FREQ MOTOR12_64KHZ
#define MOTOR_TREAD_RIGHT_SPEED 255

// left tread constants
#define MOTOR_TREAD_LEFT 2
#define MOTOR_TREAD_LEFT_FREQ MOTOR12_64KHZ
#define MOTOR_TREAD_LEFT_SPEED 255

// ultrasonic (US) distance finder constants
#define MOTOR_US 3
#define MOTOR_US_FREQ MOTOR12_64KHZ
#define MOTOR_US_SPEED 255
#define PIN_US_TRIG 48
#define PIN_US_ECHO 49

// bass motor constants
#define MOTOR_ARM_BASS 4
#define MOTOR_ARM_BASS_FREQ MOTOR12_64KHZ
#define MOTOR_ARM_BASS_SPEED 255




AF_DCMotor motorTreadRight(MOTOR_TREAD_RIGHT, MOTOR_TREAD_RIGHT_FREQ);
AF_DCMotor motorTreadLeft(MOTOR_TREAD_LEFT, MOTOR_TREAD_LEFT_FREQ);
AF_DCMotor motorUS(MOTOR_US, MOTOR_US_FREQ);
AF_DCMotor motorArmBass(MOTOR_ARM_BASS, MOTOR_ARM_BASS_FREQ);



void setup() {
  Serial.begin(115200);
  
  Serial.println("SETUP CONFIGURATION");
  
  
  motorTreadRight.setSpeed(MOTOR_TREAD_RIGHT_SPEED);
  motorTreadLeft.setSpeed(MOTOR_TREAD_LEFT_SPEED);
  motorUS.setSpeed(MOTOR_US_SPEED);
  motorArmBass.setSpeed(MOTOR_ARM_BASS_SPEED);

  pinMode(PIN_US_TRIG, OUTPUT);
  pinMode(PIN_US_ECHO, INPUT);
}

void driveForward(int timeLength) {
	motorTreadRight.run(FORWARD);
	motorTreadLeft.run(FORWARD);
	
	delay(timeLength);
	
	motorTreadRight.run(RELEASE);
	motorTreadLeft.run(RELEASE);
}

void driveBackward(int timeLength) {
	motorTreadRight.run(BACKWARD);
	motorTreadLeft.run(BACKWARD);
	
	delay(timeLength);
	
	motorTreadRight.run(RELEASE);
	motorTreadLeft.run(RELEASE);
}

void driveRotateRight(int timeLength) {
	motorTreadRight.run(BACKWARD);
	motorTreadLeft.run(FORWARD);
	
	delay(timeLength);
	
	motorTreadRight.run(RELEASE);
	motorTreadLeft.run(RELEASE);
}

void driveRotateLeft(int timeLength) {
	motorTreadRight.run(FORWARD);
	motorTreadLeft.run(BACKWARD);
	
	delay(timeLength);
	
	motorTreadRight.run(RELEASE);
	motorTreadLeft.run(RELEASE);
}

void driveForwardRight(int timeLength) {
	motorTreadRight.run(FORWARD);
	
	delay(timeLength);
	
	motorTreadRight.run(RELEASE);
}

void driveForwardLeft(int timeLength) {
	motorTreadLeft.run(FORWARD);
	
	delay(timeLength);
	
	motorTreadLeft.run(RELEASE);
}

void driveBackwardRight(int timeLength) {
	motorTreadRight.run(BACKWARD);
	
	delay(timeLength);
	
	motorTreadRight.run(RELEASE);
}

void driveBackwardLeft(int timeLength) {
	motorTreadLeft.run(BACKWARD);
	
	delay(timeLength);
	
	motorTreadLeft.run(RELEASE);
}

void playBass()
{
  motorArmBass.run(BACKWARD);
  delay(100);
  motorArmBass.run(RELEASE); 
}

float getUSDistance() {
  digitalWrite(PIN_US_TRIG, LOW);
  delayMicroseconds(2);
  
  digitalWrite(PIN_US_TRIG, HIGH);
  //delayMicroseconds(10);
  
  digitalWrite(PIN_US_TRIG, LOW);

  return pulseIn(PIN_US_ECHO, HIGH) / 58;  
}

float getUSDistanceRight() {
  motorUS.run(FORWARD);
  delay(500);
  
  float distance = getUSDistance();
  motorUS.run(RELEASE);
  
  return distance;
}

float getUSDistanceLeft() {
  motorUS.run(BACKWARD);
  delay(500);
 
  float distance = getUSDistance();
  motorUS.run(RELEASE);
  
  return distance;
}

void loop() {
  float distanceLeft = 0;
  float distanceForward = 0;
  float distanceRight = 0;
  
  distanceForward = getUSDistance();
  distanceLeft = getUSDistanceLeft();
  distanceRight = getUSDistanceRight();
  
  Serial.print("L: ");
  Serial.println(distanceLeft);
  delay(500);
  Serial.print("F: ");
  Serial.println(distanceForward);
  Serial.print("R: ");
  Serial.println(distanceRight);
  
  if (distanceForward > 10)
  {
    driveForward(2000);
  }
 else if (distanceLeft > distanceRight)
 {
   driveBackward(4000);
   driveRotateLeft(1400);
 } 
 else if (distanceLeft < distanceRight)
 {
   driveBackward(4000);
   driveRotateRight(1400);
 }
    
  
  /*
  playBass();
  delay(200);
  
  playBass();
  delay(20);
  playBass();
  delay(20);
  playBass();
  delay(20);
  
  playBass();
  delay(300);
  playBass();
  delay(200);
  playBass();
  delay(1000);


  driveForward(2000);
  driveRotateRight(4000);
  driveRotateLeft(4000);
  driveBackward(2000);
  driveForwardRight(2000);
  driveBackwardRight(2000);
  driveForwardLeft(2000);
  driveBackwardLeft(2000);*/
}
