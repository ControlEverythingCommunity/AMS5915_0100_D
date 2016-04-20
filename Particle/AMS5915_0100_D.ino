// Distributed with a free-will license.
// Use it any way you want, profit or free, provided it fits in the licenses of its associated works.
// AMS5915_0100_D
// This code is designed to work with the AMS5915_I2CS_0100-D I2C Mini Module available from ControlEverything.com.
// https://www.controleverything.com/products

#include <application.h>
#include <spark_wiring_i2c.h>

// AMS5915_0100_D I2C address is 0x28(40)
#define Addr 0x28

float pressure = 0.0, cTemp = 0.0, fTemp = 0.0;
int temp = 0;

void setup()
{
  // Set variable
  Particle.variable("i2cdevice", "AMS5915_0100_D");
  Particle.variable("pressure", pressure);
  Particle.variable("cTemp", cTemp);

  // Initialise I2C communication
  Wire.begin();
  // Initialise Serial
  Serial.begin(9600);
  delay(300);
}

void loop()
{
  unsigned int data[4];

  // Request 4 bytes of data
  Wire.requestFrom(Addr, 4);

  // Read 4 bytes of data
  // pressure msb, pressure lsb, temp msb, temp lsb
  if (Wire.available() == 4)
  {
    data[0] = Wire.read();
    data[1] = Wire.read();
    data[2] = Wire.read();
    data[3] = Wire.read();
  }

  // Convert the data
  pressure = ((data[0] & 0x3F) * 256.0 + data[1]);
  temp = ((data[2] & 0xFF) * 256.0 + (data[3] & 0xE0)) / 32;

  pressure = ((pressure - 1638.0) / ((13107.0) / 10.0));
  cTemp = ((temp * 200.0) / 2048) - 50.0;
  fTemp = (cTemp * 1.8 ) + 32;

  // Output data to dashboard
  Particle.publish("Pressure in mbar: ", String(pressure));
  delay(100);
  Particle.publish("Temperature in Celsius :", String(cTemp));
  delay(100);
  Particle.publish("Temperature in Fahrenheit : ", String(fTemp));
  delay(500);
  
}
