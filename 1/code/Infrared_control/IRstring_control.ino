// This code is intended to decode an Infrared helicopter remote using a standard IR receiver from Radio Shack using Interrupts
// This code is tested on an Arduino Mega
// connect 
// JDW 2011

int ledPin = 13; // optional LED on pin 13
int pulse_pin = 14; // connect IR receiver - I used pin 21, but you can change this if using a regular Arduino, any pin will work.
int pulse_val = 0;
boolean reading = false;
int ir_array[20];
int n = 0;
int loop_counter = 0;
int speed_val = 0;
int turn_val = 0;
int m1_val = 0;
int m2_val = 0;

String IRstring = "";

// define pins for motor 1 - these are standard 4-quadrant H-bridge control pins, you can change these if using a different motor-controller
int m1_AHI = 2;
int m1_ALI = 3;
int m1_BLI = 4;   // 12 on Ardiuno Mega
int m1_BHI = 5;

// define pins for motor 2
int m2_AHI = 8;
int m2_ALI = 9;
int m2_BLI = 10;
int m2_BHI = 11;

void setup() {
  // change the PWM frequency for Timer 1 of Arduino 
  // pins 9 & 10 on standard Arduino or pins 11 and 12 on Arduino Mega
  //TCCR1B = TCCR1B & 0b11111000 | 0x01;
  // change the PWM frequency for Timer 2 of Arduino 
  // pins 3 & 11 on standard Arduino or pins 9 & 10 on Arduino Mega 
  //TCCR2B = TCCR2B & 0b11111000 | 0x01;   
  // start serial monitor
  Serial.begin(9600);
  //led on arduino pin 13
  pinMode(ledPin, OUTPUT);
  // IR signal from helicopter controller
  pinMode(pulse_pin, INPUT);
  // set motor pins as outputs
  pinMode(m1_AHI, OUTPUT);
  pinMode(m1_ALI, OUTPUT);
  pinMode(m1_BHI, OUTPUT);
  pinMode(m1_BLI, OUTPUT);

  pinMode(m2_AHI, OUTPUT);
  pinMode(m2_ALI, OUTPUT);
  pinMode(m2_BHI, OUTPUT);
  pinMode(m2_BLI, OUTPUT);
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
      decode_speed();
      // check for turn
      decode_turn();
      // check for button
      decode_button();
      // check and limit the signal so no bad value is written to the H-bridge (above 255)
      limit_signal();
      // finally, write the values to the motors
      //write_motors();
      
      Serial.print(IRstring);
      Serial.println("");
    }
    reading = false;
    loop_counter++;
    // make sure it has not received a signal in a few seconds before stopping.
    if (loop_counter > 50){
      m1_stop();
      m2_stop();
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

