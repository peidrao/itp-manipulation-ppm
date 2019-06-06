**Projeto de Manipulação de Imagem**

O projeto, abrigou todas os filtros e funcionalidades que eram para está contidas, desde o filtro de escala cinza até a detecção de bordas.
Funções aplicadas (funcoes.c)

alocamemoria: Alocação da memória em toda a imagem (Precisa melhorar essa descrição)

temTipoPPM: Escrever o nome da imagem sem a necessidade do usuário digitar sua extensão ".ppm".

lerImagem: Leitura da imagem.

filtroEscalaCinza: Filtro para aplicar a escala cinza.

ampliar: Realiza a ampliação da resolução da imagem

zoomOut: Realiza a redução da resolução da imagem

negativo: Inverte as cores da imagem

gravarImagem: Após passar pelo filtro que o usuário selecionou, a imagem será salva.

menu: Onde o usuário escolherá quais filtros serão aplicados na imagem.



COMPILAÇÃO DO ARQUIVO
Para compilar o arquivo, basta que o usuário esteja na pasta *src*,

`gcc main.c funcoes.c -o nomeDoArquivo` 
 
ou também na pasta onde estão os todos os arquivos do projeto, basta digitar no terminal,
 
`gcc src/main.c src/funcoes.c -o bin/main` 
 
E logo após no terminal ainda, basta digitar ./nomeDoArquivo