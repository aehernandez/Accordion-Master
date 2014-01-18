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
                # Extract 4-bit word used to determine pitch
                pitch = x[:4]
                pitch = int(pitch, 2)
                # Ignore hash and extract integer used to determine intensity
                intensity = x[5:]
                intensity = int(math.fabs(float(intensity)))
                fs.noteon(0, 60 + pitch, intensity);
    except serial.serialutil.SerialException:
        pass
