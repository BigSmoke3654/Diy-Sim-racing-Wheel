// Author: Chirag Pilania

#include <Encoder.h>
#include <Joystick.h>

// --- Pins ---
#define ENC_CLK 2          // Encoder CLK pin
#define ENC_DT 3           // Encoder DT pin
#define THROTTLE_PIN A2    // Throttle pot
#define BRAKE_PIN A1       // Brake pot
#define CLUTCH_PIN A0      // Clutch pot

// Steering encoder
Encoder steering(ENC_CLK, ENC_DT);

// Setup joystick emulation
Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID, JOYSTICK_TYPE_JOYSTICK,
                   0, 0,     
                   true, true, true, 
                   true, false, false, 
                   false, false,           
                   false, false, false);       

// --- Config ---
const int MAX_STEERING_TICKS = 120;  
const int NUM_SAMPLES = 40;         

int throttleSamples[NUM_SAMPLES] = {0};
int brakeSamples[NUM_SAMPLES]    = {0};
int clutchSamples[NUM_SAMPLES]   = {0};
int sampleIndex = 0;


long lastSteering = 0;

void setup() {
  Serial.begin(9600)
  Joystick.begin();    


  Joystick.setXAxisRange(-1023, 1023);  // Steering
  Joystick.setYAxisRange(0, 1023);      // Brake
  Joystick.setZAxisRange(0, 1023);      // Throttle
  Joystick.setRxAxisRange(0, 1023);     // Clutch

  // Start wheel centered
  steering.write(0);
}


int smoothInput(int rawValue, int* samples) {
  samples[sampleIndex] = rawValue; 

  long sum = 0;
  for (int i = 0; i < NUM_SAMPLES; i++) {
    sum += samples[i];
  }

  return sum / NUM_SAMPLES; 
}

void loop() {
  
  long steerRaw = steering.read();
  steerRaw = constrain(steerRaw, -MAX_STEERING_TICKS, MAX_STEERING_TICKS);

  
  long mappedSteer = map(steerRaw, -MAX_STEERING_TICKS, MAX_STEERING_TICKS, -1023, 1023);

  
  if (abs(mappedSteer - lastSteering) > 1) {
    Joystick.setXAxis(mappedSteer);
    lastSteering = mappedSteer;
  }

  
  int throttleRaw = analogRead(THROTTLE_PIN);
  int throttleSmoothed = smoothInput(throttleRaw, throttleSamples);
  Joystick.setZAxis(throttleSmoothed);

  
  int brakeRaw = analogRead(BRAKE_PIN);
  int brakeSmoothed = smoothInput(brakeRaw, brakeSamples);
  Joystick.setYAxis(brakeSmoothed);

  
  int clutchRaw = analogRead(CLUTCH_PIN);
  int clutchSmoothed = smoothInput(clutchRaw, clutchSamples);
  Joystick.setRxAxis(clutchSmoothed);

  
  sampleIndex++;
  if (sampleIndex >= NUM_SAMPLES) sampleIndex = 0;

  delay(2);
}
