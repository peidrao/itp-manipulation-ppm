#ifndef STRUCTS_H
#define  STRUCTS_H

typedef enum {
  PAGINA_ESCOLHER_IMAGEM,
  PAGINA_ESCOLHER_EDICAO,
  PAGINA_CONCLUIDO
} Pagina;

// Estrutura dos pixeis que serão usados, no processo de manipulação da imagem
typedef struct {
    unsigned char vermelho, verde, azul; 
} Pixel;

// Estrutura com variáveis relacionadas a imagem 
typedef struct {
    Pixel **pixel;
    char cod[3];
    int alt, larg, max;
} Imagem, *Ptr_imagem;

typedef enum {
  ESC, // Escala de Cinza
  AMP, // Ampliação
  RED, // Redução
  ROT, // Rotação
  BLU, // Blurring
  SHA, // Sharpening
  DET, // Detecção de Bordas
  THR, // Binarização de Imagem
  NEG, // Negativo
  PIX, // Pixelização
  SOB, // Sobel
  GAU // Gaussiano
} Edicao;

#endif