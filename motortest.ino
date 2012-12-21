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
#define PIN_US_TRIG 28
#define PIN_US_ECHO 29


AF_DCMotor motorTreadRight(MOTOR_TREAD_RIGHT, MOTOR_TREAD_RIGHT_FREQ);
AF_DCMotor motorTreadLeft(MOTOR_TREAD_LEFT, MOTOR_TREAD_LEFT_FREQ);
AF_DCMotor motorUS(MOTOR_US, MOTOR12_64KHZ);
 

void setup() {
  //Serial.begin(9600);
  
  //Serial.println("SETUP CONFIGURATION");
  
  motorTreadRight.setSpeed(MOTOR_TREAD_RIGHT_SPEED);
  motorTreadLeft.setSpeed(MOTOR_TREAD_LEFT_SPEED);
  motorUS.setSpeed(MOTOR_US_SPEED);
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
	motorTreadLeft.run(BACKWARD);
	
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



void loop() {

}
