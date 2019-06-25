all: Imageeditor

Imageeditor: main.o funcoes.o
	gcc -o Imageeditor main.o funcoes.o

funcoes.o: funcoes.c funcoes.h
	gcc -o funcoes.o -c funcoes.c

main.o: main.c funcoes.h
	gcc -o main.o -c main.c

.PHONY: clean 

clean: 
	rm ./Imageeditor
	rm  ./*.o