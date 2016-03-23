// Distributed with a free-will license.
// Use it any way you want, profit or free, provided it fits in the licenses of its associated works.
// MMC2460MT
// This code is designed to work with the MMC2460MT_I2CS I2C Mini Module available from ControlEverything.com.
//https://www.controleverything.com/content/Magnetic-Sensor?sku=MMC2460MT_I2CS#tabs-0-product_tabset-2

import com.pi4j.io.i2c.I2CBus;
import com.pi4j.io.i2c.I2CDevice;
import com.pi4j.io.i2c.I2CFactory;
import java.io.IOException;

public class MMC2460MT
{
	public static void main(String args[]) throws Exception
	{
		// Create I2C bus
		I2CBus bus = I2CFactory.getInstance(I2CBus.BUS_1);
		// Get I2C device, MMC2460MT I2C address is 0x30(48)
		I2CDevice device = bus.getDevice(0x30);
		
		// Send measurement command
		device.write(0x07, (byte)0x23);
		Thread.sleep(500);
		
		// Read 4 bytes of data from address 0x00(0)
		// X lsb, X msb, Y lsb, Y msb
		byte[] data = new byte[4];
		device.read(0x00, data, 0, 4);
		
		// Convert data
		int xMag = (((data[1] & 0xFF) * 256) + (data[0] & 0xFF));
		if(xMag > 32767)
		{
			xMag -= 65536;
		}
		
		int yMag = (((data[3] & 0xFF) * 256) + (data[2] & 0xFF));
		if(yMag > 32767)
		{
			yMag -= 65536;
		}
		
		// Output data to screen
		System.out.printf("Magnetic field in X Axis : %d %n", xMag);
		System.out.printf("Magnetic field in Y Axis : %d %n", yMag);
	}
}
