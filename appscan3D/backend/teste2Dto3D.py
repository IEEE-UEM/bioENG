# Demonstar Codigo teste com uma solução simples de
# demonstrar a profundidade da imagem a partir dos valores de cada pixel
# eixo x = 0 a max. RGB (255) se > 255 -> = 255
# eixo y = 0 a max. RGB (255) se > 255 -> = 255
# eixo z = 0 a max. RGB (255) se > 255 -> = 255

import cv2
import numpy as np
import matplotlib
import matplotlib.pyplot as plt
from matplotlib.pyplot import imread
from mpl_toolkits.mplot3d import Axes3D
import scipy.ndimage as ndimage
from matplotlib import cm
import stl
from stl import mesh
import matplotlib.tri as mtri

mat = cv2.imread('mao2p.png',0) # Carrega a imagem em escala de cinza
print(mat)
rows, cols = mat.shape # Colhe as informações de linhas/ colunas
xv, yv = np.meshgrid(range(cols), range(rows)[::-1]) # Cria a matriz dos pixels
blurred = ndimage.gaussian_filter(mat, sigma=(5, 5), order=0) # Aplica o filtro para suavizar contrastes (Deixa a imagem embaçada)
fig = plt.figure(figsize=(6,6))
ax = fig.add_subplot(221)
ax.imshow(mat, cmap='gray')
ax = fig.add_subplot(222, projection='3d')
ax.elev= 75
ax.plot_surface(xv, yv, mat, cmap=cm.inferno,linewidth=0, antialiased=False)
ax = fig.add_subplot(223)
ax.imshow(blurred, cmap='gray')
ax = fig.add_subplot(224, projection='3d')
ax.elev= 75
ax.plot_surface(xv, yv, blurred, cmap=cm.gray,linewidth=0, antialiased=False)
plt.show()


# Defeitos desse algoritmo

# - Distorcao da imagem 3D pois o grafico somente plota em eixos axias de 
#   mesma amplitude e minha imagem eh retangular -> Realizar corte l x l na imagem a ser computada
# - Pouca nocaoo de profundidade
# - Muito ruido, distorce o fundo --> O certo seria retirar o fundo da imagem
# - Erro de dimensão ao criar arquivo .stl xv e yv > 1D