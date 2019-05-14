import cv2

#%%
def viewImage(image, name_of_window):
    cv2.namedWindow(name_of_window, cv2.WINDOW_NORMAL)
    cv2.imshow(name_of_window, image)
    cv2.waitKey(0)
    cv2.destroyAllWindows()

#%%

image = cv2.imread("20180404_172055.jpg",0)
cv2.imshow("Image", image)
cv2.waitKey(0)
cv2.destroyAllWindows()

cropped = image[10:500, 2000:500]
#viewImage(cropped, "Пёсик после кадрирования")

#%%
#scale_percent = 20 # Процент от изначального размера
#width = int(image.shape[1] * scale_percent / 100)
#height = int(image.shape[0] * scale_percent / 100)
#dim = (width, height)
#resized = cv2.resize(image, dim, interpolation = cv2.INTER_AREA)
#viewImage(resized, "После изменения размера на 20 %")

#%%
(h, w, d) = image.shape
center = (w // 2, h // 2)
M = cv2.getRotationMatrix2D(center, 180, 1.0)
rotated = cv2.warpAffine(image, M, (w, h))
viewImage(rotated, "Пёсик после поворота на 180 градусов")
#%%
