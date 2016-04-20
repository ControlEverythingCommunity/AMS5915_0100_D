// Distributed with a free-will license.
// Use it any way you want, profit or free, provided it fits in the licenses of its associated works.
// AMS5915_0100_D
// This code is designed to work with the AMS5915_I2CS_0100-D I2C Mini Module available from ControlEverything.com.
// https://www.controleverything.com/products

import com.pi4j.io.i2c.I2CBus;
import com.pi4j.io.i2c.I2CDevice;
import com.pi4j.io.i2c.I2CFactory;
import java.io.IOException;

public class AMS5915_0100_D
{
	public static void main(String args[]) throws Exception
	{
		// Create I2C bus
		I2CBus Bus = I2CFactory.getInstance(I2CBus.BUS_1);
		// Get I2C device, AMS5915_0100_D I2C address is 0x28(40)
		I2CDevice device = Bus.getDevice(0x28);
		
		// Read 4 bytes of data
		// pressure msb, pressure lsb, temp msb, temp lsb
		byte[] data = new byte[4];
		device.read(data, 0, 4);
		
		// Convert the data
		int pres = ((data[0] & 0x3F) * 256 + (data[1] & 0xFF));
		int temp = ((data[2] & 0xFF)* 256 + (data[3] & 0xE0)) / 32;
		double pressure = ((pres - 1638.0) / ((13107.0) / 10.0));
		double cTemp = ((temp * 200.0) / 2048) - 50.0;
		double fTemp = (cTemp * 1.8 ) + 32;
		
		// Output data to screen
		System.out.printf("Pressure is : %.2f mbar %n", pressure);
		System.out.printf("Temperature in Celsius : %.2f C %n", cTemp);
		System.out.printf("Temperature in Fahrenheit : %.2f F %n", fTemp);
	}
}