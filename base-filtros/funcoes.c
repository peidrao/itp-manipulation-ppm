#include "funcoes.h"

void criarMatrizPixeis(pont_imagem Imagem){
	int i;
	Imagem->pix_imagem = (pixel**)malloc(Imagem->linhas * sizeof(pixel*));
	for(i = 0; i < Imagem->linhas; i++){
		Imagem->pix_imagem[i] = (pixel*)malloc(Imagem->colunas * sizeof(pixel));
	}
}

void lerImagem(pont_imagem Imagem){
	FILE *imagem;
	int i, j;
	char nomeImagem[50];

	printf("Digite o nome da imagem a ser aberta: ");
	scanf("%s", nomeImagem);

	imagem = fopen(nomeImagem, "r");

	if(imagem == NULL){
		printf("Houve um erro ao abrir a imagem\n");
		exit(1);
	}
	
	fscanf(imagem,"%s",Imagem->codigo);
	fscanf(imagem,"%i",&Imagem->colunas);
	fscanf(imagem,"%i",&Imagem->linhas);
	criarMatrizPixeis(Imagem);
	fscanf(imagem,"%i",&Imagem->qualidade);

	for(i = 0; i < Imagem->linhas; i++){
		for(j = 0; j < Imagem->colunas; j++){
			fscanf(imagem,"%i",&Imagem->pix_imagem[i][j].red);
			fscanf(imagem,"%i",&Imagem->pix_imagem[i][j].green);
			fscanf(imagem,"%i",&Imagem->pix_imagem[i][j].blue);
		}
	}

	fclose(imagem);
}

void salvarImagem(pont_imagem Imagem){
	FILE *imagem;
	int i, j;
	char nome_imagem[100];
	printf("Digite o caminho e nome da imagem a ser salva: ");
	scanf("%s", nome_imagem);

	imagem = fopen(nome_imagem, "w");

	fprintf(imagem,"%s\n",Imagem->codigo);
	fprintf(imagem,"%i ",Imagem->colunas);
	fprintf(imagem,"%i\n",Imagem->linhas);
	fprintf(imagem,"%i\n",Imagem->qualidade);

	for(i = 0; i < Imagem->linhas; i++){
		for(j = 0; j < Imagem->colunas; j++){
			fprintf(imagem,"%i ",Imagem->pix_imagem[i][j].red);
			fprintf(imagem,"%i ",Imagem->pix_imagem[i][j].green);
			fprintf(imagem,"%i\n",Imagem->pix_imagem[i][j].blue);
		}
	}
	fclose(imagem);
	free(Imagem->pix_imagem);
}

void espelharHorizontal(pont_imagem Imagem){
	int i, j, l;

	imagem ImagemLoc;
	ImagemLoc.linhas = Imagem->linhas;
	ImagemLoc.colunas = Imagem->colunas;
	criarMatrizPixeis(&ImagemLoc);

	for(i = 0; i < Imagem->linhas; i++){
		for(j = 0, l = Imagem->colunas - 1; j < Imagem->colunas && l >= 0; j++, l--){
			ImagemLoc.pix_imagem[i][l] = Imagem->pix_imagem[i][j];
		}
	}
	free(Imagem->pix_imagem);
	Imagem->pix_imagem = ImagemLoc.pix_imagem;
}

void espelharVertical(pont_imagem Imagem){
	int i, j, k;

	imagem ImagemLoc;
	ImagemLoc.linhas = Imagem->linhas;
	ImagemLoc.colunas = Imagem->colunas;
	criarMatrizPixeis(&ImagemLoc);

	for(j = 0; j < Imagem->linhas; j++){
		for(i = 0, k = Imagem->linhas - 1; i < Imagem->linhas && k >= 0; i++, k--){
			ImagemLoc.pix_imagem[k][j] = Imagem->pix_imagem[i][j];
		}
	}
	free(Imagem->pix_imagem);
	Imagem->pix_imagem = ImagemLoc.pix_imagem;
}

void girarAntiHorario(pont_imagem Imagem){
	int i, j, l;
	
	imagem ImagemLoc;
	ImagemLoc.linhas = Imagem->colunas;
	ImagemLoc.colunas = Imagem->linhas;
	criarMatrizPixeis(&ImagemLoc);
	
	for(j = Imagem->colunas - 1, l = 0; l < Imagem->linhas && j >= 0; j--, l++){
		for(i = 0; i < Imagem->linhas; i++){
			ImagemLoc.pix_imagem[l][i] = Imagem->pix_imagem[i][j];
		}
	}
	free(Imagem->pix_imagem);
	Imagem->pix_imagem = ImagemLoc.pix_imagem;
	Imagem->colunas = ImagemLoc.colunas;
	Imagem->linhas = ImagemLoc.linhas;
}

void girarHorario(pont_imagem Imagem){
	int i, j, l;
	
	imagem ImagemLoc;
	ImagemLoc.linhas = Imagem->colunas;
	ImagemLoc.colunas = Imagem->linhas;
	criarMatrizPixeis(&ImagemLoc);
	
	for(l = Imagem->colunas - 1, i = 0; i < Imagem->linhas && l >= 0; i++, l--){
		for(j = 0; j < Imagem->colunas; j++){
			ImagemLoc.pix_imagem[j][l] = Imagem->pix_imagem[i][j];
		}
	}
	free(Imagem->pix_imagem);
	Imagem->pix_imagem = ImagemLoc.pix_imagem;
	Imagem->colunas = ImagemLoc.colunas;
	Imagem->linhas = ImagemLoc.linhas;
}

void threshold(pont_imagem Imagem, int limite){
	int mediaCores, i, j;
	for(i = 0; i < Imagem->linhas; i++){
		for(j = 0; j < Imagem->colunas; j++){
			mediaCores = (Imagem->pix_imagem[i][j].green + Imagem->pix_imagem[i][j].red + Imagem->pix_imagem[i][j].blue) / 3;
			if(mediaCores > limite){
				Imagem->pix_imagem[i][j].green = 255;
				Imagem->pix_imagem[i][j].red = 255;
				Imagem->pix_imagem[i][j].blue = 255;
			}else{
				Imagem->pix_imagem[i][j].green = 0;
				Imagem->pix_imagem[i][j].red = 0;
				Imagem->pix_imagem[i][j].blue = 0;
			}
		}
	}
}

void negativo(pont_imagem Imagem){
	int i, j;
	for(i = 0; i < Imagem->linhas; i++){
		for(j = 0; j < Imagem->colunas; j++){
			Imagem->pix_imagem[i][j].red = 255 - Imagem->pix_imagem[i][j].red;
			Imagem->pix_imagem[i][j].green = 255 - Imagem->pix_imagem[i][j].green;
			Imagem->pix_imagem[i][j].blue = 255 - Imagem->pix_imagem[i][j].blue;
		}
	}
}

void ampliar(pont_imagem Imagem, int zoom){
	int i, j, k, l;

	imagem ImagemLoc;
	ImagemLoc.linhas = Imagem->linhas * zoom;
	ImagemLoc.colunas = Imagem->colunas * zoom;
	criarMatrizPixeis(&ImagemLoc);
	
	for(i = 0, k = 0; i < Imagem->linhas && k < ImagemLoc.linhas; k ++){
		if(k % zoom == 0 && k != 0){
			i++;
		}
		for(j = 0, l = 0; j < Imagem->colunas && l < ImagemLoc.colunas;  l++){
			if(l % zoom == 0 && l != 0){
				j++;
			}
			ImagemLoc.pix_imagem[k][l] = Imagem->pix_imagem[i][j];
		}
	}
	free(Imagem->pix_imagem);
	Imagem->linhas = ImagemLoc.linhas;
	Imagem->colunas = ImagemLoc.colunas;
	Imagem->pix_imagem = ImagemLoc.pix_imagem;
}

void reduzir(pont_imagem Imagem){
	int i, j, k, l;
	
	imagem ImagemLoc;
	ImagemLoc.linhas = Imagem->linhas / 2;
	ImagemLoc.colunas = Imagem->colunas / 2;
	criarMatrizPixeis(&ImagemLoc);
	
	for(i = 0, k = 1; i < ImagemLoc.linhas && k < Imagem->linhas; i++, k += 2){
		for(j = 0, l = 1; j < ImagemLoc.colunas && l < Imagem->colunas; j++, l += 2){
			ImagemLoc.pix_imagem[i][j].red = (Imagem->pix_imagem[k - 1][l - 1].red + Imagem->pix_imagem[k - 1][l].red + Imagem->pix_imagem[k][l - 1].red + Imagem->pix_imagem[k][l].red) / 4;
			ImagemLoc.pix_imagem[i][j].green = (Imagem->pix_imagem[k - 1][l - 1].green + Imagem->pix_imagem[k - 1][l].green + Imagem->pix_imagem[k][l - 1].green + Imagem->pix_imagem[k][l].green) / 4;
			ImagemLoc.pix_imagem[i][j].blue = (Imagem->pix_imagem[k - 1][l - 1].blue + Imagem->pix_imagem[k - 1][l].blue + Imagem->pix_imagem[k][l - 1].blue + Imagem->pix_imagem[k][l].blue) / 4;
		}
	}
	free(Imagem->pix_imagem);
	Imagem->linhas = ImagemLoc.linhas;
	Imagem->colunas = ImagemLoc.colunas;
	Imagem->pix_imagem = ImagemLoc.pix_imagem;	
}

void pixelizar(pont_imagem Imagem){
	int i, j;
	pixel MediaPixeis;
	for(i = 1; i < Imagem->linhas; i += 2){
		for(j = 1; j < Imagem->colunas; j += 2){
			MediaPixeis.red = (Imagem->pix_imagem[i - 1][j - 1].red + Imagem->pix_imagem[i - 1][j].red + Imagem->pix_imagem[i][j - 1].red + Imagem->pix_imagem[i][j].red) / 4;
			MediaPixeis.green = (Imagem->pix_imagem[i - 1][j - 1].green + Imagem->pix_imagem[i - 1][j].green + Imagem->pix_imagem[i][j - 1].green + Imagem->pix_imagem[i][j].green) / 4;
			MediaPixeis.blue = (Imagem->pix_imagem[i - 1][j - 1].blue + Imagem->pix_imagem[i - 1][j].blue + Imagem->pix_imagem[i][j - 1].blue + Imagem->pix_imagem[i][j].blue) / 4;
			Imagem->pix_imagem[i - 1][j - 1] = MediaPixeis;
			Imagem->pix_imagem[i - 1][j] = MediaPixeis;
			Imagem->pix_imagem[i][j - 1] = MediaPixeis;
			Imagem->pix_imagem[i][j] = MediaPixeis;
		}
	}
}

void escalaCinza(pont_imagem Imagem){
	int i, j;
	int mediaCores;
	for(i = 0; i < Imagem->linhas; i++){
		for(j = 0; j < Imagem->colunas; j++){
			mediaCores = (Imagem->pix_imagem[i][j].red + Imagem->pix_imagem[i][j].green + Imagem->pix_imagem[i][j].blue) / 3;
			Imagem->pix_imagem[i][j].red = mediaCores;
			Imagem->pix_imagem[i][j].green = mediaCores;
			Imagem->pix_imagem[i][j].blue = mediaCores;
		}
	}
}

void aplicarEfeito(pont_imagem Imagem, int efeito[3][3], int divisor){
	int i = 0, j = 0, k, l;
	pixel somaElementos;
	somaElementos.red = 0;
	somaElementos.green = 0;
	somaElementos.blue = 0;

	imagem ImagemLoc;
	ImagemLoc.linhas = Imagem->linhas;
	ImagemLoc.colunas = Imagem->colunas;
	criarMatrizPixeis(&ImagemLoc);
	
	do{
		k = 0;
		l = 0;
		do{
			somaElementos.red += Imagem->pix_imagem[i + k][j + l].red * efeito[k][l];
			somaElementos.green += Imagem->pix_imagem[i + k][j + l].green * efeito[k][l];
			somaElementos.blue += Imagem->pix_imagem[i + k][j + l].blue * efeito[k][l];
			if(l == 2){
				l = 0;
				k++;
			}else{
				l++;
			}
		}while(k < 3);
		somaElementos.red /= divisor;
		somaElementos.green /= divisor;
		somaElementos.blue /= divisor;
		if(somaElementos.red > 255)
			somaElementos.red = Imagem->qualidade;
		if(somaElementos.green > 255)
			somaElementos.green = Imagem->qualidade;
		if(somaElementos.blue > 255)
			somaElementos.blue = Imagem->qualidade;
		if(somaElementos.red < 0)
			somaElementos.red = 0;
		if(somaElementos.green < 0)
			somaElementos.green = 0;
		if(somaElementos.blue < 0)
			somaElementos.blue = 0;
		ImagemLoc.pix_imagem[i + 1][j + 1] = somaElementos;
		somaElementos.red = 0;
		somaElementos.green = 0;
		somaElementos.blue = 0;
		if(j == Imagem->colunas - 3){
			j = 0;
			i++;
		}else{
			j++;
		}
	}while(i < Imagem->linhas - 2);
	for(i = 0; i < Imagem->linhas; i++){
		for(j = 0; j < Imagem->colunas; j++){
			if(i == 0 || i == Imagem->linhas - 1 || j == 0 || j == Imagem->colunas - 1){
				ImagemLoc.pix_imagem[i][j] = Imagem->pix_imagem[i][j];
			}
		}
	}
	free(Imagem->pix_imagem);
	Imagem->linhas = ImagemLoc.linhas;
	Imagem->colunas = ImagemLoc.colunas;
	Imagem->pix_imagem = ImagemLoc.pix_imagem;	
}

void menu(pont_imagem Imagem){
	
	int Blurring[3][3] = {{1, 1, 1}, {1, 1, 1}, {1, 1, 1}};

	int DetectorBorda[3][3] = {{-1, -1, -1},{-1, 8, -1},{-1, -1, -1}};

	int Sharpe[3][3] = {{0, -1, 0},{-1, 5, -1},{0, -1, 0}};

	int i, zoom;

	int angulo, limite;

	char opc[3];

	printf("thr - Thresholding\n");
	printf("neg - Negativo\n");
	printf("rot - Rotacionar Imagem\n");
	printf("amp - Ampliar Imagem\n");
	printf("red - Reduzir Imagem\n");
	printf("hor - Espelhar Horizontalmente\n");
	printf("ver - Espelhar Verticalmente\n");
	printf("pix - Pixelizar Imagem\n");
	printf("esc - Escala de Cinza\n");
	printf("bor - Detectar Bordas\n");
	printf("blu - Blurring\n");
	printf("sha - Sharpening\n");
	printf("ext - Sair\n");
	printf("Digite uma das opcoes: ");
	scanf("%s", opc);
	if(strcmp(opc, "thr") == 0){
		printf("Digite um valor base para binarizar: ");
		scanf("%i", &limite);
		threshold(Imagem, limite);
	}else if(strcmp(opc, "neg") == 0){
		negativo(Imagem);
	}else if(strcmp(opc, "rot") == 0){
		printf("Digite o angulo: ");
		scanf("%i",&angulo);
		if(angulo > 0){
			for(i = 0; i < angulo / 90; i++){
				girarHorario(Imagem);
			}
		}else if(angulo < 0){
			for(i = 0; i < angulo / -90; i++){
				girarAntiHorario(Imagem);
			}
		}
	}else if(strcmp(opc, "ext") == 0){
		exit(1);
	}else if(strcmp(opc, "red") == 0){
		reduzir(Imagem);
	}else if(strcmp(opc, "amp") == 0){
		printf("Digite o zoom: ");
		scanf("%i", &zoom);
		ampliar(Imagem, zoom);
	}else if(strcmp(opc, "pix") == 0){
		pixelizar(Imagem);
	}else if(strcmp(opc, "esc") == 0){
		escalaCinza(Imagem);
	}else if(strcmp(opc, "bor") == 0){
		aplicarEfeito(Imagem, DetectorBorda, 1);
	}else if(strcmp(opc, "blu") == 0){
		aplicarEfeito(Imagem, Blurring, 9);
	}else if(strcmp(opc, "sha") == 0){
		aplicarEfeito(Imagem, Sharpe, 1);
	}else if(strcmp(opc, "hor") == 0){
		espelharHorizontal(Imagem);
	}else if(strcmp(opc, "ver") == 0){
		espelharVertical(Imagem);
	}else{
		printf("Operacao nao reconhecida\n");
		menu(Imagem);
	}
	printf("Deseja realizar outra operacao? S(sim)/N(nao): ");
	scanf("%s", opc);
	if(strcmp(opc, "S") == 0){
		menu(Imagem);
	}
}