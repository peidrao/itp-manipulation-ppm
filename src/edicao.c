#include "edicao.h"

void alocarMemoria(Ptr_imagem ptr_imagem) {
    ptr_imagem->pixel = (Pixel **) malloc(ptr_imagem->alt * sizeof(Pixel *));
    for (int i = 0; i < ptr_imagem->alt; i++) {
        ptr_imagem->pixel[i] = (Pixel *) malloc(ptr_imagem->larg * sizeof(Pixel));
    }
}

bool isppm(char *caminhoImagem) {
    int nomeTam = strlen(caminhoImagem);
    bool achou = false;
    if (nomeTam > 4) {
        achou = true;
        int startIndex = nomeTam - 1;
        for (int i = startIndex; i >= 0; i--) {
            if (i == startIndex && caminhoImagem[i] != 'm') {
                achou = false;
                break;
            } else if (i == startIndex - 1 && caminhoImagem[i] != 'p') {
                achou = false;
                break;
            } else if (i == startIndex - 2 && caminhoImagem[i] != 'p') {
                achou = false;
                break;
            } else if (i == startIndex - 3 && caminhoImagem[i] != '.') {
                achou = false;
                break;
            }
        }
    }
    if (!achou) {
        return false;
    }
    return true;
}

char *lerImagem(Ptr_imagem ptr_imagem, char *caminhoImagem) {
    if (!isppm(caminhoImagem)) {
        return "Por favor, escolha uma imagem do tipo .ppm";
    }

    FILE *imagem;
    imagem = fopen(caminhoImagem, "r");

    if (imagem == NULL) {
        return "Ocorreu um erro ao abrir a imagem";
    }

    // Leitura do código da imagem. Para confirmar que realmente haverá a manipulação de um arquivo P3
    fscanf(imagem, "%s", ptr_imagem->cod);

    if (strcmp(ptr_imagem->cod, "P3") != 0) {
        fclose(imagem);
        return "Apenas o código P3 é suportado";
    }

    fscanf(imagem, "%i", &ptr_imagem->larg);
    fscanf(imagem, "%i", &ptr_imagem->alt);

    alocarMemoria(ptr_imagem);

    fscanf(imagem, "%i", &ptr_imagem->max);

    for (int i = 0; i < ptr_imagem->alt; i++) {
        for (int j = 0; j < ptr_imagem->larg; j++) {
            fscanf(imagem, "%hhu", &ptr_imagem->pixel[i][j].vermelho);
            fscanf(imagem, "%hhu", &ptr_imagem->pixel[i][j].verde);
            fscanf(imagem, "%hhu", &ptr_imagem->pixel[i][j].azul);
        }
    }
    fclose(imagem);

    return NULL;
}


void gravarImagem(Ptr_imagem ptr_imagem, char *caminhoImagem) {
    FILE *imagem;

    if (!isppm(caminhoImagem)) {
        strcat(caminhoImagem, ".ppm");
    }
    imagem = fopen(caminhoImagem, "w");

    fprintf(imagem, "%s\n", ptr_imagem->cod);
    fprintf(imagem, "%i ", ptr_imagem->larg);
    fprintf(imagem, "%i\n", ptr_imagem->alt);
    fprintf(imagem, "%i\n", ptr_imagem->max);

    for (int i = 0; i < ptr_imagem->alt; i++) {
        for (int j = 0; j < ptr_imagem->larg; j++) {
            fprintf(imagem, "%hhu ", ptr_imagem->pixel[i][j].vermelho);
            fprintf(imagem, "%hhu ", ptr_imagem->pixel[i][j].verde);
            fprintf(imagem, "%hhu\n", ptr_imagem->pixel[i][j].azul);
        }
    }
    fclose(imagem);
    free(ptr_imagem->pixel);
}

void filtroEscalaCinza(Ptr_imagem ptr_imagem) {
    for (int i = 0; i < ptr_imagem->alt; i++) {
        for (int j = 0; j < ptr_imagem->larg; j++) {
            Pixel pixel = ptr_imagem->pixel[i][j];
            int mediaCores = (ptr_imagem->pixel[i][j].vermelho + ptr_imagem->pixel[i][j].verde + ptr_imagem->pixel[i][j].azul) / 3;
            ptr_imagem->pixel[i][j].vermelho = mediaCores;
            ptr_imagem->pixel[i][j].verde = mediaCores;
            ptr_imagem->pixel[i][j].azul = mediaCores;
        }
    }
}

void ampliar(Ptr_imagem ptr_imagem, int amp) {
    // A variável ampliar será responsável por receber a apliação que o usuário deseja usar
    Imagem imagemTemp;
    imagemTemp.larg = ptr_imagem->larg * amp;
    imagemTemp.alt = ptr_imagem->alt * amp;

    alocarMemoria(&imagemTemp);

    for (int i = 0, k = 0; i < ptr_imagem->alt && k < imagemTemp.alt; k++) {
        if (k % amp == 0 && k != 0) {
            i++;
        }
        for (int j = 0, l = 0; j < ptr_imagem->larg && l < imagemTemp.larg; l++) {
            if (l % amp == 0 && l != 0) {
                j++;
            }
            imagemTemp.pixel[k][l] = ptr_imagem->pixel[i][j]; 
        }
    }

    free(ptr_imagem->pixel);
    ptr_imagem->larg = imagemTemp.larg;
    ptr_imagem->alt = imagemTemp.alt;
    ptr_imagem->pixel = imagemTemp.pixel;
}

void reduzir(Ptr_imagem ptr_imagem, int red) {
	Imagem imagemTemp;
	imagemTemp.larg = ptr_imagem->larg / red;
	imagemTemp.alt = ptr_imagem->alt / red;
	alocarMemoria(&imagemTemp);
	
    int redQuad = red * red;
	for(int i = 0, k = 1; i < imagemTemp.alt && k < ptr_imagem->alt; i++, k += red) {
		for(int j = 0, l = 1; j < imagemTemp.larg && l < ptr_imagem->larg; j++, l += red) {
            int somaRed = 0;
            int somaGreen = 0;
            int somaBlue = 0;
            for (int m = 0, n = 0, o = 0; m < redQuad; m++) {
                n++;
                if (m % red == 0 && m != 0) {
                    o++;
                }
                if (n > 1) {
                    n = 0;
                }
                if (o > 1) {
                    o = 0;
                }

                somaRed += ptr_imagem->pixel[k - n][l - o].vermelho;
                somaGreen += ptr_imagem->pixel[k - n][l - o].verde;
                somaBlue += ptr_imagem->pixel[k - n][l - o].azul;
            }
		    imagemTemp.pixel[i][j].vermelho = somaRed / redQuad;
            imagemTemp.pixel[i][j].verde = somaGreen / redQuad;
			imagemTemp.pixel[i][j].azul = somaBlue / redQuad;
        }
	}
    
	free(ptr_imagem->pixel);
    ptr_imagem->alt = imagemTemp.alt;
	ptr_imagem->larg = imagemTemp.larg; 
	ptr_imagem->pixel = imagemTemp.pixel;
}

void rotacionar(Ptr_imagem ptr_imagem, int angulo) {
    Imagem imagemTemp;
    imagemTemp.alt = ptr_imagem->larg;
    imagemTemp.larg = ptr_imagem->alt;
    alocarMemoria(&imagemTemp);

    for (int i = ptr_imagem->alt - 1, j = 0; j < ptr_imagem->alt && i >= 0; j++, i--) {
        for (int  k = 0; k < ptr_imagem->larg; k++) {
            imagemTemp.pixel[k][i] = ptr_imagem->pixel[j][k];
        }
    }

    free(ptr_imagem->pixel);
    ptr_imagem->alt = imagemTemp.alt;
    ptr_imagem->larg = imagemTemp.larg;
    ptr_imagem->pixel = imagemTemp.pixel;
}

void filtroMascara(Ptr_imagem ptr_imagem, float mascara[3][3]) {
    Imagem imagemTemp;
    imagemTemp.alt = ptr_imagem->alt;
    imagemTemp.larg = ptr_imagem->larg;
    alocarMemoria(&imagemTemp);

    float vermelho;
    float verde;
    float azul;
    for (int i = 0; i < ptr_imagem->alt; i++) {
        for (int j = 0; j < ptr_imagem->larg; j++) {
            vermelho = 0;
            verde = 0;
            azul = 0;

            if (i > 0) {
                if (j > 0) {
                    vermelho += ptr_imagem->pixel[i - 1][j - 1].vermelho * mascara[0][0];
                    verde += ptr_imagem->pixel[i - 1][j - 1].verde * mascara[0][0];
                    azul += ptr_imagem->pixel[i - 1][j - 1].azul * mascara[0][0];
                }
                vermelho += ptr_imagem->pixel[i - 1][j].vermelho * mascara[0][1];
                verde += ptr_imagem->pixel[i - 1][j].verde * mascara[0][1];
                azul += ptr_imagem->pixel[i - 1][j].azul * mascara[0][1];
                if (j < ptr_imagem->larg - 1) {
                    vermelho += ptr_imagem->pixel[i - 1][j + 1].vermelho * mascara[0][2];
                    verde += ptr_imagem->pixel[i - 1][j + 1].verde * mascara[0][2];
                    azul += ptr_imagem->pixel[i - 1][j + 1].azul * mascara[0][2];
                }
            }
            if (j > 0) {
                vermelho += ptr_imagem->pixel[i][j - 1].vermelho * mascara[1][0];
                verde += ptr_imagem->pixel[i][j - 1].verde * mascara[1][0];
                azul += ptr_imagem->pixel[i][j - 1].azul * mascara[1][0];
            }
            vermelho += ptr_imagem->pixel[i][j].vermelho * mascara[1][1];
            verde += ptr_imagem->pixel[i][j].verde * mascara[1][1];
            azul += ptr_imagem->pixel[i][j].azul * mascara[1][1];
            if (j < ptr_imagem->larg - 1) {
                vermelho += ptr_imagem->pixel[i][j + 1].vermelho * mascara[1][2];
                verde += ptr_imagem->pixel[i][j + 1].verde * mascara[1][2];
                azul += ptr_imagem->pixel[i][j + 1].azul * mascara[1][2];
            }
            if (i < ptr_imagem->alt - 1) {
                if (j > 0) {
                    vermelho += ptr_imagem->pixel[i + 1][j - 1].vermelho * mascara[2][0];
                    verde += ptr_imagem->pixel[i + 1][j - 1].verde * mascara[2][0];
                    azul += ptr_imagem->pixel[i + 1][j - 1].azul * mascara[2][0];
                }
                vermelho += ptr_imagem->pixel[i + 1][j].vermelho * mascara[2][1];
                verde += ptr_imagem->pixel[i + 1][j].verde * mascara[2][1];
                azul += ptr_imagem->pixel[i + 1][j].azul * mascara[2][1];
                if (j < ptr_imagem->larg - 1) {
                    vermelho += ptr_imagem->pixel[i + 1][j + 1].vermelho * mascara[2][2];
                    verde += ptr_imagem->pixel[i + 1][j + 1].verde * mascara[2][2];
                    azul += ptr_imagem->pixel[i + 1][j + 1].azul * mascara[2][2];
                }
            }

            vermelho = vermelho > 255 ? 255 : vermelho < 0 ? 0 : vermelho;
            verde = verde > 255 ? 255 : verde < 0 ? 0 : verde;
            azul = azul > 255 ? 255 : azul < 0 ? 0 : azul;
            imagemTemp.pixel[i][j].vermelho = vermelho;
            imagemTemp.pixel[i][j].verde = verde;
            imagemTemp.pixel[i][j].azul = azul;
        }
    }

    free(ptr_imagem->pixel);
    ptr_imagem->alt = imagemTemp.alt;
    ptr_imagem->larg = imagemTemp.larg;
    ptr_imagem->pixel = imagemTemp.pixel;
}

void filtroBinarizar(Ptr_imagem ptr_imagem, int binarizar) {
    for (int  i = 0; i < ptr_imagem->alt; i++) {
        for (int j  = 0; j < ptr_imagem->larg; j++) {
            int media = (ptr_imagem->pixel[i][j].vermelho + ptr_imagem->pixel[i][j].verde + ptr_imagem->pixel[i][j].azul) / 3;
            if (media > binarizar) {
                ptr_imagem->pixel[i][j].vermelho = 255;
                ptr_imagem->pixel[i][j].verde = 255;
                ptr_imagem->pixel[i][j].azul = 255;
            } else {
                ptr_imagem->pixel[i][j].vermelho = 0;
                ptr_imagem->pixel[i][j].verde = 0;
                ptr_imagem->pixel[i][j].azul = 0;
            }
        }
    }
}

void filtroNegativo(Ptr_imagem ptr_imagem) {
    for (int i = 0; i < ptr_imagem->alt; i++) {
        for (int j = 0; j < ptr_imagem->larg; j++) {
            ptr_imagem->pixel[i][j].vermelho = (unsigned char) (255 - (int) ptr_imagem->pixel[i][j].vermelho);
            ptr_imagem->pixel[i][j].verde = (unsigned char) (255 - (int) ptr_imagem->pixel[i][j].verde);
            ptr_imagem->pixel[i][j].azul = (unsigned char) (255 - (int) ptr_imagem->pixel[i][j].azul);
        }
    }
}

void filtroPixelizar(Ptr_imagem ptr_imagem) {
    Pixel mediaPixel; // i+=1 efeito fica tipo gaussiano
    for (int i = 1; i < ptr_imagem->alt; i+=2) {
        for (int j = 1; j < ptr_imagem->larg; j+=2) {
            mediaPixel.vermelho = (ptr_imagem->pixel[i - 1][j - 1].vermelho + ptr_imagem->pixel[i - 1][j].vermelho + ptr_imagem->pixel[i][j- 1].vermelho + ptr_imagem->pixel[i][j].vermelho) /4;
            mediaPixel.verde = (ptr_imagem->pixel[i - 1][j - 1].verde + ptr_imagem->pixel[i- 1][j].verde + ptr_imagem->pixel[i][j- 1].verde + ptr_imagem->pixel[i][j].verde) /4;
            mediaPixel.azul = (ptr_imagem->pixel[i - 1][j - 1].azul + ptr_imagem->pixel[i- 1][j].azul + ptr_imagem->pixel[i][j- 1].azul + ptr_imagem->pixel[i][j].azul) /4;

            ptr_imagem->pixel[i - 1][j - 1] = mediaPixel;
            ptr_imagem->pixel[i - 1][j] = mediaPixel;
            ptr_imagem->pixel[i][j - 1] = mediaPixel;
            ptr_imagem->pixel[i][j] = mediaPixel;
        }
    }
}

void filtroSobel(Ptr_imagem ptr_imagem) {
    const char borHor[3][3] = {{-1, 0, 1 }, {-2, 0, 2}, {-1, 0, 1}};
    const char borVert[3][3] = {{1, 2, 1},  {0, 0, 0 }, {-1, -2, -1}};
   
    Imagem imagemTemp;
    imagemTemp.alt = ptr_imagem->alt;
    imagemTemp.larg = ptr_imagem->larg;
    alocarMemoria(&imagemTemp);
    
    int valorHor, valorVert, novoPixel;
    
    // Retirar da bordar indíces negativos
    for (int i = 1; i < (ptr_imagem->alt)-1; i++) {
        for (intgcc src/main.c src/funcoes.c -o bin/main -lm j = 1; j < (ptr_imagem->larg)-1; j++) {
            valogcc src/main.c src/funcoes.c -o bin/main -lmrHor = 0;
            valogcc src/main.c src/funcoes.c -o bin/main -lmrVert = 0;

            for (int k = 0; k < 3; k++){
                for (int  l = 0; l < 3; l++){
        
                    valorHor += ((ptr_imagem->pixel[i-1+k][j-1+l].vermelho) * (borHor[k][l]));
                    valorVert += ((ptr_imagem->pixel[i-1+k][j-1+l].vermelho) * (borVert[k][l]));
                } 
            }

            novoPixel = sqrt(pow(valorVert, 2) + pow(valorHor, 2));

            imagemTemp.pixel[i][j].vermelho = novoPixel;
            imagemTemp.pixel[i][j].verde = novoPixel;
            imagemTemp.pixel[i][j].azul = novoPixel;
        } 
    }
    free(ptr_imagem->pixel);
    ptr_imagem->alt = imagemTemp.alt;
    ptr_imagem->larg = imagemTemp.larg;
    ptr_imagem->pixel = imagemTemp.pixel;
}

void filtroGaussiano(Ptr_imagem ptr_imagem) {
    int gaussianos[5][5] = {{ 2,  4,  5,  4, 2 },{ 4,  9, 12,  9, 4 },{ 5, 12, 15, 12, 5 },{ 4,  9, 12,  9, 4 },{ 2,  4,  5,  4, 2 }};

    Imagem imagemTemp;
    imagemTemp.alt = ptr_imagem->larg;
    imagemTemp.larg = ptr_imagem->alt;
    alocarMemoria(&imagemTemp);

    for (int i = 0; i < ptr_imagem->alt; i++) {
        for (int  j = 0; j < ptr_imagem->larg; j++) {
         int vermelho = 0;
         int verde = 0;
         int azul = 0;
            for (int  k = 0; k < 5; k++) {
                for (int l = 0; l < 5; l++) {
                    if(k+2+i < ptr_imagem->alt && k-2+i >= 0 && j-2+1 >= j+2+k < ptr_imagem->larg){

                        vermelho += ptr_imagem->pixel[i-2+k][j-2+l].vermelho * gaussianos[k][l];
                        verde += ptr_imagem->pixel[i-2+k][j-2+l].verde * gaussianos[k][l];
                        azul += ptr_imagem->pixel[i-2+k][j-2+l].azul * gaussianos[k][l];
                    }
                }
                imagemTemp.pixel[i][j].vermelho = vermelho / 159;
                imagemTemp.pixel[i][j].verde = verde / 159;
                imagemTemp.pixel[i][j].azul = azul / 159 ;
            }
        }
    }

    free(ptr_imagem->pixel);
    ptr_imagem->alt = imagemTemp.alt;
    ptr_imagem->larg = imagemTemp.larg;
    ptr_imagem->pixel = imagemTemp.pixel;
}
