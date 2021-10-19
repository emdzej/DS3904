#include "Arduino.h"
#include "Wire.h"
#include "DS3904.h"

int MIN_VALUES[] = { 200, 200, 200 };
int MAX_VALUES[] = { 10000, 20000, 20000 };

DS3904::DS3904(int deviceAddress)
{
  _deviceAddress = deviceAddress;
  _model = DS3904_020;
  init();
}

DS3904::DS3904(int deviceAddress, int model)
{
  _deviceAddress = deviceAddress;
  _model = model;
  init();
}

DS3904::DS3904(int deviceAddress, int model, int minValue, int maxValue)
{
  _deviceAddress = deviceAddress;
  _model = model;
  MIN_VALUES[model] = minValue;
  MAX_VALUES[model] = maxValue;
  init();
}

void DS3904::init() 
{
  _ohmPerStep = (MAX_VALUES[_model] - MIN_VALUES[_model]) / float(STEPS);
}

void DS3904::setValue(byte resistorAddress, byte value)
{
   Wire.beginTransmission(_deviceAddress);
   Wire.write(resistorAddress); 
   Wire.write(value);
   Wire.endTransmission();
   delay(WRITE_DELAY);
}

byte DS3904::getValue(byte resistorAddress)
{
    byte result = 0xFF;
  
    Wire.beginTransmission(_deviceAddress);
    Wire.write(resistorAddress);
    Wire.endTransmission();
    Wire.requestFrom(_deviceAddress, 1);
    if (Wire.available()) result = Wire.read();
  
  return result;
}

void DS3904::setOhmValue(byte resistorAddress, double ohms)
{
  byte value = fromOhms(ohms);  
  setValue(resistorAddress, value);
}

byte DS3904::fromOhms(double ohms) 
{
  return ohms / _ohmPerStep;
}

double DS3904::toOhms(byte value) {
  if ((value & HIGH_Z) == HIGH_Z) return HIGH_Z_OHM;
  return (value * _ohmPerStep) + MIN_VALUES[_model];
}

double DS3904::getOhmValue(byte resistorAddress)
{
  byte value = getValue(resistorAddress);
  return toOhms(value);
}

