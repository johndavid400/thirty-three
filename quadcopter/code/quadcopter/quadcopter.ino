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

// Name Analog input pins
int gyro_pin = 2; // connect the gyro Y axis (4.5x output) to Analog input 1
int accel_pin = 0; // connect the accelerometer X axis to Analog input 5
int steeringPot = 3; // connect the steering potentiometer to Analog input 3
int gainPot = 4; // connect the gain potentiometer to Analog input 2

// value to hold the final angle
float angle = 0.00;
// the following 2 values should add together to equal 1.0
float gyro_weight = 0.98;
float accel_weight = 0.02;
// accelerometer values
int accel_reading;
int accel_raw;
int accel_avg = 0;
int accel_offset = 428;
float accel_angle;
float accel_scale = 0.01;

//gyroscope values
int gyro_avg = 0;
int gyro_offset = 402;
int gyro_raw;
int gyro_reading;
float gyro_rate;
float gyro_scale = 0.01;
// 01 by default
float gyro_angle;
float loop_time = -0.05;

// timer variables
int last_update;
int cycle_time;
long last_cycle = 0;

void setup(){

  Serial.begin(9600);

  pinMode(throttle, INPUT);
  pinMode(front_back, INPUT);
  pinMode(left_right, INPUT);

  pinMode(motor_front, OUTPUT);    
  pinMode(motor_back, OUTPUT);    
  pinMode(motor_left, OUTPUT);    
  pinMode(motor_right, OUTPUT);    
}

void loop(){
  read_rc();
  sample_accel();
  sample_gyro();
  calculate_angle();
  time_stamp();
}

void read_rc(){

}

void write_motors(){

}

void sample_accel(){
  // Read and convert accelerometer value
  accel_reading = analogRead(accel_pin);
  accel_raw = accel_reading - accel_offset;
  accel_raw = map(accel_raw, -130, 130, -90, 90);
  accel_angle = (float)(accel_raw * accel_scale);
}

void sample_gyro(){
  // Read and convert gyro value
  gyro_reading = analogRead(gyro_pin);
  gyro_raw = gyro_reading - gyro_offset;
  gyro_rate = (float)(gyro_raw * gyro_scale) * -loop_time;
  gyro_angle = angle + gyro_rate;
}

void calculate_angle(){
  angle = (float)(gyro_weight * gyro_angle) + (accel_weight * accel_angle);
}

void time_stamp(){
  // check to make sure it has been exactly 50 milliseconds since the last recorded time-stamp
  while((millis() - last_cycle) < 50){
    delay(1);
  }
  // once the loop cycle reaches 50 mS, reset timer value and proceed
  cycle_time = millis() - last_cycle;
  last_cycle = millis();
}
