import numpy as np
import cv2
from matplotlib import pyplot as plt

img1 = cv2.imread('0002_c3s1_000001_01.jpg',0)          # queryImage
img2 = cv2.imread('0002_c3s1_000076_01.jpg',0) # trainImage

orb = cv2.ORB_create()

# find the keypoints and descriptors with SIFT
kp1, des1 = orb.detectAndCompute(img1, None)
kp2, des2 = orb.detectAndCompute(img2, None)

bf = cv2.BFMatcher(cv2.NORM_HAMMING, crossCheck=True)

# Match descriptors.
matches = bf.match(des1, des2)

# Sort them in the order of their distance.
matches = sorted(matches, key=lambda x: x.distance)

img3 = cv2.drawMatches(img1, kp1, img2, kp2, matches[:10], outImg=2)

plt.imshow(img3), plt.show()



