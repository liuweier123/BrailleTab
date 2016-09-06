import matplotlib.pyplot as plt
import matplotlib.cm as cm


plt.imshow(image_gray, cmap=cm.gray) # 指明 cmap=cm.gray
plt.axis("off") # 去掉坐标轴

plt.show() # 显示图像