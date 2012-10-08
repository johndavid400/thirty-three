// This code is intended to decode an Infrared remote using a standard Infrared receiver  from Radio Shack
// This code is tested on an Arduino Mega
// Connect the IR detector input pin to Arduino D12
// JDW 2012

int ledPin = 13; // optional LED on pin 13
int pulse_pin = 12; // connect IR receiver - I used pin 21, but you can change this if using a regular Arduino, any pin will work.
int pulse_val = 0; // create a variable for the pulse values from the IR detector
boolean reading = false; // a variable to check and see if the last available pulse was recently
String IRstring = ""; // initiate an empty String object

void setup() {   
  // start serial monitor at 9600 bits per second
  Serial.begin(9600);
  // create OUTPUT for led on arduino pin 13
  pinMode(ledPin, OUTPUT);
  // input pulse signal from infrared remote
  pinMode(pulse_pin, INPUT);
}

void pulse(){
  // use the pulseIn() function to check the length of each pulse
  pulse_val = pulseIn(pulse_pin, HIGH, 10000);
}

void booleanize(){
  // this function changes the pulse readings of 500 microseconds and 1100 microseconds into 0 or 1 boolean values.
  if (pulse_val > 750){pulse_val = 1;}
  else {pulse_val = 0;}
}

void loop() {
   pulse(); // get a pulse reading from the IR sensor
  // now check to see if it is a pulse was read
  if (pulse_val > 0){
    digitalWrite(ledPin, HIGH); // when a pulse is being read, turn on the LED on pin 13
    reading = true; // assert that we are still reading signals
    booleanize(); // convert each pulse into a boolean 0 or 1
    IRstring = IRstring + pulse_val; // append each new value to a string data object instead of an array
  }
  // if the pulse is not greater than 0...
  else {
    // if this is the first 0 reading after a set of pulses, go ahead and close the string out and read the pulses
    if (reading == true){
      Serial.println(IRstring); // Print the full String
      IRstring = "";  // set the string object to be empty ""
    }
    reading = false; // since we are no longer reading a pulse anymore, set the reading value to false
  }
  digitalWrite(ledPin, LOW); // turn off the LED
}


