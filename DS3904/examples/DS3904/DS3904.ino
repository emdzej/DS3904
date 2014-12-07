#include "Wire.h"
#include "DS3904.h"

DS3904 resistor(BASE_ADDRESS);

void setup()
{
  Wire.begin();
  Serial.begin(9600);
  resistor.setValue(RESISTOR_0, HIGH_Z);
  // Setting values in ohms is an approximation only
  resistor.setOhmValue(RESISTOR_1, 5000);
  resistor.setValue(RESISTOR_2, 0x7F);
  Serial.println("Values set");
}

void loop() 
{
  byte value;
  
  value = resistor.getValue(RESISTOR_0);
  Serial.print("Resistor 0: ");
  Serial.println(value);
  Serial.print("Resistor 1: ");
  Serial.print(resistor.getOhmValue(RESISTOR_1));
  Serial.println(" Ohms");
  value = resistor.getValue(RESISTOR_2);
  Serial.print("Resistor 2: ");
  Serial.print(value);
  Serial.print(" (");
  Serial.print(resistor.toOhms(value));
  Serial.println(" Ohms)");
  delay(1000);
}
