# Distributed with a free-will license.
# Use it any way you want, profit or free, provided it fits in the licenses of its associated works.
# AMS5915_0100_D
# This code is designed to work with the AMS5915_I2CS_0100-D I2C Mini Module available from ControlEverything.com.
# https://www.controleverything.com/products

import smbus
import time

# Get I2C bus
bus = smbus.SMBus(1)

# AMS5915_0100_D address, 0x28(40)
# Read data back, 4 bytes
# pres MSB, pres LSB, temp MSB, temp LSB
data = bus.read_i2c_block_data(0x28, 4)

# Convert the data
pres = ((data[0] & 0x3F) * 256) + data[1]
temp = ((data[2] * 256) + (data[3] & 0xE0)) / 32
pressure = (pres - 1638.0) / (13107.0 / 10.0)
cTemp = ((temp * 200.0) / 2048) - 50.0
fTemp = (cTemp * 1.8 ) + 32

# Output data to screen
print "Pressure : %.2f mbar" %pressure
print "Temperature in Celsius : %.2f C" %cTemp
print "Temperature in Fahrenheit : %.2f F" %fTemp
