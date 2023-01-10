import board
import busio
import time
from time import sleep
import struct
import digitalio
import microcontroller
import displayio
import adafruit_displayio_ssd1306
import terminalio
from adafruit_display_text import label
from oled_driver import OLED #update library functions
from mpl115a2_driver import *
import analogio
from adafruit_onewire.bus import OneWireBus
from adafruit_ds18x20 import DS18X20

# Initialize one-wire bus on board pin D5.
ow_bus = OneWireBus(board.GP16)
ds18 = DS18X20(ow_bus, ow_bus.scan()[0])

ideal_pressure = 101.325
sap_conversion_factor = 0.3375 #used to calculate ideal boiling point for water
sap_boiling_add_on = 7 #sap boils 7 degrees celsius above water
water_boiling_point = 100


#initialize sensors
oled = OLED
display = oled.initialize_oled()

#i2c initialization for non OLED devices
sda=board.GP26
scl=board.GP27
i2c=busio.I2C(scl, sda)

#needed to use i2c
i2c.try_lock()
print("i2c.scan(): " + str(i2c.scan()))

barometer = Mpl115A2(i2c) 
barometer.initiate_conversion()

#LED setup
led = digitalio.DigitalInOut(board.GP25)
led.direction = digitalio.Direction.OUTPUT
LED_STATE = False
led.value = LED_STATE

#allow sensors to initialize
time.sleep(1)

def sap_boiling_point(pressure): #found equation on sciencing website
    return (((pressure-ideal_pressure)*sap_conversion_factor)+water_boiling_point+sap_boiling_add_on)

#main loop
while True:
    #LED
    LED_STATE = not LED_STATE
    led.value = LED_STATE

    temperature = ds18.temperature
    pressure = barometer.pressure

    oled.display_data(temperature,sap_boiling_point(pressure),display)
    print(temperature,sap_boiling_point(pressure))
    time.sleep(1)
