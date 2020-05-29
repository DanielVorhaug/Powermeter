# To be used for monitoring blinking from powermeter
# Writes data to file "blink.csv". Each line is one blink. Each line is described on format year,month,day,hour,minute,second,microsecond

import gpiozero as gp
import datetime
from time import sleep

ldr = gp.DigitalInputDevice(15) # Number is sensor-pin. Signal should be 3.3V when light is on and 0V when light is off.

while True:
    if ldr.value:
        time = datetime.datetime.now()
        f = open("blink.csv", "a")
        f.write(str(time.year) + "," + str(time.month) + "," + str(time.day) + "," + str(time.hour) + "," + str(time.minute) + "," + str(time.second) + "," + str(time.microsecond) + "\n")
        print(str(time.year) + "," + str(time.month) + "," + str(time.day) + "," + str(time.hour) + "," + str(time.minute) + "," + str(time.second) + "," + str(time.microsecond))
        f.close()
        sleep(0.03)
        while ldr.value:
            sleep(0.03)