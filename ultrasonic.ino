#define ECHOPIN 39        // Pin to receive echo pulse
#define TRIGPIN 42        // Pin to send trigger pulse
#define ALERTPIN 4       // Pin to buzzer
#define GROUNDPIN 38

 
void setup()
{
  Serial.begin(115200);
  pinMode(ECHOPIN, INPUT);
  pinMode(TRIGPIN, OUTPUT);
//  pinMode(ALERTPIN, OUTPUT);
  pinMode(GROUNDPIN, INPUT);
  digitalWrite(GROUNDPIN, LOW);
}

void loop()
{
  // Start Ranging
  digitalWrite(TRIGPIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIGPIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGPIN, LOW);
  // Compute distance
  float distance = pulseIn(ECHOPIN, HIGH);
  distance= distance/58;
  Serial.println(distance);
  delay(100);
}
