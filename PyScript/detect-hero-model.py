import cv2
import numpy as np
from skimage import metrics
import pyautogui

RESOURCE_PATH = "./Hero-Avatar/"

f = open("../Texts/hero-model.txt", "w", encoding="utf-8")

# OW, OH = 5, 78
OW, OH = 0, 0

def read_all_image():
	img_list = []
	for i in range(1, 28):
		img_path = RESOURCE_PATH + str(i) + ".bmp"
		img = cv2.imread(img_path)
		img = img[200:350,120:270,:3]
		img_list.append(img)
	return img_list

img_list = read_all_image()

def top_similarity(image, img_list):
	similarity_arr = []
	for i in range(1, 28):
		img = img_list[i-1]
		sim = metrics.structural_similarity(image, img, channel_axis=2)
		similarity_arr.append((sim, img, i))

	similarity_arr.sort(key = lambda x: -x[0])
	return similarity_arr[0][2]

def capture():
	s = pyautogui.screenshot()
	s_img = np.array(s)
	s_img = s_img[200+OH:350+OH,120+OW:270+OW,:3]
	index = top_similarity(s_img, img_list)
	# print(index)
	f.write(str(index) + "\n")

capture()