import time
from rgbmatrix import Adafruit_RGBmatrix

from bibliopixel.drivers.driver_base import *

class DriverAdaMatrix(DriverBase):
    """For Testing: Provides no ouput, just a valid interface"""
    
    def __init__(self, rows = 32, chain = 1):
        """delay: time to wait in milliseconds to simulate actual hardware interface time"""
        super(DriverAdaMatrix, self).__init__(rows*32*chain)
        self._rows = rows
        self._chain = chain
        self._matrix = Adafruit_RGBmatrix(rows, chain)

    #Push new data to strand
    def update(self, data):
        self._matrix.SetBuffer(data)
