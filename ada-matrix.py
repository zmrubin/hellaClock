# DriverAdaMatrix provides a driver plugin for use with BiblioPixel: https://github.com/ManiacalLabs/BiblioPixel
# BiblioPixel is a write once, run on anything interface for LED animations on just about any hardware
# Install with "pip install bibliopixel" or download from GitHub
# Due to the Adafruit_RGBmatrix requirement, this code will only run on the Raspberry Pi

import time
from rgbmatrix import Adafruit_RGBmatrix

from bibliopixel.drivers.driver_base import *

class DriverAdaMatrix(DriverBase):
    """For Testing: Provides no ouput, just a valid interface"""
    
    # rows: height of the matrix, same as led-matrix example
    # chain: number of LEDMatrix panels, same as led-matrix example
    def __init__(self, rows = 32, chain = 1):
        """delay: time to wait in milliseconds to simulate actual hardware interface time"""
        super(DriverAdaMatrix, self).__init__(rows*32*chain)
        self._rows = rows
        self._chain = chain
        self._matrix = Adafruit_RGBmatrix(rows, chain)

    #Push new data to strand
    def update(self, data):
        self._matrix.SetBuffer(data)


# #Usage is as follows:
# #See the Wiki for more details: https://github.com/ManiacalLabs/BiblioPixel/wiki

# from bibliopixel import *
# import bibliopixel.colors as colors
# from ada-matrix import DriverAdaMatrix

# driver = DriverAdaMatrix(rows=32, chain=1)
# #MUST use serpentine=False because rgbmatrix handles the data that way
# led = LEDMatrix(driver, 32, 32, serpentine=False)

# #Must have code downloaded from GitHub for matrix_animations
# from matrix_animations import *
# import bibliopixel.log as log
# log.setLogLevel(log.DEBUG)


# try:
#     anim = ScrollText(led, "Hello World!", size=4)
#     anim.run()
# except KeyboardInterrupt:
#     led.all_off()
#     led.update()
