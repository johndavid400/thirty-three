// functions for actions in quadcopter sketch

// Name Analog input pins
int x_gyro_pin = 2; // connect the gyro X axis (4.5x output) to Analog input 0
int y_gyro_pin = 2; // connect the gyro Y axis (4.5x output) to Analog input 1
int x_accel_pin = 0; // connect the accelerometer X axis to Analog input 2
int y_accel_pin = 0; // connect the accelerometer Y axis to Analog input 3

// value to hold the final angle
float x_angle = 0.00;
float y_angle = 0.00;

// the following 2 values should add together to equal 1.0
float gyro_weight = 0.98;
float accel_weight = 0.02;

// x accelerometer values
int x_accel_reading;
int x_accel_raw;
int x_accel_avg = 0;
int x_accel_offset = 428;
float x_accel_angle;
float x_accel_scale = 0.01;
// y accelerometer values
int y_accel_reading;
int y_accel_raw;
int y_accel_avg = 0;
int y_accel_offset = 428;
float y_accel_angle;
float y_accel_scale = 0.01;
// x gyroscope values
int x_gyro_avg = 0;
int x_gyro_offset = 402;
int x_gyro_raw;
int x_gyro_reading;
float x_gyro_rate;
float x_gyro_scale = 0.01;
float x_gyro_angle;
// y gyroscope values
int y_gyro_avg = 0;
int y_gyro_offset = 402;
int y_gyro_raw;
int y_gyro_reading;
float y_gyro_rate;
float y_gyro_scale = 0.01;
float y_gyro_angle;

// 01 by default
float loop_time = -0.05;

// timer variables
int last_update;
int cycle_time;
long last_cycle = 0;

void sample_accel(){
  // Read and convert X axis accelerometer value
  x_accel_reading = analogRead(x_accel_pin);
  x_accel_raw = x_accel_reading - x_accel_offset;
  x_accel_raw = map(x_accel_raw, -130, 130, -90, 90);
  x_accel_angle = (float)(x_accel_raw * x_accel_scale);
  // Read and convert Y ayis accelerometer value
  y_accel_reading = analogRead(y_accel_pin);
  y_accel_raw = y_accel_reading - y_accel_offset;
  y_accel_raw = map(y_accel_raw, -130, 130, -90, 90);
  y_accel_angle = (float)(y_accel_raw * y_accel_scale);
}

void sample_gyro(){
  // Read and convert X axis gyro value
  x_gyro_reading = analogRead(x_gyro_pin);
  x_gyro_raw = x_gyro_reading - x_gyro_offset;
  x_gyro_rate = (float)(x_gyro_raw * x_gyro_scale) * -loop_time;
  x_gyro_angle = x_angle + x_gyro_rate;
  // Read and convert Y axis gyro value
  y_gyro_reading = analogRead(y_gyro_pin);
  y_gyro_raw = y_gyro_reading - y_gyro_offset;
  y_gyro_rate = (float)(y_gyro_raw * y_gyro_scale) * -loop_time;
  y_gyro_angle = y_angle + y_gyro_rate;
}

void calculate_angle(){
  x_angle = (float)(gyro_weight * x_gyro_angle) + (x_accel_weight * x_accel_angle);
  y_angle = (float)(gyro_weight * y_gyro_angle) + (y_accel_weight * y_accel_angle);
}

void time_stamp(){
  // check to make sure it has been exactly 50 milliseconds since the last recorded time-stamp
  while((millis() - last_cycle) < 50){ delay(1); }
  // once the loop cycle reaches 50 mS, reset timer value and proceed
  cycle_time = millis() - last_cycle;
  last_cycle = millis();
}
