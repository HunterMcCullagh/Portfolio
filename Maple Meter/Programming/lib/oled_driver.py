import board
import busio
import time
import struct
import digitalio
import microcontroller
import displayio
import adafruit_displayio_ssd1306
import terminalio
from adafruit_display_text import label

class OLED:
    def initialize_oled():
        WIDTH = 128
        HEIGHT = 64
        displayio.release_displays()

        #create i2c bus for oled
        sda_oled = board.GP2
        scl_oled = board.GP3
        i2c = busio.I2C(scl_oled,sda_oled)
        address = 61 #might have to change this to 61

        if(i2c.try_lock()):
            i2c.unlock()

        display_bus = displayio.I2CDisplay(i2c, device_address=address)
        display = adafruit_displayio_ssd1306.SSD1306(display_bus, width=WIDTH, height=HEIGHT)

        #Make the display context
        group = displayio.Group(max_size=10)
        NUM_OF_COLOR = 2
        bitmap = displayio.Bitmap(WIDTH, HEIGHT, NUM_OF_COLOR)
        bitmap_palette = displayio.Palette(NUM_OF_COLOR)
        bitmap_palette[0] = 0x000000
        bitmap_palette[1] = 0xFFFFFF

        tileGrid = displayio.TileGrid(bitmap,pixel_shader=bitmap_palette,x=0, y=0)
        group.append(tileGrid)
        display.show(group)
        bitmap.fill(0)
        return display

    def display_data(temperature,pressure,display):

        text_group = displayio.Group(max_size=10)
        y_displacement = 5
        x_displacement = 64
        y_interval = 10
        font_size = 10
        font_scale = 1

        formatString = "{:0.3f}"

        text = "River's Edge Acres"
        text_area = label.Label(terminalio.FONT, text=text, color=0xFFFFFF,x=0,y=y_displacement)
        text_group.append(text_area)

        text = "Current Temperature"+str(formatString.format(temperature)))
        text_area = label.Label(terminalio.FONT, text=text, color=0xFFFFFF,x=0,y=y_interval+y_displacement)
        text_group.append(text_area)

        text = "Ideal Temperature"+str(formatString.format(pressure)))
        text_area = label.Label(terminalio.FONT, text=text, color=0xFFFFFF,x=0,y=y_interval+y_displacement)
        text_group.append(text_area)

        display.show(text_group)

    def test(display):

        text_group = displayio.Group(max_size=10)
        y_displacement = 5
        x_displacement = 64
        y_interval = 10
        font_size = 10
        font_scale = 1

        text = "River's Edge Acres"
        text_area = label.Label(terminalio.FONT, text=text, color=0xFFFFFF,x=0,y=y_displacement)
        text_group.append(text_area)

        display.show(text_group)
