# %% [markdown]
# PIL 和 OpenCV 是两种在 Python 中处理图像的方案。Opencv的性能优势非常明显。

# %%
import numpy as np
import cv2 as cv
import matplotlib as plt

# %%
img = cv.imread('images/ross.jpg', cv.IMREAD_GRAYSCALE)

# %% [markdown]
# 注意，cv库操作的就是numpy，而不是自定义的Image类。

# %%
type(img)

# %%
img_rgb = cv.cvtColor(img, cv.COLOR_BGR2RGB)

# %% [markdown]
# Jupyter 里最好不要 开窗口， 用 matplotlib 来显示兼容性最好。

# %%
cv.namedWindow("Image")
cv.imshow("Image", img_rgb)
cv.waitKey (0)
cv.destroyAllWindows()

# %%



