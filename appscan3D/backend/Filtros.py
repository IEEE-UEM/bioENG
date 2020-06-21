import os
import cv2
import subprocess
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.image as mpimg

def Plote(img):

	plt.axis('off')
	plt.imshow(cv2.cvtColor(img, cv2.COLOR_BGR2RGB))
	#plt.savefig("test.png", bbox_inches='tight')
	plt.show()

def FiltroCinza(img):

	imagem = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)

	return imagem

def FiltroBinario(img, nivel):         #retorna a imagem binarizada

	retval, threshold = cv2.threshold(img, nivel, 255, cv2.THRESH_BINARY)
	imagem = cv2.cvtColor(threshold ,cv2.COLOR_BGR2RGB)

	return imagem

def Equalizar(img):         #retorna a imagem binarizada

	#img = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
	img = FiltroCinza(img)
	imagem = cv2.equalizeHist(img)

	return imagem
 
def AjusteGama(img, gamma=2.5):

	invGamma = 1.0 / gamma
	table = np.array([((i / 255.0) ** invGamma) * 255
		for i in np.arange(0, 256)]).astype("uint8")

	return cv2.LUT(img, table)

def FiltroGauss(img):

	imagem = cv2.GaussianBlur(img,(5,5), 0)

	return imagem

def FiltroBilateral(img):

	imagem = cv2.bilateralFilter(img ,9,75,75)

	return imagem

def FiltroMedio(img):

	imagem = cv2.medianBlur(img, 5)

	return imagem

def EscreverContornos(img): 

	imgray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
	canny = cv2.Canny(imgray,100,200)

	(contornos,_) = cv2.findContours(canny.copy(), cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
	print(" Encontrado: {} objetos".format(len(contornos)))

	for i in contornos:

		area = cv2.contourArea(i)

		if (area > 1220):

			cv2.drawContours(imagem,[i],-1,(0,0,255), 2)

	return imagem

def EscreverBordas(img):

	imagem = cv2.Canny(img,100,200)

	return imagem

def AreaPerimetro(img):

	gris = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
	gauss = cv2.GaussianBlur(gris, (5,5), 0)
	canny = cv2.Canny(gauss, 50, 150)
	(contornos,_) = cv2.findContours(canny.copy(), cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
	print(" Encontrado: {} objetos".format(len(contornos)))
	cv2.drawContours(img,contornos,-1,(0,0,255), 2)

	for i in contornos:

		perimeter = cv2.arcLength(i,True)
		area = cv2.contourArea(i)

		print('A: ',area,'P: ', perimeter)
		print('R: ', (area/perimeter)*2)

	return img

def Circulo(img):

	canny = cv2.Canny(img, 50, 150)
	(contornos,_) = cv2.findContours(canny.copy(), cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
	print(" Encontrado: {} objetos".format(len(contornos)))

	circles = cv2.HoughCircles(canny, cv2.HOUGH_GRADIENT, 1.2, 100)
	
	if circles is not None:

		circles = np.round(circles[0, :]).astype("int")
	 

		for (x, y, r) in circles:

			#cv2.circle(img, (x, y), r, (0, 255, 0), 4)
			#cv2.rectangle(img, (x - 10, y - 10), (x + 5, y + 5), (0, 128, 255), -1)
			cv2.rectangle(img, (x-r-15 , y-r-15), (x+r+15, y+r+15), (0, 128, 255), thickness=3)
			imagem = img[y-r-15:y+r+15, x-r-15:x+r+15]

	return imagem

def Convexo(img):

	ret, threshed_img = cv2.threshold(cv2.cvtColor(img, cv2.COLOR_BGR2GRAY),100, 255, cv2.THRESH_BINARY)
	(contours,_) = cv2.findContours(threshed_img, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
	 
	for cnt in contours:

		area = cv2.contourArea(cnt)

		if (10000 < area < 100000):

			hull = cv2.convexHull(cnt)

			cv2.drawContours(img, [hull], -1, (0, 0, 255), 3)
		
	return img

def Triangulos(img):

	gris = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
	gauss = cv2.GaussianBlur(gris, (5,5), 0)
	canny = cv2.Canny(gauss, 50, 150)
	(contours,_) = cv2.findContours(canny.copy(), cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
	print(" Encontrado: {} objetos".format(len(contours)))
	areas = [cv2.contourArea(c) for c in contours]

	i = 0
	for extension in areas:
		if extension > 600:
			actual = contours[i]
			approx = cv2.approxPolyDP(actual,0.05*cv2.arcLength(actual,True),True)
			if len(approx) == 3:
				cv2.drawContours(img,[actual],0,(0,0,255),2)
				[x,y,w,h] = cv2.boundingRect(actual)

				if h>250 and w>250:
					continue
			 
				if h<40 or w<40:
					continue
			 
				cv2.rectangle(img,(x,y),(x+w,y+h),(255,0,255),2)

			i = i+1

	return img

# Exemplo de uso:
#imagem = cv2.imread("semaforo.jpg")
#imagem = FiltroCinza(imagem)
#imagem = AjusteGama(imagem)
#imagem = FiltroBinario(imagem)
#imagem = Suavizar(imagem)
#imagem = EscreverContornos(imagem)
#AjustadorGama(1,460)
#Removedor(1,460)
#Plote(imagem)
