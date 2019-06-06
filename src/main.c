#include "funcoes.h"

void main() {
  Imagem imagem;
  lerImagem(&imagem); // Resposnsável por fazer toda a leitura da imagem
  menu(&imagem);  // Menu com as opções de filtros. 
  gravarImagem(&imagem); // Após a imagem ser lida e o usuário escolher o filtro que será aplciada a mesma, essa função irá salvar a imagem em um arquivo modificado pelo filtro.
}