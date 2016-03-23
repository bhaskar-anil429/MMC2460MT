// Distributed with a free-will license.
// Use it any way you want, profit or free, provided it fits in the licenses of its associated works.
// MMC2460MT
// This code is designed to work with the MMC2460MT_I2CS I2C Mini Module available from ControlEverything.com.
// https://www.controleverything.com/content/Magnetic-Sensor?sku=MMC2460MT_I2CS#tabs-0-product_tabset-2

#include <Wire.h>

// MMC2460MT I2C Address is 0x30(48)
#define Addr 0x30

void setup() 
{
  // Initialise I2C communication
  Wire.begin();
  // Initialise Serial Communication, set baud rate = 9600
  Serial.begin(9600);

  // Start I2C Transmission
  Wire.beginTransmission(Addr);
  // Select command register 0
  Wire.write(0x07);
  // Send measurement command
  Wire.write(0x23);
  // Stop I2C Transmission
  Wire.endTransmission();
  
}

void loop()
{
  unsigned int data[4];
  // Start I2C Transmission
  Wire.beginTransmission(Addr);
  // Select data register
  Wire.write(0x00);
  // Stop I2C Transmission
  Wire.endTransmission();
    
  // Request 4 byte of data
  Wire.requestFrom(Addr, 4);

  // xMag lsb, xMag msb, yMag lsb, yMag msb
  if(Wire.available() == 4)
  {
    data[0] = Wire.read();
    data[1] = Wire.read();
    data[2] = Wire.read();
    data[3] = Wire.read();
    delay(100);
  } 
  delay(300);
     
  // Convert the values
  int xMag = ((data[1] * 256) + data[0]);
  int yMag = ((data[3] * 256) + data[2]);
       
  // Output data to serial monitor
  Serial.print("Magnetic field in X-Axis : ");
  Serial.println(xMag);
  Serial.print("Magnetic field in Y-Axis : ");
  Serial.println(yMag);
  delay(1000); 
}

