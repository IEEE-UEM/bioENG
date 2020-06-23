# Baixar o pip
# Baixar OpenCV

# Demonstrar um codigo simples

# Importar biblioteca
import cv2

# Carregar a imagem em uma variavel
img = cv2.imread('mao2.jpeg',1)
# 1 = Carrega a imagem com as cores padroes
# 0 = Carrega a imagem em escala de cinza*
# -1 = Alpha Channel = Mapa de transparencia, relacionado a imagens vetorizadas (quadriculado no fundo)

print(img)
# printa matrizes com todos os pixels

'''link para ver a cor de cada pixel https://www.w3schools.com/colors/colors_rgb.asp '''
cv2.imshow('image', img)
#imshow('titulodaimagem',variavel)

cv2.waitKey(0) # = 0 imagem fica congelada, se >0 e o tempo em ms para a imagem ficar aberta
cv2.destroyAllWindows() # fecha todas as janelas apos o tempo determinado

cv2.imwrite('mao2p.png', img) #Faz uma copia da variavel img em .png

# Citar apostila que revisa os algoritmos anteriores que realizam a 
# conversao 2D --> 3D
