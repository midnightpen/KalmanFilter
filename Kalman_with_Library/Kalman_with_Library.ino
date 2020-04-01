#include <Wire.h>
#include <VL53L0X.h>
#include <SimpleKalmanFilter.h>

VL53L0X sensor;

SimpleKalmanFilter simpleKalmanFilter(2, 2, 0.01);
const long SERIAL_REFRESH_TIME = 100;
long refresh_time;

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
  float estimated_value = simpleKalmanFilter.updateEstimate(sensorVal);
  
  if (sensorVal <= 1200) {
    Serial.print("\n");
    Serial.print(sensorVal);
    Serial.print("\t");
    Serial.print(estimated_value);
    Serial.print("\t");
    Serial.print(1200);
    Serial.print("\t");
    Serial.print(0);
  }
}
