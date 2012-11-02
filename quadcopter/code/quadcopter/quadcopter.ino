// code for quadcopter

// variables for the RC input
int throttle = 4;
int front_back = 5;
int left_right = 6;

// variables for the motor outputs
int motor_front = 3;
int motor_back = 9;
int motor_left = 10;
int motor_right = 11;


void setup(){
  // start serial monitor at 9600bps
  Serial.begin(9600);
  // set up R/C inputs
  pinMode(throttle, INPUT);
  pinMode(front_back, INPUT);
  pinMode(left_right, INPUT);
  // set up motor outputs
  pinMode(motor_front, OUTPUT);
  pinMode(motor_back, OUTPUT);
  pinMode(motor_left, OUTPUT);
  pinMode(motor_right, OUTPUT);
}

void loop(){
  read_rc();         // read r/c inputs
  write_motors();    // write values to the motors
//  sample_accel();    // read accelerometer inputs
//  sample_gyro();     // read gyroscope inputs
//  calculate_angle(); // calculate angle from gyro and accel
//  time_stamp();      // update time stamp for loop cycle
}

void read_rc(){
  // get r/c pulse length from receiver for throttle
  throttle_val = pulseIn(throttle, HIGH, 20000);
  if (throttle_val > 1000 && throttle_val < 2000){
    throttle_val = map(throttle_val, 1000, 2000, 0, 255);
  } else{ throttle_val = 0 }
  // get r/c pulse length from receiver for front_back
  front_back_val = pulseIn(front_back, HIGH, 20000);
  if (front_back_val > 1000 && front_back_val < 2000){
    front_back_val = map(front_back_val, 1000, 2000, -100, 100);
  } else{ front_back_val = 0 }
  // get r/c pulse length from receiver for left_right
  left_right_val = pulseIn(left_right, HIGH, 20000);
  if (left_right_val > 1000 && left_right_val < 2000){
    left_right_val = map(left_right_val, 1000, 2000, -100, 100);
  } else{ left_right_val = 0 }
}

void write_motors(){
  // write values to motors
  motor_front_val = throttle_val + front_back_val;
  motor_back_val = throttle_val - front_back_val;
  motor_left_val = throttle_val + left_right_val;
  motor_right_val = throttle_val - left_right_val;
}

