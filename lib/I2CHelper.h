#pragma once
#ifndef I2CHELPER_H
#define I2CHELPER_H

#ifdef TEENSYDUINO
#include <i2c_t3.h>
#else
#include <Wire.h>
#endif

void i2c_Scan(TwoWire& wire)
{
    // // Leonardo: wait for serial port to connect
    // while (!Serial)
    // {
    // }

    Serial.println ();
    Serial.println ("I2C scanner. Scanning ...");
    byte count = 0;

    wire.begin();
    for (byte i = 8; i < 120; i++)
    {
        wire.beginTransmission (i);
        if (wire.endTransmission () == 0)
        {
            Serial.print ("Found address: ");
            Serial.print (i, DEC);
            Serial.print (" (0x");
            Serial.print (i, HEX);
            Serial.println (")");
            count++;
            delay (1);
        }
    }
    Serial.println ("Done.");
    Serial.print ("Found ");
    Serial.print (count, DEC);
    Serial.println (" device(s).");
    Serial.println ("***********");
    Serial.println (" ");
}

#endif // I2CHELPER_H
