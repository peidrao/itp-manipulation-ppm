<h1> Projeto de Manipulação de Imagem </h1>

<h4>O que o projeto atendeu?</h4>
<ul>
<li>Uso de arranjos / matrizes.</li>
<li>Uso de registros (struct).</li>
<li>Definição de novos tipos de dados através de typedef.</li>
<li>Uso de alocação dinâmica.</li>
<li>Pelo menos uma função/procedimento que usa recursão (Não foi implementado).</li>
<li>Leitura de arquivos.</li>
<li>Modularização do programa em diferentes arquivos (uso de diferentes arquivos .c e .h, cada um com sua funcionalidade).
  <ul>
  <li><b>edicao.c</b> - Todas as funções desde filtros e outras manipulações que fazem as transformações nas imagens</li>
  <li><b>edicao.h</b> - Declaração de todas as funções</li>
  <li><b>main.c</b> - Onde ocorre a leitura da imagem, o menu é dado ao usuário e ocorre a gravação da imagem</li>
  <li><b>structs.h</b> - Estruturas onde são trabalhados os pixels e as informações de cada imagem como a largura e sua altura, entre outras</li>
  </ul>
</li> 
<li>Definição de um padrão de indentação do código fonte e de nomenclatura das sub-rotinas e variáveis, e a adequação a este padrão.</li>
<li>Documentação adequada do código-fonte.</li>
</ul>

<h4>Funções que foram feitas em todo o projeto:</h4>

<b>alocamemoria:</b> Alocação da memória em toda a imagem (Precisa melhorar essa descrição).

<b>temTipoPPM:</b> Escreve a extensão da imagem sem que o usuário precise digitar "nome_imagem.ppm" e sim "nomeimagem".

<b>lerImagem:</b> Leitura da imagem.

<b>filtroEscalaCinza:</b> Filtro para aplicar a escala cinza.

<b>ampliar:</b> Realiza a ampliação da resolução da imagem

<b>reduzir:</b> Realiza a redução da resolução da imagem

<b>rotacao:</b> Rotaciona a imagem dado os ângulos de 90°, 180° ou 270°

<b>gravarImagem:</b> Após passar pelo filtro que o usuário selecionou, a imagem será salva.

<b>menu:</b> Onde o usuário escolherá quais filtros serão aplicados na imagem.

<h4>Funcionalidades complementares </h4>

<b>GTK (Interface em gtk)</b>: O usuário usará uma interface para aplicar os efeitos que deseja em vez de usar o terminal (usando apenas para compilar o programa).

<b>filtronNegativo:</b> Inverte as cores da imagem

<b>filtroBinarizar (Metodo de limimiar por threshold):</b> Determina-se um nível de cinza a partir de qualquer ponto qu for acessado. 

<b>Pixelizar:</b> A média dos três pixeis modificados é aplicado aos pixeis originais.

<b>filtroSobel:</b> Detecta as bordas horizontais e verticais da imagem em escala de cinza, e assim a imagem é transformada de RGB para a escala de cinza e o resultado é uma imagem com contornos brancos.

<b>filtroGaussiano:</b> Filtro que realiza o desfoque da imagem. Pixeis que são similares são desfocados entre si

O que seria feito de diferente?

<h4>COMPILAÇÃO DO ARQUIVO</h4>
Basta digitar no terminal,
 
<blockquote> gcc src/edicao.c src/main.c -o bin/main -lm `pkg-config --cflags --libs gtk+-3.0` -export-dynamic </blockquote>

E logo após,

<blockquote>gcc src/edicao.c src/main.c -o bin/main -lm `pkg-config --cflags --libs gtk+-3.0` -export-dynamic -Wall -ggdb </blockquote>
 
Com isso a inteface em gtk será iniciada automaticamente, contudo é necessário que o usuário tenha o gtk+3.0, e suas respectivas depêndencias do mesmo em sua distribuição, caso o usuário não possua o programa não iniciará, para isso basta que o mesmo faça a intalação em sua distribuição:

Distribuições Debian/Ubuntu:
<blockquote>sudo apt-get install libgtk-3-dev</blockquote>

Contribuição