SDL_PATH = /opt/homebrew/Cellar/sdl2/2.30.7

CC = gcc

CFLAGS = -Wall -Wextra -I include
CFLAGS += -Wno-unused-parameter -Wno-unused-variable -Wno-unused-function
CFLAGS += -I$(SDL_PATH)/include

LDFLAGS = -L$(SDL_PATH)/lib -lSDL2

BIN = puff_clicker

SRC = $(wildcard src/*.c)
# SRC += $(wildcard src/*/*.c)

OBJ = $(SRC:.c=.o)

all: $(BIN)

$(BIN): $(OBJ)
	$(CC) $(OBJ) -o $(BIN) $(CFLAGS) $(LDFLAGS)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(BIN)

re: fclean all
