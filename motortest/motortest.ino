//#include <Esplora.h>
#include <AFMotor.h>


// movement limitations
#define FORWARD_HALT_DISTANCE 10



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



// Drum constants
#define PIN_LEFT_DRUMSTICK_VCC 48
#define PIN_LEFT_DRUMSTICK_GND 49

//Constants for the sampler board
#define PIN_SAMPLER_PLAY 39
#define PIN_SAMPLER_RECORD 41

//Bass Drum constants
#define MOTOR_BASS_DRUM 4



#define a3 4545  //220hz
#define a3s 4292 //233hz
#define c4 3817  //262hz
#define c5 1912      //523
#define g3 5102  //196hz
#define b3 4049  //247hz
#define d4 3401  //294


//#define c 3830    // 261 Hz  //this has been commented out because it throws compilation errors.
#define d 3400    // 294 Hz 
#define e 3038    // 329 Hz 
#define f 2864    // 349 Hz 
#define g 2550    // 392 Hz 
#define a 2272    // 440 Hz 
#define b 2028    // 493 Hz 
#define C 1912    // 523 Hz 





// Define a special note, 'R', to represent a rest
#define R 0






AF_DCMotor motorTreadRight(MOTOR_TREAD_RIGHT, MOTOR_TREAD_RIGHT_FREQ);
AF_DCMotor motorTreadLeft(MOTOR_TREAD_LEFT, MOTOR_TREAD_LEFT_FREQ);
AF_DCMotor motorUS(MOTOR_US, MOTOR_US_FREQ);
AF_DCMotor motorArmBass(MOTOR_ARM_BASS, MOTOR_ARM_BASS_FREQ);


float distanceLeft = 0;
float distanceForward = 0;
float distanceRight = 0;

bool isDriveForward = false;
bool canDriveForward = false;


const int speakerOut = 24;


void setup() {
  Serial.begin(9600);  
  Serial.println("SETUP CONFIGURATION");
  
  pinMode(PIN_SAMPLER_PLAY, OUTPUT);
  pinMode(PIN_SAMPLER_RECORD, OUTPUT);

  digitalWrite(PIN_SAMPLER_PLAY, LOW);  
  digitalWrite(PIN_SAMPLER_RECORD, LOW);  
    
  pinMode(speakerOut, OUTPUT);
  pinMode(26, OUTPUT);
  
  digitalWrite(26, LOW);
  
  /*
  pinMode(26, OUTPUT);
  pinMode(9, OUTPUT);
  digitalWrite(26, LOW);
  */



  //Serial.begin(9600);

  //Serial.println("SETUP CONFIGURATION");


  //motorBass.setSpeed(255);

  // motor drive with flagging
  isDriveForward = false;
  canDriveForward = false;
  // end motor drive flagging
  
  
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

// motor drive with flagging
void driveForwardBegin()
{
	motorTreadRight.run(FORWARD);
	motorTreadLeft.run(FORWARD);
}

void driveHalt()
{
	motorTreadRight.run(RELEASE);
	motorTreadLeft.run(RELEASE);
	
	isDriveForward = false;
	canDriveForward = false;
}
// end motor drive with flagging

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


void bassBeat() {
 motorArmBass.run(BACKWARD);
 delay(75);
 
 motorArmBass.run(RELEASE); 
}



/*
a3 quart (252)

c4 sixteenth (60)
c4 (half+quarter?) (704)
a#3 (2 quarters) 104
a3 (eighth) 136
g3 (sixteenth) 104
a3 (372) 
a#3 (368)
b3 (384)
c4 (384)
d4 (252)
long pause (3 sec?)
c4  1392
*/


// MELODY and TIMING  =======================================
//  melody[] is an array of notes, accompanied by beats[], 
//  which sets each note's relative length (higher #, longer note) 
//int melody[] = {  C,  b,  g,  C,  b,   e,  R,  C,  c,  g, a, C };

int melody[] = { c4, a, a};
int beats[] = { 64, 16, 16};

//int melody[] = { a3, c4, c4, a3s, a3, g3, a3, a3s, b3, c4, d4, c5 };
//int beats[] =  { 16,  4, 32,  32,  8,  4, 32,  32,  32,   32,  32,  64 };
//int beats[]  = { 16, 16, 16,  8,  8,  16, 32, 16, 16, 16, 8, 8 }; 
int MAX_COUNT = sizeof(melody) / 2; // Melody length, for looping.

// Set overall tempo
long tempo = 10000;
// Set length of pause between notes
int pause = 1000;
// Loop variable to increase Rest length
int rest_count = 100; //<-BLETCHEROUS HACK; See NOTES

// Initialize core variables
int tone_ = 0;
int beat = 0;
long duration  = 0;

// PLAY TONE  ==============================================
// Pulse the speaker to play a tone for a particular duration
void playTone() {
  long elapsed_time = 0;
  if (tone_ > 0) { // if this isn't a Rest beat, while the tone has 
    //  played less long than 'duration', pulse speaker HIGH and LOW
    while (elapsed_time < duration) {

      digitalWrite(speakerOut,HIGH);
      delayMicroseconds(tone_ / 2);

      // DOWN
      digitalWrite(speakerOut, LOW);
      delayMicroseconds(tone_ / 2);

      // Keep track of how long we pulsed
      elapsed_time += (tone_);
    } 
  }
  else { // Rest beat; loop times delay
    for (int j = 0; j < rest_count; j++) { // See NOTE on rest_count
      delayMicroseconds(duration);  
    }                                
  }                                 
}


void playMelody() {

   // Set up a counter to pull from melody[] and beats[]
  for (int i=0; i<MAX_COUNT; i++) {
    tone_ = melody[i];
    beat = beats[i];

    duration = beat * tempo; // Set up timing

    playTone(); 
    // A pause between notes...
    delayMicroseconds(pause);

  }
  
}

void recordSync(int durationInMillis) {
  digitalWrite(PIN_SAMPLER_RECORD, HIGH);
  delay(600); //Settle period?
  delay(durationInMillis); 
  delay(200); //Settle down period
  digitalWrite(PIN_SAMPLER_RECORD, LOW);
}

void playRecordingSync(int durationInMillis) {
  digitalWrite(PIN_SAMPLER_PLAY, HIGH);
  delay(durationInMillis);
  digitalWrite(PIN_SAMPLER_PLAY, LOW);
}

void startRecordAsync() {
  digitalWrite(PIN_SAMPLER_RECORD, HIGH);
  delay(600); //Settle
}

void stopRecordingAsync() {
    delay(200);
    digitalWrite(PIN_SAMPLER_RECORD, LOW);
}

void playbackRecordingAsync() {
  digitalWrite(PIN_SAMPLER_PLAY, HIGH);
}

void stopPlaybackRecordingAsync() {
  digitalWrite(PIN_SAMPLER_PLAY, LOW);
}

void playBass()
{
  motorArmBass.run(BACKWARD);
  delay(100);
  motorArmBass.run(RELEASE); 
}

void setUSDistances() 
{
	distanceForward = getUSDistance();
	distanceLeft = getUSDistanceLeft();
	distanceRight = getUSDistanceRight();
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


void playAJingle() {
  startRecordAsync();
  
  playMelody();
  bassBeat();
  delay(50);
  bassBeat();
  delay(50);
  bassBeat();
  delay(250);
  bassBeat();
  delay(250);
  bassBeat();
  delay(100);
  bassBeat();
 
  /*
  playMelody();
  
  bassBeat();
  delay(50);
  bassBeat();
*/  
  
  stopRecordingAsync();
  
  delay(5000);
  
  playRecordingSync(3000);
  
  delay(1000);
    
}



void loop() {
  
  if (!isDriveForward && canDriveForward) 
  {
	driveForwardBegin();
  }
  else if (isDriveForward && canDriveForward && getUSDistance() <= FORWARD_HALT_DISTANCE)
 {
        driveHalt();
  }
  else if (isDriveForward &! canDriveForward)
  {
	driveHalt();
  }
  else if (!isDriveForward &! canDriveForward)
  {	
		distanceForward = getUSDistance();
		
		if (distanceForward > FORWARD_HALT_DISTANCE)
		{
			driveForwardBegin();
		}
		else
		{
			distanceLeft = getUSDistanceLeft();
			distanceRight = getUSDistanceRight();
			
			// do one more pass if distance measurement failed
			if (distanceLeft <= 0) distanceLeft = getUSDistanceLeft();
			if (distanceRight <= 0) distanceRight = getUSDistanceRight();
			
			if (distanceLeft <= 0 && distanceRight <= 0)
			{
				driveBackward(4000);
			}
			else if (distanceLeft != 0 && distanceLeft > distanceRight)
			{
				driveRotateLeft(1400);
			}
			else if (distanceRight != 0 && distanceRight > distanceLeft)
			{
				driveRotateRight(1400);
			}
		}
  }
  
/*  
  
  
  Serial.print("L: ");
  Serial.println(distanceLeft);
  delay(500);
  Serial.print("F: ");
  Serial.println(distanceForward);
  Serial.print("R: ");
  Serial.println(distanceRight);
  
 if (distanceForward > 5)
 {
    driveForward(2000);
 } else {
    //Were close to something. Make some noise!
    playAJingle();
    if (distanceLeft > distanceRight)
    {
      driveBackward(4000);
      driveRotateLeft(1400);
    } else 
    {
       driveBackward(4000);
       driveRotateRight(1400);
    }
 }
 */
}


