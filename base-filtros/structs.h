//Struct que define os elementos r, g e b de cada pixel
typedef struct{
	int red, green, blue;
}pixel;

//Struct de imagem que contém uma matriz de pixeis, além das outras informações contidas no arquivo ppm
typedef struct{
	pixel **pix_imagem;
	char codigo[3];
	int qualidade, colunas, linhas;
}imagem, *pont_imagem;