int ledPin = 13; // optional LED on pin 13
String IRstring = ""; // create an empty String object 
char incomingByte;
void setup() {   
  // start serial monitor
  Serial.begin(9600);
  //led on arduino pin 13
  pinMode(ledPin, OUTPUT);
}

void loop() {

  // send data only when you receive data:
  if (Serial.available() > 0) {
    // read the incoming byte:
    incomingByte = Serial.read();
    IRstring = IRstring + incomingByte;
    Serial.print("01234");
    Serial.println("");
    Serial.print(IRstring);
    Serial.println("");
  }
  else {
    if (IRstring.substring(0,4) == "0"){
      blink(1000);
    }
    else if (IRstring.substring(0,4) == "01"){
      blink(750);
    }
    else if (IRstring.substring(0,4) == "012"){
      blink(500);
    }
    else if (IRstring.substring(0,4) == "0123"){
      blink(200);
    }
    else {
      digitalWrite(ledPin, LOW);
    }
    
  }
}

void blink(int time){
  digitalWrite(ledPin, HIGH);
  delay(time);
  digitalWrite(ledPin, LOW); 
  delay(time);0
  
}
