/*
  ReadAnalogVoltage

  Reads an analog input on pin 0, converts it to voltage, and prints the result to the Serial Monitor.
  Graphical representation is available using Serial Plotter (Tools > Serial Plotter menu).
  Attach the center pin of a potentiometer to pin A0, and the outside pins to +5V and ground.

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/ReadAnalogVoltage

  https://learn.sparkfun.com/tutorials/using-the-arduino-pro-mini-33v

  https://www.sparkfun.com/products/11113
  for the 5v pro mini arduino, the analog read limit is 5v
  for the 3.3v pro mini arduino, the analog read limit is 3.3v

  resistor kit
  https://www.sparkfun.com/products/10969
  

  Voltage dividers
  https://www.allaboutcircuits.com/tools/voltage-divider-calculator/

  https://learn.sparkfun.com/tutorials/voltage-dividers/all


  https://quadmeup.com/how-to-connect-apm-airspeed-sensor-pitot-tube-to-inav/
*/

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
}

// the loop routine runs over and over again forever:
void loop() {
  // read the input on analog pin 0:
  int sensorValue = analogRead(A0);
  // Convert the analog reading (which goes from 0 - 1023) 
  //   to a voltage (0 - 5V) for the pro mini5v:
  float voltage = sensorValue * (5.0 / 1023.0);
  // print out the value you read:
  Serial.print("Voltage: ");
  Serial.print(voltage);
  Serial.print("\t");


  Serial.print("\r\n"); 
  
  //// https://learn.adafruit.com/experimenters-guide-for-metro/circ08-using%20the%20arduino%20serial%20plotter
  
}
