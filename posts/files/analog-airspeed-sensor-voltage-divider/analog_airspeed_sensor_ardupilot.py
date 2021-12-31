
resistors = [1.5, 4.7, 10, 47, 100, 220, 330, 470, 680,
             1e3 ,2.2e3, 3.3e3, 4.7e3, 10e3, 22e3, 47e3, 100e3, 330e3, 
             1e6]


Vin = 5

R1 = 2.2e3
R2 = 2.2e3+2.2e3 # two in series

Vout = Vin * R2 / (R1+R2)
print("Vin = {}".format(Vin))
print("Vout = {}".format(Vout))
print(" resistor ratio R2/R1 = {}".format(R2/R1))




# https://pyserial.readthedocs.io/en/latest/pyserial.html


import serial.tools.list_ports as port_list
ports = list(port_list.comports())
for p in ports:
    print (p)


import serial
from datetime import datetime

sensor = "DH11"
# serial_port = '/dev/ttyACM0'  # linux
serialPortNum = 'COM14'   # windows
baud_rate = 9600
#path = "%s_LOG_%s.txt" % (str(datetime.now()), sensor)
path = 'C:/Users/neal/Desktop/serialread.txt'
serialPort = serial.Serial(serialPortNum, baud_rate)

# serialPort.close()

with open(path, 'w+') as f:
    while True:
        
        # Read data out of the buffer until a carraige return / new line is found
        serialString = serialPort.readline()   
        
        #serialString = serialString.decode("utf-8") #ser.readline returns a binary, convert to string
        serialString = serialString.decode("Ascii")
        
        # Print the contents of the serial data
        print(serialString)

        
        f.write(serialString)
        
        
        

    