import gpiozero as gp
import datetime
from time import sleep

ldr = gp.DigitalInputDevice(15)

while True:
    if ldr.value:
        time = datetime.datetime.now()
        f = open("blink.csv", "a")
        f.write(str(time.year) + "," + str(time.month) + "," + str(time.day) + "," + str(time.hour) + "," + str(time.minute) + "," + str(time.second) + "," + str(time.microsecond) + "\n")
        print(str(time.year) + "," + str(time.month) + "," + str(time.day) + "," + str(time.hour) + "," + str(time.minute) + "," + str(time.second) + "," + str(time.microsecond))
        f.close()
        while ldr.value:
            sleep(0.03)