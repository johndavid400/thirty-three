// Basic Infrared receiver test - Upload code to Arduino
// Connect IR detector/receiver module Radio Shack (#276-640) to pin D12 (also power/gnd pins)
// Open Serial Monitor on Arduino IDE, set speed to 9600 baud
// Point Infrared remote (TV/VCR/DVD/IR Helicopter, etc..) and push a button
// See values on monitor - should look somthing like "00000010101000000010" +/- a few digits

int pulse_pin = 12; // connect IR receiver to this pin- I used pin D12, but any pin will work.
int pulse_val = 0; // create a variable to store the pulse values from the IR detector
boolean reading = false; // a boolean variable to check if the IR sensor is still receiving a string
String IRstring = ""; // initiate an empty String object to hold all of the booleanized pulse values

void setup() {   
  Serial.begin(9600); // start serial monitor at 9600 bits per second
  pinMode(pulse_pin, INPUT); // input pulse signal from infrared remote
}
void loop() {
   pulse_val = pulseIn(pulse_pin, HIGH, 10000); // get a pulse reading from the IR sensor
  // now check to see if it is any pulse was read from the sensor
  if (pulse_val > 0){
    reading = true; // assert that we are reading a signal
    if (pulse_val > 750){pulse_val = 1;} // booleanize to 1 if above 750uS (closer to 1100uS)
    else {pulse_val = 0;} // booleanize to 0 if below 750uS (closer to 500uS)
    IRstring += pulse_val; // append each new value to the string data object
  }
  else {
    // if this is the first 0 reading after a string, finish that string and print the value
    if (reading == true){
      Serial.println(IRstring); // Print the full String
      IRstring = "";  // reset the string object to be empty "", so we can read the next one
    }
    reading = false; // we are no longer reading a pulse, set the reading boolean to false and wait for a pulse
  }
}
