import cv2
import numpy as np
from skimage import metrics
import pyautogui

f = open("../Texts/hero-model.txt", "w", encoding="utf-8")

# OW, OH = 5, 78
OW, OH = 0, 0

IMAGE_NUMBER = 33

def read_all_image():
	img_list = []
	for i in range(1, IMAGE_NUMBER + 1):
		img = cv2.imread("./Hero-Avatar/%d.bmp" % i)
		img = img[200:350,120:270,:3]
		img_list.append(img)
	return img_list

img_list = read_all_image()

def top_similarity(image, img_list):
	similarity_arr = []
	for i in range(1, IMAGE_NUMBER + 1):
		sim = metrics.structural_similarity(image, img_list[i-1], channel_axis=2)
		similarity_arr.append((i, sim))

	similarity_arr.sort(key = lambda x: -x[1])
	return similarity_arr[0][0]

def capture():
	s = pyautogui.screenshot()
	s_img = np.array(s)
	s_img = s_img[200+OH:350+OH,120+OW:270+OW,:3]
	index = top_similarity(s_img, img_list)
	# print(index)
	f.write(str(index) + "\n")

capture()