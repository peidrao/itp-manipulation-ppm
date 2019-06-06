#folder = main

code = main

EXEC_NAME = $(code)
EXEC_DIR  = ./bin
INC_DIR   = ./inc
LIB_DIR   = ./lib
SRC_DIR   = ./src/$(folder)

CC     = gcc
CFLAGS = -g
LIBS   = -lm -lconsole

EXEC = $(EXEC_DIR)/$(EXEC_NAME)
SRC = $(SRC_DIR)/$(code).c
OBJ  = $(SRC:.c=.o)

%.o: %.c
	$(CC) $< -o $@ -c $(CFLAGS) -I$(INC_DIR)

$(EXEC): $(OBJ)
	$(CC) $^ -o $@ -L$(LIB_DIR) $(LIBS)

.PHONY: clean
clean:
	rm -f ./src/*.o ./bin/*