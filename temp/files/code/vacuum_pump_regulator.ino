#include <SevSeg.h>
SevSeg sevseg; 

/*

Neal Gordon
2020-06-07
vacuum_pump_regulator.ino

code to read a pressure sensor and control relay
https://www.amazon.com/gp/product/B07P99RJ6T/ref=ppx_yo_dt_b_asin_title_o00_s00?ie=UTF8&psc=1

input: -14.5 psi (-1.0 bars) to 30 psi (2.0 bars)
Output: 0.5V -4.5V linear voltage output. 

// http://www.circuitbasics.com/arduino-7-segment-display-tutorial/

*/

// function that returns a float for mapping numbers. Default map only returns integers
float mapfloat(float x, float in_min, float in_max, float out_min, float out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

// global variables

float pressureSensorOffset = 0.0;

// Generally, you should use "unsigned long" for variables that hold time
// The value will quickly become too large for an int to store
unsigned long previousMillis = 0;        // will store last time LED was updated
unsigned long currentMillis = 0;

// interval at which to blink (milliseconds)
const long pumptime = 1000;           
String pumpstate = "off";
String printstring1 = "";

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(57600);

  // set up LCD
  byte numDigits = 4;
  byte digitPins[] = {10, 11, 12, 13};
  byte segmentPins[] = {9, 2, 3, 5, 6, 8, 7, 4};

  bool resistorsOnSegments = true; 
  bool updateWithDelaysIn = false;
  byte hardwareConfig = COMMON_CATHODE; 
  sevseg.begin(hardwareConfig, numDigits, digitPins, segmentPins, resistorsOnSegments);
  sevseg.setBrightness(10);


  // initialize pin to control power supply
  pinMode(A2, OUTPUT);

  // run to calibrate once
  for (int i=0; i<5; i++) {
  //while (millis() < 2000) {
      int pressureSensorOffsetraw = analogRead(A1);
      pressureSensorOffset = mapfloat(pressureSensorOffsetraw, 0,1023,-14.5,30);
      Serial.print("calibrating offset, psi: ");
      Serial.print(pressureSensorOffset);   
      Serial.print("\n");
      //delay(250)   ;
  }
}


// the loop routine runs continiously:
void loop() {

  // read pot resistance
  int targetpresSensorValue = analogRead(A0);
  float targetpressure = -1*mapfloat(targetpresSensorValue, 0,1023,0,10);
  
  Serial.print("target psi: ");
  Serial.print(targetpressure);
  Serial.print("\t");

  // read the input on analog pin 0:
  int presSensorValue = analogRead(A1);
  
  // Convert the analog reading (which goes from 0 - 1023) to 
  // a voltage (0.5 - 4.5V), then to a pressure:
  float pressure = mapfloat(presSensorValue, 0,1023,-14.5,30);// - pressureSensorOffset;

  Serial.print("actual psi: ");
  Serial.print(pressure);

  sevseg.setNumber(pressure,1);
  sevseg.refreshDisplay();  
  
  // check to see if it's time to blink the LED; that is, if the difference
  // between the current time and last time you blinked the LED is bigger than
  // the interval at which you want to blink the LED.
  currentMillis = millis();

  if ( pressure > targetpressure) {
    // run pump to reduce pressure/increase vacuum
    
    // save the time when the pump started
    previousMillis = currentMillis;    
    pumpstate = "on";
    digitalWrite(A2,HIGH);        
  }

  else if ( (pressure <= targetpressure) and (currentMillis - previousMillis >= pumptime) ) {
    // turn on relay/vacuum pump for a minimum of 10 seconds

    // default, pump off
    pumpstate = "off";
    digitalWrite(A2,LOW);
  }

  Serial.print("\tpump "+pumpstate);

  Serial.print("\n");
  //delay(1000);
  
//loop
}
