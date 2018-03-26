#include <FastLED.h>

// Number of LED's in strip 
#define NUM_LEDS 20
// Data pin of the led strip  
#define DATA_PIN 12

// Hue change 
uint16_t gHue = 0;
uint8_t  gHueDelta = 10;
uint8_t  BRIGHTNESS = 50;
//Definitions and port-number constants 
const uint8_t HR_RX = 7;
const uint8_t ledPin = 13;
byte oldSample, sample;

// Define the array of leds
CRGB leds[NUM_LEDS];

void setup() {
  
  Serial.begin(9600);
  pinMode (HR_RX, INPUT);  //Signal pin to input  
  delay(1000);             //Wait to print test 
  Serial.println("Waiting for heart beat...");

  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);

  FastLED.setBrightness(  BRIGHTNESS );
  
  //Wait until a heart beat is detected  
  while (!digitalRead(HR_RX)) {};
  
  pinMode(ledPin, OUTPUT);
  delay(1000);           //Wait to print test 
  Serial.println ("Heart beat detected!");
}

void loop() {
  sample = digitalRead(HR_RX);  //Store signal output 
  
  if (sample && (oldSample != sample)) {
    
    //digitalWrite(ledPin, HIGH);   // set the LED on
    //delay(10);                    // need to wait between on and off 
    //digitalWrite(ledPin, LOW);    // set the LED off
    
    gHue += gHueDelta; // compute new hue
    fill_rainbow( leds, NUM_LEDS, gHue, 7); 
    // send the 'leds' array out to the actual LED strip
    FastLED.show(); 
    gHue = gHue % 360; // bring hue back in range
 
    Serial.println("Beat");
  }
  oldSample = sample;           //Store last signal received 
}
