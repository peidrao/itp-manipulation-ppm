As funções implementadas foram as de ler e salvar a imagem, espelhamento horizontal e vertical da mesma, rotação em 90° em sentido horário e anti horário,
binarização da imagem, efeito negativo, apliar e reduzir, pixelizar a imagem em 4 a 4 pixeis, escala de cinza, além dos efeitos blurring, sharpening e detector de bordas.

Todas as funções foram feitas, porém não foi possível documentar devidamente o código.

Os efeitos para rotacionar, reduzir e pixelizar a imagem poderiam ser feitos diferente, uma vez que estes poderiam rotacionar para qualquer ângulo, reduzir a imagem em n vezes e pixeliza-la em nxn pixeis, aumentando ou diminuindo o grau dos quadros dentro da imagem.

Para compilar o projeto, é necessário somente iserir o comando 'make' enquanto estiver no diretório do projeto, ou inserir os seguintes comandos:
'gcc main.c funcoes.c -o Imageeditor'
Caso já exista um arquivo Imageeditor, o comando 'make clean' poderá ser executado, para que os arquivos já existentes sejam apagados.