import numpy as np
import cv2
from matplotlib import pyplot as plt

img = cv2.imread('./images/ross.jpg')

cv2.imshow( 'image' , img)
cv2.waitKey(2000)
cv2.destroyAllWindows()

# 该函数有两个返回值，第一个retVal（得到的阈值值（在后面一个方法中会用到）），第二个就是阈值化后的图像
_, thresh = cv2.threshold(img, 150, 255, cv2.THRESH_BINARY)
cv2.imshow( 'image' , thresh)
cv2.waitKey(0)
cv2.destroyAllWindows()