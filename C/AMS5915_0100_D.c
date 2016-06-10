// Distributed with a free-will license.
// Use it any way you want, profit or free, provided it fits in the licenses of its associated works.
// AMS5915_0100_D
// This code is designed to work with the AMS5915_I2CS_0100-D I2C Mini Module available from ControlEverything.com.
// https://www.controleverything.com/products

#include <stdio.h>
#include <stdlib.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <fcntl.h>

void main()
{
	// Create I2C bus
	int file;
	char *bus = "/dev/i2c-1";
	if((file = open(bus, O_RDWR)) < 0)
	{
		printf("Failed to open the bus. \n");
		exit(1);
	}
	// Get I2C device, AMS5915_0100_D I2C address is 0x28(40)
	ioctl(file, I2C_SLAVE, 0x28);

	// Read 4 bytes of data
	// pressure msb, pressure lsb, temp msb, temp lsb
	char data[4] = {0};
	if(read(file, data, 4) != 4)
	{
		printf("Erorr : Input/output Erorr \n");
	}
	else 
	{
		// Convert the data
		int pres = ((data[0] & 0x3F) * 256 + data[1]);
		int temp = (data[2] * 256 + (data[3] & 0xE0)) / 32;
		float pressure = ((pres - 1638.0) / ((13107.0) / 10.0));
		float cTemp = ((temp * 200.0) / 2048) - 50.0;
		float fTemp = (cTemp * 1.8 ) + 32;

		// Output data to screen
		printf("Pressure is : %.2f mbar \n", pressure);
		printf("Temperature in Celsius : %.2f C \n", cTemp);
		printf("Temperature in Fahrenheit : %.2f F \n", fTemp);
	}
}
