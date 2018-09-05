import numpy as np
import cv2

# 빨간선 검출 코드

img = cv2.imread('./red_line.PNG')
imhsv = cv2.cvtColor(img, cv2.COLOR_BGR2HSV)

lower = np.array([0, 50, 50])
upper = np.array([20, 255, 255])
mask = cv2.inRange(imhsv, lower, upper)
res = cv2.bitwise_not(img, img, mask=mask)

cv2.imshow('res', res)
cv2.waitKey(0)
cv2.destroyAllWindows()
