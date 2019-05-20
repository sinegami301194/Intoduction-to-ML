# Open image
import cv2 # Import library
image = cv2.imread('unnamed.jpg')
cv2.imshow("Image", image)
cv2.waitKey(0)
cv2.destroyAllWindows()
