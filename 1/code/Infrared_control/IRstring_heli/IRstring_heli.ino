// This code is intended to decode an Infrared remote using a standard Infrared receiver  from Radio Shack
// This code is tested on an Arduino Mega
// Connect the IR detector input pin to Arduino D
// JDW 2012

int ledPin = 13; // optional LED on pin 13
int pulse_pin = 12; // connect IR receiver - I used pin 21, but you can change this if using a regular Arduino, any pin will work.
int pulse_val = 0; // create a variable for the pulse values from the IR detector
boolean reading = false; // a variable to check and see if the last available pulse was recently
int loop_counter = 0; // counter to check loop cycles
String IRstring = ""; // initiate an empty String object

int m1_A = 8;     //define I1 interface
int m1_B = 11;    //define I2 interface 
int m1_pwm = 9;   //enable motor A

int m2_A = 12;    //define I3 interface 
int m2_B = 13;    //define I4 interface 
int m2_pwm = 10;  //enable motor B

void setup() {   
  // start serial monitor at 9600 bits per second
  Serial.begin(9600);
  // create OUTPUT for led on arduino pin 13
  pinMode(ledPin, OUTPUT);
  // input pulse signal from infrared remote
  pinMode(pulse_pin, INPUT);
  // Create motor outputs
  pinMode(m1_A, OUTPUT);
  pinMode(m1_B, OUTPUT);
  pinMode(m1_pwm, OUTPUT);
  pinMode(m2_A, OUTPUT);
  pinMode(m2_B, OUTPUT);
  pinMode(m2_pwm, OUTPUT);  
}

void pulse(){
  // use the pulseIn() function to check the length of each pulse
  pulse_val = pulseIn(pulse_pin, HIGH, 10000);
}

void booleanize(){
  // this function changes the pulse readings of 500 microseconds and 1100 microseconds into 0 or 1 boolean values.
  if (pulse_val > 750){
    pulse_val = 1;
  }
  else {
    pulse_val = 0;
  }
}

void loop() {
  pulse(); // get a pulse reading from the IR sensor
  // now check to see if it is a pulse was read
  if (pulse_val > 0){
    digitalWrite(ledPin, HIGH); // when a pulse is being read, turn on the LED on pin 13
    reading = true; // assert that we are still reading signals
    booleanize(); // convert each pulse into a boolean 0 or 1
    IRstring = IRstring + pulse_val; // append each new value to a string data object instead of an array
    loop_counter = 0; // since we just read a pulse, reset the pulse counter to 0
  }
  // if the pulse is not greater than 0...
  else {
    // if this is the first 0 reading after a set of pulses, go ahead and close the string out and read the pulses
    if (reading == true){
      Serial.println(IRstring); // Print the full String
      IRstring = "";  // set the string object to be empty ""
    }
    reading = false; // since we are no longer reading a pulse anymore, set the reading value to false
    loop_counter++; // increment the loop counter
    // check to see if the loop count has reached 50 without receiving a signal
    if (loop_counter > 50){
      loop_counter = 0; // if so, reset the counter
    }
  }
  digitalWrite(ledPin, LOW); // turn off the LED


  switch (8) {
  case '010':    
    digitalWrite(2, HIGH);
    break;
  case 'b':    
    digitalWrite(3, HIGH);
    break;
  case 'c':    
    digitalWrite(4, HIGH);
    break;
  case 'd':    
    digitalWrite(5, HIGH);
    break;
  case 'e':    
    digitalWrite(6, HIGH);
    break;
  default:
    // turn all the LEDs off:
    for (int thisPin = 2; thisPin < 7; thisPin++) {
      digitalWrite(thisPin, LOW);
    }
  } 


}


 
