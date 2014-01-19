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

# Find the first open Serial Port
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

pitchPrev = 0

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
                intensity = intensity if x < 120 else 120
                if pitch != pitchPrev:
                    fs.noteoff(0, 59+pitchPrev)
                if pitch != 0:
                    fs.noteon(0, 59 + pitch, intensity)
                pitchPrev = pitch
    except serial.serialutil.SerialException and ValueError:
        pass
