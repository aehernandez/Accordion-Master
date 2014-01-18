from pyo import *
import time
import sys
import serial
import math

for i in range(256):
    try:
        ser = serial.Serial("/dev/ttyUSB{}".format(i) , 9600)
        print "Found open serial port: USB{}".format(i)
        break

    except serial.SerialException and OSError:
        if i == 255:
            print "Fatal Error: No open port found"  
            sys.exit()
            pass

s = Server().boot()
a = Sine(220, 0, 1).out()
s.start()
print("Finished init\n")

while True:
    try:
        if ser.inWaiting():
            x = ser.readline()
            if x.strip() and x != '':
                print x
                x = int(math.fabs(float(x)))
                a.setMul(x*x/20)
    except serial.serialutil.SerialException:
        pass
