void setup()
{
  Serial.begin(57600);  

  pinMode(4, OUTPUT);
  digitalWrite(4, HIGH);

  pinMode(A0, INPUT);
  digitalWrite(A0, HIGH);  
  
  pinMode(A1, INPUT);
  digitalWrite(A1, HIGH);  

  pinMode(A2, INPUT);
  digitalWrite(A2, HIGH);  

}
int analog_x,analog_y,analog_z;
float vol_x,vol_y,vol_z;
 
void loop()
{
 analog_x=analogRead(0);
 analog_y=analogRead(1);
  analog_z=analogRead(2);
  vol_x=analog_x *5.0/1024;//convert analog_x-->voltage value(v)
  vol_y=analog_y *5.0/1024; // range is 1023
  vol_z=analog_z *5.0/1024;
  
  vol_x -= 3.27;
  vol_y -= 2.85;
  vol_z -= 2.84;
  
  Serial.print("x:");
  Serial.print(vol_x);
  Serial.print(" y:");
  Serial.print(vol_y);
  Serial.print(" z:");
  Serial.println(vol_z);
  delay(200);
}
