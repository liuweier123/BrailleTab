#!/usr/bin/env python
#coding=utf-8
import numpy as np
import enlarge as el
from PIL import Image
import pytesseract
import matplotlib.pyplot as plt
im=Image.open('10.jpg')

out=el.enlarge(im)
plt.imshow(out)                   #draw the image
plt.show()                        # show the image



