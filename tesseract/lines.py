#!/usr/bin/env python
#coding=utf-8
from PIL import Image
import pytesseract
import numpy as np
import otsu as ot

def lines(im_text):
    im_text=clip(im_text)
    width,height=im_text.size
    pix=im_text.load()
    data = np.asarray(im_text)
    fl=[]
    remain=[]
    for s in range(height):
        if np.sum(data[s])==width*255:
            region=(0,0,width,s)
            fl=im_text.crop(region)
            region2=(0,s,width,height)
            remain=im_text.crop(region2)
            remain=clip(remain)
            break
        else:
            fl=im_text
            remain=[]
    return fl,remain

def clip(im_bin):
    line=0
    pix=im_bin.load()
    width,height=im_bin.size
    for x in range(height):
        for y in range(width):
            if pix[y,x]==0:
                region=(0,line,width,height)
                return im_bin.crop(region)
            if y==width-1:
                line+=1
    region=(0,line,width,height)
    return im_bin.crop(region)

im=Image.open('10.JPG').convert('L')

th=ot.otsu_thrd(im)
im_out=ot.segment(im,th)
out=clip(im_out)
new,re=lines(out)


str=pytesseract.image_to_string(new, lang='fra')

while (re!=[]):
    new,re=lines(re)
    if new!=[]:
        str+='\n'+pytesseract.image_to_string(new, lang='fra')
print(str)