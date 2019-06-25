#include "structs.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <string.h>
#include <math.h>

#ifndef FUNCOES_H
#define  FUNCOES_H

    // Função responsável pela leitura da imagem e retorna eventuais erros
    char *lerImagem(Ptr_imagem imagem, char *caminhoImagem);

    // Função que salva a imagem 
    void gravarImagem(Ptr_imagem imagem, char *caminhoImagem);

    // Filtro para transformar a imagem em cinza
    void filtroEscalaCinza(Ptr_imagem imagem);
    
    /* Aumenta a resolução da imagem
     * A variável tipo int é a responsável por calcular a quantidade de ampliação que a imagem tera.
     * Se a imagem tem uma resolução de 400x400, e o usuário coloca uma ampliação de 10, teremos
     * 10*400 - > Altura e 10*400 - > Largura. Dessa forma o tamanho final da imagem será de 4000x4000
     */
    void ampliar(Ptr_imagem ptr_imagem, int amp);

    /* Diminui a resolução da imagem
     * Analogo ao filtro de ampliar que multiplica a largura pelo número que o usuário colocou para reduzir.
     * Se o usuário estiver usando uma imagem com resolução de 1920x1080 e na variável red (que irá receber o tamanho que o usuário quer diminuir),
     * então a imagem sofrerá uma redução que resulta da divisão da largura por red e altura por red.
     * Usando a imagem com resolução anterior e um red de 5 a imagem ficará com resolução de 384x216 (1920/5 x 1080/5).
    */
    void reduzir(Ptr_imagem ptr_imagem, int red);

    /* Rotação da imagem 
     * Dado um ângulo de 90°, 180° ou 270° a imagem irá fazer a rotação.
    */
    void rotacionar(Ptr_imagem ptr_imagem, int rot);
    
    void filtroMascara(Ptr_imagem ptr_imagem, float mascara[3][3]);

    // Binariza a imagem usando thresholding 
    void filtroBinarizar(Ptr_imagem ptr_imagem, int binarizar);

    // Aplica o efeito de inversão de cores na imagem
    void filtroNegativo(Ptr_imagem ptr_imagem);

    // São criados blocos de cor dos três pixeis (vermelho, verde e azul), na qual é feito a média dos mesmos e o valor da média de cada pixel é aplicado ao percuso de cada repitição.  
    void filtroPixelizar(Ptr_imagem ptr_imagem);

    //Detecta as bordas horizontais e verticais da imagem em escala de cinza, e assim a imagem é transformada de RGB para a escala de cinza e o resultado é uma imagem com contornos brancos.    
    void filtroSobel(Ptr_imagem ptr_imagem);
    
    // Realiza o desfoque da imagem. Pixeis que são similares são desfocados entre si
    void filtroGaussiano(Ptr_imagem ptr_imagem);

#endif