//Definitions  
const int HR_RX = 7;
const int ledPin = 13;
byte oldSample, sample;

void setup() {
  Serial.begin(9600);
  pinMode (HR_RX, INPUT);  //Signal pin to input  
  delay(3000);
  Serial.println("Waiting for heart beat...");

  //Wait until a heart beat is detected  
  while (!digitalRead(HR_RX)) {};
  
  pinMode(ledPin, OUTPUT);
  delay(3000);
  Serial.println ("Heart beat detected!");
  
}

void loop() {
  
  sample = digitalRead(HR_RX);  //Store signal output 
  if (sample && (oldSample != sample)) {
    digitalWrite(ledPin, HIGH);   // set the LED on
    delay(10);                    // need to wait between on and off (can we faid here?)
    digitalWrite(ledPin, LOW);    // set the LED off
    Serial.println("Beat");
  }
  oldSample = sample;           //Store last signal received 
  
}
  
