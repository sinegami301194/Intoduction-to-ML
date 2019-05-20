# Open image
import cv2 # Import library

def viewImage(image, name_of_window):
    cv2.namedWindow(name_of_window, cv2.WINDOW_NORMAL)
    cv2.imshow(name_of_window, image)
    cv2.waitKey(0)
    cv2.destroyAllWindows()

image = cv2.imread('unnamed.jpg')
output = image.copy()
cv2.rectangle(output, (250, 100), (650, 600), (0, 255, 255), 10)
cv2.line(output, (450, 100), (450, 600), (0, 0, 255), 5)
viewImage(output, "Draw the rectangle")


