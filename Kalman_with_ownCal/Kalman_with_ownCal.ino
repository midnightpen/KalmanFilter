#include <Wire.h>
#include <VL53L0X.h>

VL53L0X sensor;

float err_measure = 1;
float err_estimate = 1;
float pro_variance = 0.01;

float kalman_gain ;
float current_estimate;
float last_estimate;

void setup()
{
  Serial.begin(9600);
  Wire.begin();
  sensor.setTimeout(500);
  if (!sensor.init())
  {
    Serial.println("Failed to detect and initialize sensor!");
    while (1) {}
  }

#if defined LONG_RANGE
  // lower the return signal rate limit (default is 0.25 MCPS)
  sensor.setSignalRateLimit(0.1);
  // increase laser pulse periods (defaults are 14 and 10 PCLKs)
  sensor.setVcselPulsePeriod(VL53L0X::VcselPeriodPreRange, 18);
  sensor.setVcselPulsePeriod(VL53L0X::VcselPeriodFinalRange, 14);
#endif

#if defined HIGH_SPEED
  // reduce timing budget to 20 ms (default is about 33 ms)
  sensor.setMeasurementTimingBudget(20000);
#elif defined HIGH_ACCURACY
  // increase timing budget to 200 ms
  sensor.setMeasurementTimingBudget(200000);
#endif
}

void loop()
{
  float sensorVal = sensor.readRangeSingleMillimeters();
  //  ...................................................................
  kalman_gain = err_estimate/(err_estimate + err_measure);
  current_estimate = last_estimate + kalman_gain * (sensorVal - last_estimate);
  err_estimate =  (1.0 - kalman_gain)*err_estimate + fabs(last_estimate-current_estimate)*pro_variance;
  last_estimate = current_estimate;

  
  if (sensorVal <= 1200) {
    Serial.print("\n");
    Serial.print(sensorVal);
    Serial.print("\t");
    Serial.print(current_estimate);
    Serial.print("\t");
    Serial.print(1200);
    Serial.print("\t");
    Serial.print(0);
  }
  delay(100);
}
