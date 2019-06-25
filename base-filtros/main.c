#include "funcoes.h"

int main(){
	imagem Imagem;
	lerImagem(&Imagem);
	menu(&Imagem);
	salvarImagem(&Imagem);
	return 0;
}