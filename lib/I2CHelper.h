#pragma once
#ifndef I2CHELPER_H
#define I2CHELPER_H

#ifdef TEENSYDUINO
#include <i2c_t3.h>
#else
#include <Wire.h>
#endif


template <typename WireType>
class I2CExtension
{
public:

    void attach(WireType& w) { wire = &w; }

    void scan()
    {
        Serial.println("I2C scanner. Scanning ...");
        byte count = 0;

        wire->begin();
        for (byte i = 8; i < 120; i++)
        {
            wire->beginTransmission (i);
            if (wire->endTransmission () == 0)
            {
                Serial.print("Found address: ");
                Serial.print(i, DEC);
                Serial.print(" (0x");
                Serial.print(i, HEX);
                Serial.println(")");
                count++;
                delay(1);
            }
        }
        Serial.print("Found ");
        Serial.print(count, DEC);
        Serial.println(" device(s).");
        Serial.println("***********");
        Serial.println(" ");
    }

    uint8_t writeByte(uint8_t device_addr, uint8_t reg_addr, uint8_t data)
    {
        return writeBytes(device_addr, reg_addr, &data, 1);
    }

    uint8_t writeBytes(uint8_t device_addr, uint8_t reg_addr, uint8_t* data, uint8_t size)
    {
        wire->beginTransmission(device_addr);
        wire->write((uint8_t)reg_addr);

        for (uint8_t i = 0; i < size; i++) wire->write((uint8_t) data[i]);
        uint8_t status = wire->endTransmission();
        return status;
    }

    uint8_t writeWord(uint8_t device_addr, uint8_t reg_addr, uint16_t data)
    {
        return writeWords(device_addr, reg_addr, &data, 1);
    }

    uint8_t writeWords(uint8_t device_addr, uint8_t reg_addr, uint16_t* data, uint8_t size)
    {
        wire->beginTransmission(device_addr);
        wire->write(reg_addr); // send address
        for (uint8_t i = 0; i < size; i++)
        {
            wire->write((uint8_t)((data[i] >> 8) & 0x00FF));
            wire->write((uint8_t)((data[i] >> 0) & 0x00FF));
        }
        uint8_t status = wire->endTransmission();
        return status;
    }

    int8_t readByte(uint8_t device_addr, uint8_t reg_addr, uint8_t *data)
    {
        return readBytes(device_addr, reg_addr, data, 1);
    }

    int8_t readBytes(uint8_t device_addr, uint8_t reg_addr, uint8_t *data, uint8_t size)
    {
        wire->beginTransmission(device_addr);
        wire->write(reg_addr);
        wire->endTransmission(false);
        wire->beginTransmission(device_addr);
        wire->requestFrom(device_addr, size);

        int8_t count = 0;
        while (wire->available()) data[count++] = wire->read();
        return count;
    }

    int8_t readWord(uint8_t device_addr, uint8_t reg_addr, uint16_t *data)
    {
        return readWords(device_addr, reg_addr, data, 1);
    }

    int8_t readWords(uint8_t device_addr, uint8_t reg_addr, uint16_t *data, uint8_t size)
    {
        wire->beginTransmission(device_addr);
        wire->write(reg_addr);
        wire->endTransmission(false);
        wire->beginTransmission(device_addr);
        wire->requestFrom(device_addr, (uint8_t)(size * 2));

        bool msb = true;
        int8_t count = 0;
        while (wire->available())
        {
            if (msb) data[count]    = wire->read() << 8;
            else     data[count++] |= wire->read();
            msb = !msb;
        }
        wire->endTransmission();
        return count;
    }

private:

    WireType* wire;
}

#endif // I2CHELPER_H
