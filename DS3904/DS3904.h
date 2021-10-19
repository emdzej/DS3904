/*
  DS3904.h - Library for I2C variable resistor/switch
  Created by Michal Jaskolski, 2014-12-06
  Distributed under the MIT Licence
  
  Datasheet can be found here http://datasheets.maximintegrated.com/en/ds/DS3904-DS3905.pdf
http://datasheets.maximintegrated.com/en/ds/DS3904-DS3905.pdf*/

#ifndef DS3904_h
#define DS3904_h

#include "Arduino.h"

#define RESISTOR_0 0xF8
#define RESISTOR_1 0xF9
#define RESISTOR_2 0xFA
#define HIGH_Z 0x80
#define DS3904_010 0
#define DS3904_020 1
#define DS3905_020 2
#define BASE_ADDRESS 0x50
#define WRITE_DELAY 20
#define STEPS 0x80
#define HIGH_Z_OHM 5500000

class DS3904
{
  public:
    DS3904(int deviceAddress);
    DS3904(int deviceAddress, int model);
    DS3904(int deviceAddress, int model, int minValue, int maxValue);
    void setValue(byte resistorAddress, byte value);
    byte getValue(byte resistorAddress);
    void setOhmValue(byte resistorAddress, double ohms);
    double getOhmValue(byte resistorAddress);
    double toOhms(byte value);
    byte fromOhms(double ohms);
  private:
    void init();
    int _deviceAddress;
    int _model;  
    float _ohmPerStep;  
};

#endif
