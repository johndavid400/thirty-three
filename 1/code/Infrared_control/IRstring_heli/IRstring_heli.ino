// This code is intended to decode an Infrared remote using a standard Infrared receiver  from Radio Shack
// This code is tested on an Arduino Mega
// Connect the IR detector input pin to Arduino D
// JDW 2012

int ledPin = 13; // optional LED on pin 13
int pulse_pin = 6; // connect IR receiver - I used pin 21, but you can change this if using a regular Arduino, any pin will work.
int pulse_val = 0; // create a variable for the pulse values from the IR detector
boolean reading = false; // a variable to check and see if the last available pulse was recently
int loop_counter = 0; // counter to check loop cycles
String IRstring = ""; // initiate an empty String object

int speed_val = 0;
int turn_val = 0;
int m1_val = 0;
int m2_val = 0;

int m1_dir = 12;  // motor 1 direction
int m1_pwm = 3;   // motor 1 speed

int m2_dir = 13;  // motor 2 direction
int m2_pwm = 11;  // motor 2 speed

int speed_multiplier = 19; // this value determines how much to multiply the speed increment by. Get this number by dividing 255 (total PWM resolution) by the number of speed steps (or resolution) available - in this case 14.

// speed codes are contained in indexes 7, 8, 9, & 10
String speed1 = "0000";
String speed2 = "0010";
String speed3 = "0011";
String speed4 = "0100";
String speed5 = "0101";
String speed6 = "0110";
String speed7 = "0111";
String speed8 = "1000";
String speed9 = "1001";
String speed10 = "1010";
String speed11 = "1011";
String speed12 = "1100";
String speed13 = "1101";
String speed14 = "1110";

// turning codes are contained in indexes 15, 16, & 17
String left1 = "111";
String left2 = "110";
String left3 = "101";
String right1 = "001";
String right2 = "010";
String right3 = "011";

// button codes are contained in indexes 11, 12, and 13
String button_left = "111";
String button_right = "000";



void setup() {
  // start serial monitor at 9600 bits per second
  Serial.begin(9600);
  Serial.println("Serial transmission begin");
  // create OUTPUT for led on arduino pin 13
  pinMode(ledPin, OUTPUT);
  // input pulse signal from infrared remote
  pinMode(pulse_pin, INPUT);
  // Create motor outputs
  pinMode(m1_dir, OUTPUT);
  pinMode(m1_pwm, OUTPUT);
  pinMode(m2_dir, OUTPUT);
  pinMode(m2_pwm, OUTPUT);
}

void pulse(){
  // use the pulseIn() function to check the length of each pulse
  pulse_val = pulseIn(pulse_pin, HIGH, 20000);
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
    reading = true; // assert that we are still reading signals
    booleanize(); // convert each pulse into a boolean 0 or 1
    IRstring += pulse_val; // append each new value to a string data object instead of an array
    loop_counter = 0; // since we just read a pulse, reset the pulse counter to 0


  }
  // if the pulse is not greater than 0...
  else {
    // if this is the first 0 reading after a set of pulses, go ahead and close the string out and read the pulses
    if (reading == true){
      
      Serial.println(IRstring); // Print the full String
      //Serial.println(speed_val);
      IRstring = "";  // set the string object to be empty ""
    }
    reading = false; // since we are no longer reading a pulse anymore, set the reading value to false
    loop_counter++; // increment the loop counter
    // check to see if the loop count has reached 50 without receiving a signal
    if (loop_counter > 100){
      m1_stop();
      m2_stop();
      loop_counter = 0; // if so, reset the counter
    }
  }
  if (IRstring.length() > 19){
    // check speed value
    decode_speed();
    // check for turn
    decode_turn();
    // check for button
    decode_button();
    // check and limit the signal so no bad value is written to the H-bridge (above 255)
    limit_signal();
    // finally, write the values to the motors
    write_motors();
  }
}

void decode_speed(){
  // speed
  if      (IRstring.substring(7,11) == speed1){speed_val = 0;}
  else if (IRstring.substring(7,11) == speed2){speed_val = 20;}
  else if (IRstring.substring(7,11) == speed3){speed_val = 40;}
  else if (IRstring.substring(7,11) == speed4){speed_val = 60;}
  else if (IRstring.substring(7,11) == speed5){speed_val = 80;}
  else if (IRstring.substring(7,11) == speed6){speed_val = 100;}
  else if (IRstring.substring(7,11) == speed7){speed_val = 120;}
  else if (IRstring.substring(7,11) == speed8){speed_val = 140;}
  else if (IRstring.substring(7,11) == speed9){speed_val = 160;}
  else if (IRstring.substring(7,11) == speed10){speed_val = 180;}
  else if (IRstring.substring(7,11) == speed11){speed_val = 200;}
  else if (IRstring.substring(7,11) == speed12){speed_val = 220;}
  else if (IRstring.substring(7,11) == speed13){speed_val = 240;}
  else if (IRstring.substring(7,11) == speed14){speed_val = 255;}
  else    {speed_val = 0;}

//  if      (IRstring.substring(7,11) == speed1){speed_val = 0;}
//  else if (IRstring.substring(7,11) == speed2){speed_val = 2;}
//  else if (IRstring.substring(7,11) == speed3){speed_val = 3;}
//  else if (IRstring.substring(7,11) == speed4){speed_val = 4;}
//  else if (IRstring.substring(7,11) == speed5){speed_val = 5;}
//  else if (IRstring.substring(7,11) == speed6){speed_val = 6;}
//  else if (IRstring.substring(7,11) == speed7){speed_val = 7;}
//  else if (IRstring.substring(7,11) == speed8){speed_val = 8;}
//  else if (IRstring.substring(7,11) == speed9){speed_val = 9;}
//  else if (IRstring.substring(7,11) == speed10){speed_val = 10;}
//  else if (IRstring.substring(7,11) == speed11){speed_val = 11;}
//  else if (IRstring.substring(7,11) == speed12){speed_val = 12;}
//  else if (IRstring.substring(7,11) == speed13){speed_val = 13;}
//  else if (IRstring.substring(7,11) == speed14){speed_val = 14;}
//  else    {speed_val = 0;}

  // now we should scale the 14 speed steps up to the maximum PWM range of 255. 255/14 = 18.21. So we rounded up to 19.
  //  speed_val = speed_val * speed_multiplier;
  m1_val = speed_val;
  m2_val = speed_val;
}

void decode_turn(){
  // turn
  if      (IRstring.substring(15,18) == left1){turn_val = -1;}
  else if (IRstring.substring(15,18) == left2){turn_val = -2;}
  else if (IRstring.substring(15,18) == left3){turn_val = -3;}
  else if (IRstring.substring(15,18) == right1){turn_val = 1;}
  else if (IRstring.substring(15,18) == right2){turn_val = 2;}
  else if (IRstring.substring(15,18) == right3){turn_val = 3;}
  else    {turn_val = 0;}

  // now apply the turn bias to the m1 and m2 values
  switch (turn_val) {
    case -1:
      // left turn 1
      m1_val = speed_val / 2;
      m2_val = speed_val;
      break;
    case -2:
      // left turn 2
      m1_val = 0;
      m2_val = speed_val * 2;
      break;
    case -3:
      // left turn 3
      m1_val = -speed_val;
      m2_val = speed_val;
      break;
    case 1:
      // right turn 1
      m2_val = speed_val / 2;
      m1_val = speed_val;
      break;
    case 2:
      // right turn 2
      m2_val = 0;
      m1_val = speed_val * 2;
      break;
    case 3:
      // right turn 3
      m2_val = -speed_val;
      m1_val = speed_val;
      break;
    default:
      // if nothing else matches
      break;
  }
}

void decode_button(){
  // button
  if (IRstring.substring(11,14) == button_left){
    // left button
    m1_val = -m1_val;
    m2_val = -m2_val;
  }
}

void limit_signal(){
  if (m1_val > 255){
    m1_val = 255;
  }
  else if (m1_val < -255){
    m1_val = -255;
  }
  if (m2_val > 255){
    m2_val = 255;
  }
  else if (m2_val < -255){
    m2_val = -255;
  }
}


void write_motors(){
  // check direction of m1_val and write appropriately
  if (m1_val > 0){
    m1_forward(m1_val);
  }
  else if (m1_val < 0){
    m1_reverse(-m1_val);
  }
  else {
    m1_stop();
  }
  // check direction of m2_val and write appropriately
  if (m2_val > 0){
    m2_forward(m2_val);
  }
  else if (m2_val < 0){
    m2_reverse(-m2_val);
  }
  else {
    m2_stop();
  }
}


// motor functions for Arduino Motor-shield
void m1_forward(int pwm_speed){
  digitalWrite(m1_dir, HIGH);
  analogWrite(m1_pwm, pwm_speed);
}
void m1_reverse(int pwm_speed){
  digitalWrite(m1_dir, LOW);
  analogWrite(m1_pwm, pwm_speed);
}
void m1_stop(){
  digitalWrite(m1_dir, LOW);
  digitalWrite(m1_pwm, LOW);
}
void m2_forward(int pwm_speed){
  digitalWrite(m2_dir, HIGH);
  analogWrite(m2_pwm, pwm_speed);
}
void m2_reverse(int pwm_speed){
  digitalWrite(m2_dir, LOW);
  analogWrite(m2_pwm, pwm_speed);
}
void m2_stop(){
  digitalWrite(m2_dir, LOW);
  digitalWrite(m2_pwm, LOW);
}


