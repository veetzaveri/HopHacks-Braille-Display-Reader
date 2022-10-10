#include <basicMPU6050.h> 

basicMPU6050<> imu;

void setup() {
  imu.setup();
  Serial.begin(38400);
}
void loop() {  
  Serial.print(millis());
  Serial.print(",");
  Serial.print(map(imu.rawAx(), -32768, 32768, -500, 500));
  Serial.print(",");
  Serial.println(map(imu.rawAy(), -32768, 32768, -500, 500));
}
