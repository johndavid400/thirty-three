// This code is intended to decode an Infrared helicopter remote using a standard IR receiver from Radio Shack using Interrupts
// This code is tested on an Arduino Mega
// connect 
// JDW 2011

int ledPin = 13; // optional LED on pin 13
int pulse_pin = 14; // connect IR receiver - I used pin 21, but you can change this if using a regular Arduino, any pin will work.
int pulse_val = 0;
boolean reading = false;

int n = 0;
int loop_counter = 0;

String IRstring = "";

void setup() {   
  // start serial monitor
  Serial.begin(9600);
  //led on arduino pin 13
  pinMode(ledPin, OUTPUT);
  // IR signal from helicopter controller
  pinMode(pulse_pin, INPUT);
}

void pulse(){
  pulse_val = pulseIn(pulse_pin, HIGH, 10000);
}

void booleanize(){
  // this function changes the pulse readings of 500 microseconds and 1100 microseconds (the only 2 pulse lengths I could detect) into 1 or 0 boolean values.
  if (pulse_val > 750){
    pulse_val = 1;
  }
  else {
    pulse_val = 0;
  }
}

void loop() {
  // get a pulse reading from the IR sensor
  
   pulse();

  // now check to see if it is above 0
  if (pulse_val > 0){
    digitalWrite(ledPin, HIGH);
    // if so, lets start reading the pulses
    reading = true;
    booleanize();
    // append each new value to a string data object instead of an array
    IRstring = IRstring + pulse_val;
    loop_counter = 0;
  }
  // if the pulse is not greater than 0...
  else {
    // if this is the first 0 reading after a set of pulses, go ahead and close the set out and read the pulses
    if (reading == true){
      // read and decode pulses
      //decode_speed();
      // check for turn
      //decode_turn();
      // check for button
      //decode_button();
      // check and limit the signal so no bad value is written to the H-bridge (above 255)
      //limit_signal();
      // finally, write the values to the motors
      //write_motors();
      
      Serial.print(IRstring);
      Serial.println("");
    }
    reading = false;
    loop_counter++;
    // make sure it has not received a signal in a few seconds before stopping.
    if (loop_counter > 50){
      //m1_stop();
      //m2_stop();
      loop_counter = 0;
    }
  }
  digitalWrite(ledPin, LOW);
}

void write_motors(){
}

void limit_signal(){
}

void decode_turn(){
}

void decode_button(){
}

void decode_speed(){
}

