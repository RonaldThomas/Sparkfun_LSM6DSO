/*
 * WHO AM I?
 * The ultimate question for an accelerometer...
 * Written for the Teensy 4.0 and Sparkfun LSM6DSO breakout board.
 *    This is free software: you can redistribute it and/or modify it under
 *    the terms of the GNU Affero General Public License as published by the
 *    Free Software Foundation, either version 3 of the License, or (at your 
 *    option) any later version.
 *
 *    This software is distributed in the hope that it will be useful, but
 *    WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *    See the GNU Affero General Public License for more details.
 *
 *    You should have received a copy of the GNU Affero General Public License
 *    along with this software.  If not, see <https://www.gnu.org/licenses/>.
 */


 
#include <Arduino.h>
#include <SPI.h>

#define DATAOUT 11       //COPI
#define DATAIN 12        //CIPO
#define SPICLOCK 13      //SCK
#define CHIPSELECT 10    //CS

void setup()
{

     Serial.begin(115200);
     Serial.println("");
     Serial.println("start");
     SPI.begin();

     // Set SPI pin modes
     //pinMode(SPICLOCK, OUTPUT);
     //pinMode(DATAOUT, OUTPUT);
     //pinMode(DATAIN, INPUT);
     pinMode(CHIPSELECT, OUTPUT);

     // Initialize SPI bus settings
     SPI.beginTransaction(SPISettings(1000000, MSBFIRST, SPI_MODE3));

     digitalWrite(CHIPSELECT, HIGH); //disable device

     delay(10);

     // Write to CTRL_REG1 to take out of power down mode
     digitalWrite(CHIPSELECT, LOW); //enable device
     SPI.transfer(0x20);
     SPI.transfer(0x8F);
     digitalWrite(CHIPSELECT, HIGH);

     delay(10);

     // Read and print WHO_AM_I register
     digitalWrite(CHIPSELECT, LOW); //enable device
     // WHO_AM_I address with bit 0 set to "1" as the device read command
     SPI.transfer(0x8F);
     uint8_t deviceid = SPI.transfer(0x00);
     digitalWrite(CHIPSELECT, HIGH);

     SPI.endTransaction();

     Serial.println(deviceid, HEX);
     delay(1000);
}

void loop()
{
     uint8_t i = 0x8f;
     // for (uint8_t i = 0x80; i < (0x80 + 0x7E); i++)  use this to run thru all addresses
     {
          SPI.beginTransaction(SPISettings(100000, MSBFIRST, SPI_MODE0));
          // Read and print WHO_AM_I register
          digitalWrite(CHIPSELECT, LOW); //enable device  
          // WHO_AM_I address with bit 0 set to "1" as the device read command
          SPI.transfer(i);
          uint8_t deviceid = SPI.transfer(0x00);
          digitalWrite(CHIPSELECT, HIGH);
          Serial.print("res: 0x");
          Serial.print(i, HEX);
          Serial.print("  0x");
          Serial.println(deviceid, HEX); // For the LSM6DSO, the device ID should be 0x6c.
          SPI.endTransaction();
          delay(10);
     }
     //Serial.println("---------------------------------------------------");
     delay(40);
}
