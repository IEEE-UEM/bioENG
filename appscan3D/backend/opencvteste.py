# Baixar o pip
# Baixar OpenCV

# O que é OpenCV e o que ele é capaz de fazer

# Demonstrar um código simples

# Importar biblioteca
import cv2

# Carregar a imagem em uma variável
img = cv2.imread('mao2.jpeg',1)
# 1 = Carrega a imagem com as cores padrões
# 0 = Carrega a imagem em escala de cinza*
# -1 = Alpha Channel = Mapa de transparência, relacionado a imagens vetorizadas (quadriculado no fundo)

print(img)
# Ṕrinta a matrizes com todos os pixels

'''link para ver a cor de cada pixel https://www.w3schools.com/colors/colors_rgb.asp '''
cv2.imshow('image', img)
#imshow('titulodaimagem',variavel)

cv2.waitKey(0) # = 0 imagem ficam congelada | > 0, tempo em ms para a imagem ficar aberta
cv2.destroyAllWindows() # fecha todas as janelas após o tempo determinado

cv2.imwrite('mao2p.png', img) #Faz uma cópia da variável img em .png

# Citar apostila que revisa os algoritmos anteriores que realizam a 
# conversão 2D --> 3D