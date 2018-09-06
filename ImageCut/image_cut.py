import numpy as np
import cv2
from PIL import Image


def hough(thr):
    img = cv2.imread('./image.jpg')
    imgray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)

    # Canny의 두번째, 세번째 인자값도 조절하면 정확도 달라짐
    edges = cv2.Canny(imgray, 100, 150, apertureSize=3)

    lines = cv2.HoughLines(edges, 1, np.pi/180, thr)

    for line in lines:
        r, theta = line[0]
        a = np.cos(theta)
        b = np.sin(theta)
        x0 = a*r
        y0 = b*r
        x1 = int(x0 + 1000*(-b))
        y1 = int(y0 + 1000*a)
        x2 = int(x0 - 1000*(-b))
        y2 = int(y0 - 1000*a)

        height = img.shape[0]
        width = img.shape[1]

        img_left = img[0:height, 0:x1]
        cv2.imwrite('image_1.jpg', img_left)

        img_right = img[0:height, x1:width]
        cv2.imwrite('image_2.jpg', img_right)

        cv2.line(img, (x1, y1), (x2, y2), (0, 255, 0), 2)

    cv2.imshow('res', img)
    cv2.waitKey(0)
    cv2.destroyAllWindows()


# 인자 값 바꾸면 정확도가 달라짐
hough(190)