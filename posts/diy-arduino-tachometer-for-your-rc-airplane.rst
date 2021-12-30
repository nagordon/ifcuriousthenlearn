.. title: DIY Arduino Tachometer for your RC Airplane
.. slug: diy-arduino-tachometer-for-your-rc-airplane
.. date: 2021-12-29 17:11:39 UTC-08:00
.. tags: electronics
.. description: Build your own IR tachometer for propellor RPM
.. status: published


.. change status from my notes and comments, draft, published


The Project
===============

To properly tune a small gas airplane engine, a tach is essential. I was just going to buy a tower hobbies tachometer for tuning my new Yak 54 gas RC airplane, but instead I spent an entire day build my own, and you can too!

There are some good products out there that work, but you don't have the sastifaction of making it yourself. 

* https://www.towerhobbies.com/product/on-board-digital-tachometer/DLEG5525.html
* https://www.amazon.com/gp/product/B07N77H8D4/ref=ox_sc_act_title_1?smid=A21F9KBNUKR8LM&psc=1


This will show you how to build your own with hopefully a lot less time than it took me. Also, once you get a ground unit working well, you can add an airplane unit and get RPM telemetry when you are flying, but we will leave that for another day. 

The ardupilot documentation has a nice overview of what the software is doing, but we are using an IR sensor instead of a hall effect sensor which requires a magnet, but has less noise.

* https://ardupilot.org/plane/docs/common-rpm.html


I roughly followed this tutorial to create mine

* https://automaticaddison.com/how-to-develop-an-arduino-based-optical-tachometer/


The library for the OLED is here

* https://github.com/olikraus/U8g2_Arduino


The sensor is not perfect and has about 500-1000 RPMs of noise, which isn't great but not sure how you make it better. One thing I noticed is that if you point the IR transmitter and reciever in a little there seems to be less noise. 



Materials
===============

* ardunio pro mini 5v

  * https://www.sparkfun.com/products/11113
  
* IR obstacle sensor HW-201 module
  
  * https://www.amazon.com/HiLetgo-Infrared-Avoidance-Reflective-Photoelectric/dp/B07W97H2WS/ref=sr_1_13?keywords=line+follower+sensor&qid=1640830855&sr=8-13
  
* SSD1306 oled screen
  
  * https://www.uctronics.com/uctronics-0-96-inch-oled-module-12864-128x64-yellow-blue-ssd1306-driver-i2c-serial-self-luminous-display-board-for-arduino-raspberry-pi.html

* 9v battery


Images
===============



Wiring Diagram
^^^^^^^^^^^^^^^^

.. image:: /files/diy-arduino-tachometer-for-your-rc-airplane/gallery/Propellor_Tachometer_Using_Arduino_Wiring_Diagram.jpg
  :width: 500

Finished!
^^^^^^^^^^^^^^^^
Everything is soldered together and ready to test. 

  
.. image:: /files/diy-arduino-tachometer-for-your-rc-airplane/gallery/finished_tach2.jpg
  :width: 500   

I mounted everything on a piece of balsa wood and added shrink wrap for durability. The battery is simply taped on for easy changing.

.. image:: /files/diy-arduino-tachometer-for-your-rc-airplane/gallery/mounted_tach_screen.jpg
  :width: 500


.. /image:: /files/diy-arduino-tachometer-for/your-rc-airplane/gallery/tach_screen.jpg
  :width: 500

\

.. image:: /files/diy-arduino-tachometer-for-your-rc-airplane/gallery/mounted_tach_battery.jpg
  :width: 500


 


The code
===============


.. code-block:: C
   :number-lines:

    /*
    PropTach v0.2
    Neal Gordon
    */

    // Import OLED library
    #include <Arduino.h>
    #include <U8x8lib.h>

    #ifdef U8X8_HAVE_HW_SPI
    #include <SPI.h>
    #endif

    // The complete list is available here: https://github.com/olikraus/u8g2/wiki/u8x8setupcpp
    U8X8_SSD1306_128X64_NONAME_HW_I2C u8x8(/* reset=*/ U8X8_PIN_NONE);

    // The number of blades on the propeller. Adjust accordingly.
    const unsigned int BLADE_COUNT = 2;
    
    // Volatile keyword is used with interrupts
    // This variable is subject to change inside an interrupt
    // service routine
    volatile unsigned int myinterrupts = 0;
    unsigned int myinterrupts_print;


    // Used for capturing the rpm (revolutions per minute)
    unsigned int rpm;
    unsigned int rpm_print;

    void setup()
        {
        Serial.begin(9600);
        
        u8x8.begin();
        u8x8.setPowerSave(0);
        u8x8.setFont(u8x8_font_amstrad_cpc_extended_r);  // u8x8_font_amstrad_cpc_extended_r , u8x8_font_chroma48medium8_r
        // u8x8_font_amstrad_cpc_extended_f
        // u8x8_font_chroma48medium8_r

        u8x8.drawString(0,0,"PropTach v0.2");  // line 0
        u8x8.drawString(0,1,"-------------");  // line 1
        u8x8.drawString(0,2,"Blades");         // line 2
        u8x8.setCursor(0, 3);                  // line 3
        u8x8.print(BLADE_COUNT);               // line 3
        u8x8.drawString(0,5,"RPM");            // line 4
        u8x8.drawString(0, 6, "     ");


        // The Infrared phototransistor is connected to pin 2.
        // Interrupt triggers when signal goes from HIGH to LOW
        // on pro mini arduino must use pins 2 or 3 for interrupts
        // file:///C:/Program%20Files%20(x86)/Arduino/reference/www.arduino.cc/en/Reference/AttachInterrupt.html
        attachInterrupt(digitalPinToInterrupt(3), isr_break_count, FALLING); 
        
        }


    void isr_break_count()
        { 
        myinterrupts++;
        }



    // the loop routine runs over and over again forever:
    void loop() 
        {

        // Update time and rpm every second
        delay(300);

        // Don't process interrupts during this calculation
        noInterrupts();

        // Calculate the RPM. If a 3-blade propeller, 3 breaks
        // per second would yield 1 rpm, which is 60 rpm. 
        rpm = (60 * myinterrupts) / BLADE_COUNT;
        rpm_print = rpm;
        myinterrupts_print = myinterrupts;
        
        myinterrupts = 0;
        rpm = 0;

        // Restart interrupts
        interrupts();

        //  Serial.print("interrupts: ");
        //  Serial.print(myinterrupts_print);
        //  Serial.print("\t"); 

        Serial.print("rpm: ");
        Serial.print(rpm_print);
        Serial.print("\t"); 

        Serial.print("\r\n"); 

        u8x8.drawString(0, 6, "     ");
        u8x8.drawString(0, 6, String(rpm_print).c_str());

        }




Stay Curious!

