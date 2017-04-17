
// INCLUDED LIBRARIES
#include "neopixel.h"
#include "math.h"


// NEOPIXEL DEFINITIONS
#define PIXEL_PIN D1 //NeoRing
#define PIXEL_COUNT 12
#define PIXEL_TYPE SK6812RGBW
Adafruit_NeoPixel strip = Adafruit_NeoPixel(PIXEL_COUNT, PIXEL_PIN, PIXEL_TYPE);
    
// RGB LED INTS
int redPin = A4;    // RED pin of the LED to PWM pin **A4**
int greenPin = D2;  // GREEN pin of the LED to PWM pin **D0**
int bluePin = D3;   // BLUE pin of the LED to PWM pin **D1**
int redValue = 255; // Full brightness for an Cathode RGB LED is 0, and off 255
int greenValue = 255; // Full brightness for an Cathode RGB LED is 0, and off 255
int blueValue = 255; // Full brightness for an Cathode RGB LED is 0, and off 255</td>

// SOFTPOT INTS
int softPotPin = A0; // Define a pin that we'll place the FSR on
//int softPotReading = 0; // Create a variable to hold the FSR reading
int softPotValue = 0; 
const int numSamples = 5;
int softPotSamples[numSamples];
int softPotSmoothedValue = 0;


void setup()
{
Serial.begin(9600); // Start Serial
pinMode( redPin, OUTPUT);
pinMode( greenPin, OUTPUT);
pinMode( bluePin, OUTPUT);
Particle.subscribe("LUMIN_HIGH", ledHIGH);
Particle.subscribe("LUMIN_OFF", ledOFF);
Serial.println("setUpComplete");
strip.begin(); // Lets get these lights going
strip.show(); // Let there be light
for(int i=0; i< numSamples; i++) softPotSamples[i]= 0;
analogWrite( redPin, redValue);
analogWrite( greenPin, greenValue); 
analogWrite( bluePin, blueValue);
delay (1000);
}

void loop()
{
// Use analogRead to read the photo cell reading
// This gives us a value from 0 to 4095
softPotValue = analogRead(softPotPin);
smoothSoftPOT();
Serial.println(softPotSmoothedValue);
//Serial.println(softPotValue);
int ringBrightness = map(softPotSmoothedValue, 0, 3000, 0, 255);
int ringColor = map(softPotSmoothedValue, 0, 3000, 0, 255);
if (softPotSmoothedValue > 500){
    Particle.publish( "LUMIN_HIGH", PUBLIC);
}
if (softPotSmoothedValue < 200){
    Particle.publish( "LUMIN_OFF", "0", PUBLIC);
}
for (int i=0; i < strip.numPixels(); i++) {
strip.setBrightness(ringBrightness);
strip.setPixelColor (i,ringColor,0,0,55);
strip.show();
}
// wait 1/10th of a second and then loop
delay(1000);
}


void smoothSoftPOT(){

	int avg = 0;
	for( int i = 1; i < numSamples; i++ )
	{
		softPotSamples[i-1] = softPotSamples[i];
		avg += softPotSamples[i];
	}
  softPotSamples[numSamples-1] = softPotValue;
  avg += softPotSamples[numSamples-1];

	softPotSmoothedValue = avg / numSamples;

}

int ledHIGH(const char*event, const char*data)
{
   // write the mixed color
   analogWrite( redPin ,0);
   analogWrite( greenPin ,0);
   analogWrite( bluePin ,50);
Serial.println("SUCCESSHIGH");
}

int ledOFF(const char*event, const char*data)
{

   // write the mixed color
   analogWrite( redPin ,50);
   analogWrite( greenPin ,0);
   analogWrite( bluePin , 0);
   Serial.println("SUCCESSOFF");
}