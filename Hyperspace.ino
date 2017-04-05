// Hyperspace Game
// Ian Lee, David Hoysen, Ruolan Xia
// Design IOT, Carnegie Mellon University
// Feb 2016


// Identify the pins
int fsrPin = A0;
int solenoid = D0;
int currentPressure = 0;
int ledPin = D1;

// General setup fun!
void setup() {

  // What's input and what's output
  pinMode( solenoid , OUTPUT ); // sets pin as output
  pinMode( fsrPin , INPUT); // sets pin as input
  pinMode( ledPin, OUTPUT); // sets pin as output

  digitalWrite(solenoid, LOW); // Set solenoid off
  digitalWrite(ledPin, LOW); // Set LED off

  // Listen for any published event with the name "diot2016/il/position-change"
  // When triggered, pass any info from this event 
  // to a function called 'handlePositionChange'
  Particle.subscribe(  "diot2016/il/position-change" , handlePositionChange );

  Serial.begin(9600);
}

void loop()
{
  // read the value from the sensor
  int currentPressure = analogRead( fsrPin );
  Serial.println( currentPressure );

  // If the sensor is triggered publish an event
  if (currentPressure < 500)
  {
    Particle.publish( "diot2016/dh/position-change");
    delay(1000);
  }
}

// Function to handle the event this device subscribed to
void handlePositionChange(const char *event, const char *data)
{
// Turn on solenoid & LED for 1s then turn them off
  digitalWrite(solenoid, HIGH);
  digitalWrite(ledPin, HIGH);
  delay(1000);
  digitalWrite(solenoid, LOW);
  digitalWrite(ledPin, LOW);

}
