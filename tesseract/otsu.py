from PIL import Image
def histogram(im):
    pixel =im.load()
    width, height = im.size
    hist = [0]*256
    for y in range(height):
        for x in range(width):
            gray_level= pixel[x, y]
            hist[gray_level] = hist[gray_level]+1
    return hist

def otsu_thrd(im):
    hist = histogram(im)
    sum_all = 0
    for t in range(256):
        sum_all += t * hist[t]
    sum_back, w_back, w_for, var_max, thd = 0, 0, 0, 0, 0
    width, height = im.size
    total = height*width

    for t in range(256):
        # update weights
        w_back += hist[t]
        if (w_back == 0): continue
        w_fore = total - w_back
        if (w_fore == 0) : break
        # calculate classes means
        sum_back += t * hist[t]
        mean_back = sum_back / w_back
        mean_fore = (sum_all - sum_back) / w_fore
        # Calculate Between Class Variance
        var_between = w_back * w_fore * (mean_back - mean_fore)**2
        if (var_between > var_max):
            var_max = var_between
            thd = t
    return thd

def segment(im, thrd = 128):
    width, height = im.size
    mat = im.load()
    out = Image.new('L',(width, height))
    out_pix = out.load()
    for x in range(width): # go over the image columns
        for y in range(height): # go over the image rows
            if mat[x, y] >= thrd: # compare to threshold
                out_pix[x, y] = 255
            else:
                out_pix[x, y] = 0
    return out

def binary(im):
    th=otsu_thrd(im)
    return segment(im,th)

