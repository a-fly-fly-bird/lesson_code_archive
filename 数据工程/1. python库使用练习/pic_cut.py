import numpy as np
import cv2
from matplotlib import pyplot as plt

# Image operation using thresholding
img = cv2.imread('./images/7.jpg')

gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)

# src：源图像，可以为8位的灰度图，也可以为32位的彩色图像。（两者由区别）
# dst：输出图像
# thresh：阈值
# maxval：dst图像中最大值
# type：阈值类型

# 该函数有两个返回值，第一个retVal（得到的阈值值（在后面一个方法中会用到）），第二个就是阈值化后的图像
ret, thresh = cv2.threshold(gray, 0, 255, cv2.THRESH_BINARY_INV +
                            cv2.THRESH_OTSU)
cv2.imshow( 'image' , thresh)
cv2.waitKey(0)
cv2.destroyAllWindows()

# Noise removal using Morphological
# closing operation
kernel = np.ones((3, 3), np.uint8)
closing = cv2.morphologyEx(thresh, cv2.MORPH_CLOSE, kernel, iterations=2)

# Background area using Dialation
bg = cv2.dilate(closing, kernel, iterations=1)

# Finding foreground area
# 当图像内的各个子图没有连接时，可以直接使用形态学的腐蚀操作确定前景对象，但是如果图像内的子图连接在一起时，就很难确定前景对象了。此时，借助于距离变换函数 cv2.distanceTransform（）可以方便地将前景对象提取出来。
# 距离变换函数 cv2.distanceTransform（）计算二值图像内任意点到最近背景点的距离。一般情况下，该函数计算的是图像内非零值像素点到最近的零值像素点的距离，即计算二值图像中所有像素点距离其最近的值为 0 的像素点的距离。当然，如果像素点本身的值为 0，则这个距离也为 0。
# 距离变换函数 cv2.distanceTransform（）的计算结果反映了各个像素与背景（值为 0 的像素点）的距离关系。通常情况下：
# 如果前景对象的中心（质心）距离值为 0 的像素点距离较远，会得到一个较大的值。
# 如果前景对象的边缘距离值为 0 的像素点较近，会得到一个较小的值。
# 如果对上述计算结果进行阈值化，就可以得到图像内子图的中心、骨架等信息。距离变换函数 cv2.distanceTransform（）可以用于计算对象的中心，还能细化轮廓、获取图像前景等，有多种功能。
# https://blog.csdn.net/ftimes/article/details/106836803
dist_transform = cv2.distanceTransform(closing, cv2.DIST_L2, 0)
ret, fg = cv2.threshold(dist_transform, 0.02
                        * dist_transform.max(), 255, 0)

cv2.imshow('image', fg)
cv2.waitKey(0)
cv2.destroyAllWindows()
