from PID import PID
import time
import board
import analogio
import pwmio

import board
from adafruit_onewire.bus import OneWireBus
from adafruit_ds18x20 import DS18X20
ow_bus = OneWireBus(board.GP3)
ds18 = DS18X20(ow_bus, ow_bus.scan()[0])

pid = PID(10, 0.5, 0.05, setpoint=1)
pid.setpoint = 30
pid.output_limits = (0, 100)    # Output value will be between 0 and 10


    
pid.sample_time = 10  # Update every 10 milliseconds when set to the millisecond ('ms') scale
current_value = 20

heater = pwmio.PWMOut(board.GP0, frequency=500)

fan = pwmio.PWMOut(board.GP4, frequency=500)
fan_percentage = 50

fan.duty_cycle = int((2**16-1)*fan_percentage/100)

while True:
    temperature_value = ds18.temperature
    output = pid(temperature_value)
    
    heater.duty_cycle = int((2**16-1)*output/100)
    
    print("Temperature: " + str(temperature_value))
    print("PID Response: " + str(output/100))
    print("")
    time.sleep(1)

