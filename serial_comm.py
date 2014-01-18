import fluidsynth
import time
import sys
import serial
import math

fs = fluidsynth.Synth()
fs.start(driver='alsa')

# Load the accordion soundfont
sfid = fs.sfload("accordion.sf2")
fs.program_select(0, sfid, 0, 0)

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


print("Finished init\n")

while True:
    try:
        if ser.inWaiting():
            x = ser.readline()
            if x.strip() and x != '':
                print x
                x = int(math.fabs(float(x)))
                fs.noteon(0, 60, x);
    except serial.serialutil.SerialException:
        pass
