#!/usr/bin/python

# RGBMatrix example w/Python Imaging Library - graphics prims & image loading

import Image
import ImageDraw
import time
from rgbmatrix import Adafruit_RGBmatrix

# Rows and chain length are both required parameters:
matrix = Adafruit_RGBmatrix(32, 1)

# Bitmap example w/graphics prims
image = Image.new("1", (32, 32)) # Can be larger than matrix if wanted!!
draw  = ImageDraw.Draw(image)    # Declare Draw instance before prims
# Draw some shapes into image...
draw.rectangle((0, 0, 31, 31), fill=0, outline=1)
draw.line((0, 0, 31, 31), fill=1)
draw.line((0, 31, 31, 0), fill=1)
# Then scroll image across screen...
for n in range(-32, 33): # Start off top-left, move off bottom-right
	matrix.Clear()
	# IMPORTANT: *MUST* pass image ID, *NOT* image object!
	matrix.SetImage(image.im.id, n, n)
	time.sleep(0.05)

# 8-bit paletted GIF scrolling example
image = Image.open("cloud.gif")
image.load()          # Must do this before SetImage() calls
matrix.Fill(0x6F85FF) # Fill screen to sky color
for n in range(32, -image.size[0], -1): # Scroll R to L
	matrix.SetImage(image.im.id, n, 0)
	time.sleep(0.025)

# 24-bit RGB scrolling example.
# The adafruit.png image has a couple columns of black pixels at
# the right edge, so erasing after the image isn't necessary.
matrix.Clear()
image = Image.open("adafruit.png")
image.load()
for n in range(32, -image.size[0], -1):
	matrix.SetImage(image.im.id, n, 1)
	time.sleep(0.025)

matrix.Clear()
