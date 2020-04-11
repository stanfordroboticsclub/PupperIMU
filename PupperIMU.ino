
/*
  Modified from Sparkfun code written by Nathan Seidle

  Nathan Seidle: "
  It takes about 1ms at 400kHz I2C to read a record from the sensor, but we are polling the sensor continually
  between updates from the sensor. Use the interrupt pin on the BNO080 breakout to avoid polling.
  "

  Hardware Connections:
  Connect the I2C pins from the BNO080 breakout to the Teensy. Connect the Teensy to the RaspberryPi with a short USB micro -> USB A cable. 
*/

#include <Wire.h>

#include "SparkFun_BNO080_Arduino_Library.h"
BNO080 myIMU;

long last_print = micros();

void setup()
{
  Serial.begin(500000);
  Serial.println();
  Serial.println("BNO080 IMU Streaming");

  Wire.begin();
  if (myIMU.begin() == false)
  {
    Serial.println("BNO080 not detected at default I2C address. Check your jumpers and the hookup guide. Freezing...");
    while (1);
  }
  Wire.setClock(400000); //Increase I2C data rate to 400kHz
  // The maximum report rate for the rotation vector is 400Hz -> report every 2.5ms
  myIMU.enableRotationVector(10); //Send data update every 10ms
  Serial.println(F("Rotation vector enabled"));
  Serial.println(F("Output in form i, j, k, real, accuracy"));
}

void loop()
{
  if (myIMU.dataAvailable() == true)
  {
    float quatI = myIMU.getQuatI();
    float quatJ = myIMU.getQuatJ();
    float quatK = myIMU.getQuatK();
    float quatReal = myIMU.getQuatReal();
    Serial.print(quatReal, 4);
    Serial.print(F(","));
    Serial.print(quatI, 4);
    Serial.print(F(","));
    Serial.print(quatJ, 4);
    Serial.print(F(","));
    Serial.print(quatK, 4);
    Serial.println();
  }
}
