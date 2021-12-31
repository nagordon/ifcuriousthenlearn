.. title: analog airspeed sensor voltage divider for ardupilot
.. slug: analog-airspeed-sensor-voltage-divider
.. date: 2021-12-30 10:49:58 UTC-08:00
.. tags: electronics
.. category: 
.. description: use a 5v analog airspeed indicator on a 3.3v ADC 
.. type: text
.. status: published


I have a handful of old analog pitot airspeed sensors that I would like to use, but takes a little work to safely use them without frying your board. This was also a project to help me understand how to set up generic analog sensors using voltage dividers. I would not necessarily recommend buying analog sensors in 2021, as they are hard to find, and most new airspeed sensors are digital and use i2c protocol, and work great out of the box. I have adapted these old sensors to use the RSSI ADC port of newer controllers, but to do so safely we need to reduce the max signal volage to 3.3v. A simple voltage divider will take care of this. 

Note this concept can be used with any analog sesnors on arduino or ardupilot/INAV/PX4 flight controllers.

I originally followed this tutorial to get started, but made a minor change to the resistors, and wanted to share my design. Thanks @pspychalski for your tutorial. 

* https://quadmeup.com/how-to-connect-apm-airspeed-sensor-pitot-tube-to-inav/


Hardware  
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
The hardware I used is

* ardunio pro mini 5v

  * https://www.sparkfun.com/products/11113

* sparkfun ftdi board for uploading code to arduino

  * https://www.sparkfun.com/products/11113

* DIY drones airspeed sensor

* 2.2kohm resistors


The board looks like this  

.. image:: /files/analog-airspeed-sensor-voltage-divider/back_of_sensor.jpg
  :width: 500

the setup to read the A0 voltage is like so

.. image:: /files/analog-airspeed-sensor-voltage-divider/read_5v_sensor.jpg
  :width: 500

and the arduino code

.. code-block:: C
   :number-lines:

    void setup() {
    Serial.begin(9600);
        }
        void loop() {
        // read the input on analog pin 0:
        int sensorValue = analogRead(A0);
        
        // Convert the analog reading (which goes from 0 - 1023) 
        //   to a voltage range (0 - 5V) of the pro mini 5v:
        float voltage = sensorValue * (5.0 / 1023.0);
        
        Serial.print("Voltage: ");
        Serial.print(voltage);
        Serial.print("\t\r\n");
        }

and using this code we get the raw values up to 5v, which the arduino is OK with but most hobby-grade flight controllers ADC ports are 3.3v and it will likely damage it.

.. image:: /files/analog-airspeed-sensor-voltage-divider/5v_sensor_analog_readplot.png
  :width: 700


Voltage Divider Design  
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^


To design our voltage divider, I referenced this amazing electronics resource, 

`https://ultimateelectronicsbook.com <https://ultimateelectronicsbook.com>`_

sparkfun also has a built-in calculator for checking your numbers and some good background. 

`https://learn.sparkfun.com/tutorials/voltage-dividers/all <https://learn.sparkfun.com/tutorials/voltage-dividers/all>`_

I used python for the calculation of the resistor values to use to get a voltage drop from 5v to 3.3v  

.. code-block:: python
   :number-lines:

    Vin = 5

    R1 = 2.2e3
    R2 = 2.2e3+2.2e3 # two in series

    Vout = Vin * R2 / (R1+R2)
    print("Vin = {}".format(Vin))
    print("Vout = {}".format(Vout))
    print(" resistor ratio R2/R1 = {}".format(R2/R1))

    # Vin = 5
    # Vout = 3.3333333333333335
    # resistor ratio R2/R1 = 2.0


or try your own resistor values to get the desired voltage drop.

.. raw:: html

    <embed>
        <iframe src="https://trinket.io/embed/python/5e297f189f?showInstructions=true" width="100%" height="356" frameborder="0" marginwidth="0" marginheight="0" allowfullscreen></iframe>
    </embed>


So it looks like we need n=3 2.2kOhm resistors to get a drop from 5v to 3.3v. We ultimatley want a 2:1 ratio of resistors, so any values with that ratio should work. And just for fun, because it's easy, I checked my math out with the circuitlab simulation, and everything looks good. Note I used 100 and 200 Ohms but as long as we maintain a 2:1 we will get the same voltage reduction.


`Circuitlab`_ , or `https://www.circuitlab.com/editor/#?id=56c4dkqd8xyq`__ is awesome and easy

.. _Circuitlab: https://www.circuitlab.com/editor/#?id=56c4dkqd8xyq

__ Circuitlab_



.. image:: /files/analog-airspeed-sensor-voltage-divider/circultlab_simulation.png
  :width: 800


Wiring the Voltage Divider  
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

I first tested the circuit like so

.. image:: /files/analog-airspeed-sensor-voltage-divider/read_3_3v_sensor.jpg
  :width: 500

and looking at the analog readings, it is giving me the voltages I expect, which is max=3.3v and min is 0 when you pull vacuum, with a nominal voltage of 1.7v at ambient pressure so it looks like the design is working as expected.

.. image:: /files/analog-airspeed-sensor-voltage-divider/5v_sensor_analog_readplot_converted_to_3_3v.png
  :width: 700


Everything Looks good, so I soldered together the resistors like so, installed some JR 2.54mm pin connectors, and we are ready to fly!

.. image:: /files/analog-airspeed-sensor-voltage-divider/voltage_divider.jpg
  :width: 200


and the final designs for the arduino or to use with the Matek F405-SE controller are here!

.. image:: /files/analog-airspeed-sensor-voltage-divider/wiring_arduinopromini.png
  :width: 800

\

.. image:: /files/analog-airspeed-sensor-voltage-divider/wiring_matekF450SE_controller.png
  :width: 800

A few observations are with this 2:1 voltage divider, the nominal no airspeed voltage is 1.7, and at max pressure, the max voltage is 3.06 , and the min voltage when I pull min negative pressure is zero. So, it is not exactly max of 3.3v, but thats OK. The main goal here is to not damage the ADC on the flight controller. 

Thanks for reading, happy flying, and Stay Curious!

