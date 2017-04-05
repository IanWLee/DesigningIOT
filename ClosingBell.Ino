// FINAL CODE
// The Closing (Camp)Bell Ambient Stock Tracker
// Ian Lee, Himanshu Rasam

Servo myservo;  // create servo object to control a servo
int pos = 0;    // variable to store the servo position
int stock_analysis= 0;
int ledGreen = D0;
int ledRed = D1;
void setup()
{
 myservo.attach(D3);  // attaches the servo on pin 0 to the servo object
 Particle.function ("newData", newData);
 // Set up our pins for output
  Particle.function("ledGreen", ledControlG);
  Particle.function("ledRed", ledControlR);
  pinMode(ledGreen, OUTPUT);
  pinMode(ledRed, OUTPUT);
  digitalWrite(ledGreen, LOW);
  digitalWrite(ledRed, LOW);
}
void loop()
{
}
int newData( String s_a)
{
 Serial.print( "Received = ");
 Serial.println( s_a );
 // if the first row is an decimal number and we wanted to extract
 // it from the string.. we would do this.
 // find the index of the first comma in the string
 int spacePos = s_a.indexOf(",");
 // create a substring from the first character to the first comma
 // and convert that to a floating point (decimal number).
 float spend = s_a.substring(0, spacePos ).toFloat();
 stock_analysis = spend;
 // Return 1 to say completed successfull
 return 1;
}
void indicator()
{
 if (stock_analysis<=3)
 { pos= (int)(130+stock_analysis/3*14);
   myservo.write (pos);
 }
 else if (stock_analysis>3 && stock_analysis<=6 )
 { pos= (int)(130+stock_analysis/3*14);
   myservo.write (pos);
 }
 else if (stock_analysis>6 && stock_analysis<=9 )
 { pos= (int)(130+stock_analysis/3*14);
   myservo.write (pos);
 }
}
int ledControlG(String command)
{
  int state = LOW;
  if(command == "HIGH") state = HIGH;
  else if(command == "LOW") state = LOW;
  else return -1;
  digitalWrite(ledGreen, state);
  digitalWrite(ledRed, LOW);
  return 1;
}
int ledControlR(String command)
{
  int state = LOW;
  if(command == "HIGH") state = HIGH;
  else if(command == "LOW") state = LOW;
  else return -1;
  digitalWrite(ledRed, state);
  digitalWrite(ledGreen, LOW);
  return 1;
}
