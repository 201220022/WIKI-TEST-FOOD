import time
import numpy as np
import cv2
import pytesseract
import pyautogui

pytesseract.pytesseract.tesseract_cmd = './Tesseract-OCR/tesseract.exe'

f = open("../Texts/attributes.txt", "a")

# OW, OH = 5, 78
OW, OH = 0, 0

attrs = ["strength", "magic", "skill", "speed", "blood", "armor", "resist"]

def resize(img, scale):
	dim = (img.shape[1] * scale, img.shape[0] * scale)
	img = cv2.resize(img, dim, interpolation = cv2.INTER_LINEAR)
	return img

def show_attributes(image):
	# adjust column based on input image
	left_column = image[473+OH:533+OH, 123+OW:163+OW, :3]
	# cv2.imshow("img", left_column)
	# cv2.waitKey(0)
	right_column = image[473+OH:518+OH, 227+OW:267+OW, :3]
	# cv2.imshow("img", right_column)
	# cv2.waitKey(0)

	img = cv2.vconcat([left_column, right_column])
	img = resize(img, 4)
	# cv2.imshow("img", img)
	# cv2.waitKey(0)

	text = pytesseract.image_to_string(img, config='--psm 6 outputbase digits')
	# print(text)
	values = text.strip().split()

	# print out attributes
	if len(attrs) != len(values):
		print("Error extracting attributes, ocr text: %s" % text)
		return
	for attr, value in zip(attrs, values):
		# print(attr + ": " + value)
		f.write(value + "\n")

def capture():
	s = pyautogui.screenshot()
	s_img = np.array(s)
	show_attributes(s_img)

# start = time.time()
# for i in range(20):
# 	capture()
# end = time.time()
# rt = end - start
# print('runtime for 20 capture: %.3f, per capture: %.3f' % (rt, rt/20))

capture()