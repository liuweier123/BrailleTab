#!/usr/bin/env python
#coding=utf-8
import numpy as np
from PIL import Image
import matplotlib.pyplot as plt
def enlarge(im,n=2):
    return im.resize(n* np.array(im.size))     # resize the matrix



