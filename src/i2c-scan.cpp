
/*
 *  Project 09-i2c-scan
 *
 *  Austral - Electronica Digital - 2023 - EAM
 *
 * 	i2c-scan.cpp
 * 		Scans for i2c devices
 *      This program tests the standard 7 bit address space
 *
 *  For running in ESP32
 */

/*
 * 	System includes
 */

#include <Arduino.h>

#include <Wire.h>

//  Public functions

void
setup(void)
{
    Wire.begin();
    Serial.begin(BAUD);
    while (!Serial)
    ;
    Serial.printf("\nI2C Scanner\n");
}

void
loop(void)
{
    int error, address; // variable for error and I2C address
    int nDevices;

    Serial.printf("\n\n----- Scanning -----\n");

    nDevices = 0;
    for (address = 1; address < 127; address++)
    {
        // The i2c_scanner uses the return value of
        // the Write.endTransmisstion to see if
        // a device did acknowledge to the address.
        Wire.beginTransmission(address);
        error = Wire.endTransmission();

        switch(error)
        {
            case 0:
                Serial.printf("I2C device found at address 0x%02X !\n", address);
                nDevices++;
                break;
            case 4:
                Serial.printf("Unknown error at address 0x%02X !\n", address);
                break;
        }
    }
    if (nDevices == 0)
        Serial.printf("No I2C devices found\n");
    Serial.printf("----- done -----\n");

    delay(5000); // wait 5 seconds for the next I2C scan
}
