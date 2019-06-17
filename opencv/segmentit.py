import cv2
import numpy as np

img = cv2.imread('out1.png')
cv2.imshow('img', 64 * img) 
cv2.waitKey(0)
cv2.destroyAllWindows()

np.unique(img.flatten())