#ifndef STRUCTS_H
#define  STRUCTS_H

// Estrutura dos pixeis que serão usados, no processo de manipulação da imagem
typedef struct {
    unsigned char red, green, blue; 
} Pixel;

// Estrutura com variáveis relacionadas a imagem 
typedef struct {
    Pixel **pixel;
    char cod[3];
    int alt, larg, max;
} Imagem, *Ptr_imagem;

#endif