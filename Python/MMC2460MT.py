# Distributed with a free-will license.
# Use it any way you want, profit or free, provided it fits in the licenses of its associated works.
# MMC2460MT
# This code is designed to work with the MMC2460MT_I2CS I2C Mini Module available from ControlEverything.com.
# https://www.controleverything.com/content/Magnetic-Sensor?sku=MMC2460MT_I2CS#tabs-0-product_tabset-2

import smbus
import time

# Get I2C bus
bus = smbus.SMBus(1)

# MMC2460MT address, 0x30(48)
# Select Control register, 0x07(7)
#		0x23(35)	Initiate measurement, Continous mode ON, Frequency 1.5Hz
#					No Boost, SET done, No RESET, No Refill Cap
bus.write_byte_data(0x30, 0x07, 0x23)

time.sleep(0.5)

# MMC2460MT address, 0x30(48)
# Read data back from 0x00(0), 4 bytes
# X-Axis LSB, X-Axis MSB, Y-Axis LSB, Y-Axis MSB
data = bus.read_i2c_block_data(0x30, 0x00, 4)

# Convert the data
xMag = data[1] * 256 + data[0]
if xMag > 32767 :
	xMag -= 65536

yMag = data[3] * 256 + data[2]
if yMag > 32767 :
	yMag -= 65536

# Output data to screen
print "Magnetic field in X-Axis : %d" %xMag
print "Magnetic field in Y-Axis : %d" %yMag
