#include "funcoes.h"

int alocarMemoria(Ptr_imagem ptr_imagem) {
    if (ptr_imagem->alt * ptr_imagem->larg > 30250000) {
        return 1;
    }
    ptr_imagem->pixel = (Pixel **) malloc(ptr_imagem->alt * sizeof(Pixel *));
    for (int i = 0; i < ptr_imagem->alt; i++) {
        ptr_imagem->pixel[i] = (Pixel *) malloc(ptr_imagem->larg * sizeof(Pixel));
    }
    return 0;
}

void temTipoPPM(char *nomeImagem) {
    int nomeTam = strlen(nomeImagem);
    int achou = 0;
    if (nomeTam > 4) {
        achou = 1;
        int startIndex = nomeTam - 1;
        for (int i = startIndex; i >= 0; i--) {
            if (i == startIndex && nomeImagem[i] != 'm') {
                achou = 0;
                break;
            } else if (i == startIndex - 1 && nomeImagem[i] != 'p') {
                achou = 0;
                break;
            } else if (i == startIndex - 2 && nomeImagem[i] != 'p') {
                achou = 0;
                break;
            } else if (i == startIndex - 3 && nomeImagem[i] != '.') {
                achou = 0;
                break;
            }
        }
    }
    if (achou == 0) {
        strcat(nomeImagem, ".ppm");
    }
}

void lerImagem(Ptr_imagem ptr_imagem) {
    FILE *imagem;
    
    char nomeImagem[50];
    char caminhoImagem[50] = "./img/";

    printf("Digite o nome de uma imagem: ");
    scanf("%s", nomeImagem);
    temTipoPPM(nomeImagem);
    printf("%s\n", nomeImagem);

    strcat(caminhoImagem, nomeImagem);
    imagem = fopen(caminhoImagem, "r");

    if (imagem == NULL) {
        printf("Ocorreu um erro ao abrir a imagem %s\n", nomeImagem);
        exit(1);
    }

    // Leitura do código da imagem. Para confirmar que realmente haverá a manipulação de um arquivo P3
    fscanf(imagem, "%s", ptr_imagem->cod);

    if (strcmp(ptr_imagem->cod, "P3") != 0) {
        printf("Código %s não suportado!\n", ptr_imagem->cod);
        fclose(imagem);
    }

    fscanf(imagem, "%i", &ptr_imagem->larg);
    fscanf(imagem, "%i", &ptr_imagem->alt);

    alocarMemoria(ptr_imagem);

    fscanf(imagem, "%i", &ptr_imagem->max);

    printf("Largura = %i\nAltura = %i\n\n", ptr_imagem->larg, ptr_imagem->alt);

    for (int i = 0; i < ptr_imagem->alt; i++) {
        for (int j = 0; j < ptr_imagem->larg; j++) {
            fscanf(imagem, "%hhu", &ptr_imagem->pixel[i][j].red);
            fscanf(imagem, "%hhu", &ptr_imagem->pixel[i][j].green);
            fscanf(imagem, "%hhu", &ptr_imagem->pixel[i][j].blue);
        }
    }
    fclose(imagem);
}

void gravarImagem(Ptr_imagem ptr_imagem) {
    FILE *imagem;

    char caminhoImagem[50] = "./img-filtros/";
    char nomeImagem[50]; // TODO: tamanho

    printf("Digite o nome para a imagem a ser processada: ");
    scanf("%s", nomeImagem);

    temTipoPPM(nomeImagem);

    strcat(caminhoImagem, nomeImagem);
    imagem = fopen(caminhoImagem, "w");

    fprintf(imagem, "%s\n", ptr_imagem->cod);
    fprintf(imagem, "%i ", ptr_imagem->larg);
    fprintf(imagem, "%i\n", ptr_imagem->alt);
    fprintf(imagem, "%i\n", ptr_imagem->max);

    for (int i = 0; i < ptr_imagem->alt; i++) {
        for (int j = 0; j < ptr_imagem->larg; j++) {
            fprintf(imagem, "%hhu ", ptr_imagem->pixel[i][j].red);
            fprintf(imagem, "%hhu ", ptr_imagem->pixel[i][j].green);
            fprintf(imagem, "%hhu\n", ptr_imagem->pixel[i][j].blue);
        }
    }
    fclose(imagem);
    free(ptr_imagem->pixel);
}

void filtroEscalaCinza(Ptr_imagem ptr_imagem) {
    for (int i = 0; i < ptr_imagem->alt; i++) {
        for (int j = 0; j < ptr_imagem->larg; j++) {
           // Pixel pixel = ptr_imagem->pixel[i][j];
            int mediaCores = (ptr_imagem->pixel[i][j].red + ptr_imagem->pixel[i][j].green + ptr_imagem->pixel[i][j].blue) / 3;
            ptr_imagem->pixel[i][j].red = mediaCores;
            ptr_imagem->pixel[i][j].green = mediaCores;
            ptr_imagem->pixel[i][j].blue = mediaCores;
        }
    }
}

int ampliar(Ptr_imagem ptr_imagem, int amp) {
    // A variável ampliar será responsável por receber a apliação que o usuário deseja usar
    Imagem imagemTemp;
    imagemTemp.larg = ptr_imagem->larg * amp;
    imagemTemp.alt = ptr_imagem->alt * amp;

    int erro = alocarMemoria(&imagemTemp);
    if (erro != 0) {
        printf("A ampliação requerida é muito grande. Digite uma ampliação menor: \n\t");
        return erro;
    }

    for (int i = 0, k = 0; i < ptr_imagem->larg && k < imagemTemp.larg; k++) {
        if (k % amp == 0 && k != 0) {
            i++;
        }
        for (int j = 0, l = 0; j < ptr_imagem->alt && l < imagemTemp.alt; l++) {
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

    return 0;
}

// A redução 1 a 3 apĺica um efeito bem loco, a redução de 4 é a mais fiel sem alteração na cor, de 5 em diante a imagem vai escurecendo
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

                somaRed += ptr_imagem->pixel[k - n][l - o].red;
                somaGreen += ptr_imagem->pixel[k - n][l - o].green;
                somaBlue += ptr_imagem->pixel[k - n][l - o].blue;
            }
		    imagemTemp.pixel[i][j].red = somaRed / redQuad;
            imagemTemp.pixel[i][j].green = somaGreen / redQuad;
			imagemTemp.pixel[i][j].blue = somaBlue / redQuad;
        }
	}
    
	free(ptr_imagem->pixel);
    ptr_imagem->alt = imagemTemp.alt;
	ptr_imagem->larg = imagemTemp.larg; 
	ptr_imagem->pixel = imagemTemp.pixel;
}

void rotacao(Ptr_imagem ptr_imagem, int angulo) {
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

void filtroNegativo(Ptr_imagem ptr_imagem) {
    for (int i = 0; i < ptr_imagem->alt; i++) {
        for (int j = 0; j < ptr_imagem->larg; j++) {
        Pixel pixel = ptr_imagem->pixel[i][j];    
            ptr_imagem->pixel[i][j].red = (unsigned char) (255 - (int) ptr_imagem->pixel[i][j].red);
            ptr_imagem->pixel[i][j].green = (unsigned char) (255 - (int) ptr_imagem->pixel[i][j].green);
            ptr_imagem->pixel[i][j].blue = (unsigned char) (255 - (int) ptr_imagem->pixel[i][j].blue);
        }
    }
}

void filtroBinarizar(Ptr_imagem ptr_imagem, int binarizar) {
    
    for (int  i = 0; i < ptr_imagem->alt; i++){
        for (int j  = 0; j < ptr_imagem->larg; j++){
        Pixel pixel = ptr_imagem->pixel[i][j];
            int mediaCores = (ptr_imagem->pixel[i][j].red + ptr_imagem->pixel[i][j].green + ptr_imagem->pixel[i][j].blue) / 3;
            if (mediaCores > binarizar) {
                ptr_imagem->pixel[i][j].red = 255;
                ptr_imagem->pixel[i][j].green = 255;
                ptr_imagem->pixel[i][j].blue = 255;
            }else {
                ptr_imagem->pixel[i][j].red = 0;
                ptr_imagem->pixel[i][j].green = 0;
                ptr_imagem->pixel[i][j].blue = 0;
            }
        }
        
    }
    


}

void menu(Ptr_imagem ptr_imagem) {
    char efeito[3];

    printf(
        "*--------------------------------------*\n"
        "| PROGRAMA de MANIPULAÇÃO DE IMAGEM    |\n"
        "+--------------------------------------+\n"
        "|  (esc) - Escala de cinza             |\n"
        "|  (amp) - ampliar                     |\n"
        "|  (red) - Reduzir                     |\n"
        "|  (neg) - Negativo                    |\n"
        "|  (rot) - Rotacionar                  |\n"
        "|  (thr) - Binarizar imagem            |\n"
        "|                                      |\n"
        "|                                      |\n"
        "|  (sair) - Sair do Programa           |\n"
        "+--------------------------------------+\n");

    int valido = 0;
    while (valido == 0) {
        printf("Digite a manipulação desejada: ");
        scanf("%s", efeito);

        if (strcmp(efeito, "esc") == 0) {
            valido = 1;
            filtroEscalaCinza(ptr_imagem);
            printf("Realizando Filtro de Escala de Cinza\n\n");
        } else if (strcmp(efeito, "amp") == 0) {
            valido = 1;
            printf("Digite a ampliação: ");
            int amp;
            int erro = 1;
            while (erro != 0) {
                scanf("%i", &amp);
                erro = ampliar(ptr_imagem, amp);
            }
            printf("Realizando Ampliação da Imagem\n\n");
        } else if (strcmp(efeito, "red") == 0) {
            valido = 1;
            printf("Digite a redução: ");
            int red;
            scanf("%i", &red);
            reduzir(ptr_imagem, red);
            printf("Realizando Redução da Imagem\n\n");
        } else if (strcmp(efeito, "neg") == 0) {
            valido = 1;
            filtroNegativo(ptr_imagem);
            printf("Realizando Filtro de Inversão de Cores\n\n");
        } else if (strcmp(efeito, "rot") == 0) {
            valido = 1;
            int angulo;
            printf("Digite o ângulo: ");
            scanf("%d", &angulo);
            if (angulo > 0) {
                for (int i = 0; i < angulo / 90; i++) {
                    rotacao(ptr_imagem, angulo);
                }
            }
        } else if(strcmp(efeito, "thr")==0) {
                int binarizar;
                valido = 1;
                printf("Quanto deseja binarizar?  ");
                scanf("%i", &binarizar);
                filtroBinarizar(ptr_imagem, binarizar);

        } else if (strcmp(efeito, "sair") == 0) {
            printf("Saindo...\n");
            exit(1);
        } else {
            printf("O camando digitado não é válido. ");
        } 
    }
}
