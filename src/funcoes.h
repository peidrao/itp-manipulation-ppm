#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structs.h"

#ifndef FUNCOES_H
#define  FUNCOES_H

    int alocarMemoria(Ptr_imagem ptr_imagem);

    // Função responsável pela leitura da imagem 
    void lerImagem(Ptr_imagem imagem);

    // Função que salva a imagem 
    void gravarImagem(Ptr_imagem imagem);

    // Filtro para transformar a imagem em cinza
    void filtroEscalaCinza(Ptr_imagem imagem);
    
    /* Aumentar a resolução da imagem
     * A variável tipo int é a responsável por calcular a quantidade de ampliação que a imagem tera
     * Se a imagem tem uma resolução de 400x400, e o usuário coloca uma ampliação de 10, teremos
     * 10*400 - > Altura e 10*400 - > Largura. Dessa forma o tamanho final da imagem será de 4000x4000
     */
    int ampliar(Ptr_imagem ptr_imagem, int amp);

    // Diminuir a resolução da imagem
    void reduzir(Ptr_imagem ptr_imagem, int red);

    //Rotaciona a imagem no sentido horário
    void rotacao(Ptr_imagem ptr_imagem, int rot);
    
    //Rotaciona a imagem no sentido anti-horário
    void rotacaoAntiHorario(Ptr_imagem ptr_imagem);

    // Aplica o efeito de inversão de cores na imagem
    void filtronNegativo(Ptr_imagem ptr_imagem);

    void filtroBinarizar(Ptr_imagem ptr_imagem,  int binarizar);


    void menu();

#endif