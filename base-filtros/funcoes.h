#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structs.h"

//Função responsável por realizar o alocamento dînâmico dos pixeis, uma vez passado o endereço de memória da imagem
void criarMatrizPixeis(pont_imagem Imagem);

//Função responsável por ler a imagem a partir do arquivo e armazenar suas imformações dentro da variável Imagem
void lerImagem(pont_imagem Imagem);

//Função responsável por salvar os dados da imagem em um arquivo
void salvarImagem(pont_imagem Imagem);

//Função que realiza o espelhamento horizonatal da imagem
void espelharHorizontal(pont_imagem Imagem);

//Função que realiza o espalmento vertial de uma imagem
void espelharVertical(pont_imagem Imagem);

//Função responsável por rotacionar a imagem no sentido anti horário
void girarAntiHorario(pont_imagem Imagem);

//Função responsável por rotacionar a imagem no sentido horário
void girarHorario(pont_imagem Imagem);

//Função responsável pela binarização da imagem, uma vez passado um limite para o truncamento
void threshold(pont_imagem Imagem, int limite);

//Função responsável por deixar a imagem em negativo, calculando o complemento das cores dos pixeis
void negativo(pont_imagem Imagem);

//Função responsável por ampliar a imagem em x vezes, uma vez que seja passado a quantidade de vezes
void ampliar(pont_imagem Imagem, int zoom);

//Função que reduz a imagem pela metade
void reduzir(pont_imagem Imagem);

//Função para pixelizar uma imagem, por meio do cálculo da média entre 4 pixeis
void pixelizar(pont_imagem Imagem);

//Função responsável por deixar a imagem em escala de cinza, que é feito por meio da média dos valores do r, g e b dos píxeis
void escalaCinza(pont_imagem Imagem);

//Função responsável por aplicar os filtros blurring, sharpening e detector de bordas na imagem
void aplicarEfeito(pont_imagem Imagem, int efeito[3][3], int divisor);

//Menu responsável por mostrar as opções ao usuário e chamar as demais funções do sistema
void menu();