.. title: Measure PWM Signals for under 5 USD with a Pi Pico Oscillicope
.. slug:  PWM-Signals-Pi-Pico
.. date: 2022-02-14 10:49:58 UTC-08:00
.. tags: electronics
.. category: 
.. description: buiding and using your own cheap oscilliscope for troubleshooting your RC Airplane PWM signals
.. type: text
.. status: draft



If you've ever wondered how your RC car or airplane servos know where to move, then hopefully this will shed some light on the subject. I find electronics concepts are like magic, and when I finally understand them, they feel less like magic and more like superpowers! Unfortunaltey for mechanically minded people (myself included), electronics can be challenging to design and build, and even more challenging to troubleshoot. "If I could only see what is happening inside the wire" you might have found yourself saying. Well, the first step you should take is learn how to use a multimeter. This tool is essential for every electronics tinkerer for measuring voltage, current, and some can measure capcitance, temperature, etc, etc. However, this only gets you so far, as the sample rate of a multimeter is not fast enough to "see" common signals such as `PWM-Pulse Width Modulation <https://en.wikipedia.org/wiki/Pulse-width_modulation>`_, PPM, SBUS, etc. You need an oscilliscope. A couple searches and you will realize that they are really expensive. I ended up buy and really cheap one on Amazon just to see if actually worked, and it does. It is probably limited to not very useful for the practicing electrical engineer, but for me to measure PWM servo signals, it worked. `Quimat 2.4" TFT Digital <https://www.amazon.com/dp/B07QML4LJL?ref=ppx_pop_mob_ap_share>`_. If you expect to do more than just simple pwm measurment, I would save your money and buy a nicer one, OR build your own for a few dollars. 

Another goal of this project was to measure the voltage level of the RC receiver. Most modern electronics use 5v or 3.3v for serial communications or pwm signals. It's important to know what your hardware is generating or needs, and if it can only handle 3.3v, a 5v signal will damage it, soo it's best to check it.  


Hardware and Software
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Assuming you have an android device, here is the equipment you'll need to buy

* $4 - https://www.raspberrypi.com/products/raspberry-pi-pico/  

* $1.5 - https://play.google.com/store/apps/details?id=xyz.fhdm.scoppy


The software and instructions are here on github 

* https://github.com/fhdm-dev/scoppy  


using the app wiki

https://oscilloscope.fhdm.xyz/wiki/Using-the-App


The Math  
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

Classic Analog servos operate on a 50Hz frequency. I am not sure why but thats what it is. this works out to

`50Hz = 50 cycles per second, or 1/50 = 0.02 seconds per cycle = 20 millisecond peroid`

in order to convey information through an analog signal it is done by the length of time the voltage is "on", or "high", and the servo can read that and convert it to a position. An example is when the signal is high for 1.5ms, the servo interprets that as middle.

In summary, we have the following properties of out square wave PWM signal

Duty Cycle = 1-2ms = 1000-2000us
Peroid = 20 ms
Frequency/Frame Rate = 1/20ms = 50 Hz



If you have a true RMS multimeter (I recommend the `Artech A5030 <https://www.sparkfun.com/products/18342>`_
), you can measure the logic voltage if you know the duty cycle of the signal. The A5030 also can measure frequency and duty cycle, so you really dont need an oscillicope for a lot of basic signal analysis.


the math is 


logic voltage * duty cycle = measured voltage

for example 

3.3v * 1ms/20ms = 0.165v
or 
3.3v * 2ms/20ms = 0.33v





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

