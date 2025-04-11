SDL_PATH = /opt/homebrew/Cellar/sdl2/2.30.7
SDL_IMAGE_PATH = /opt/homebrew/Cellar/sdl2_image/2.8.8
SDL_TTF_PATH = /opt/homebrew/Cellar/sdl2_ttf/2.24.0

CC = gcc

CFLAGS = -Wall -Wextra -I include
CFLAGS += -Wno-unused-parameter -Wno-unused-variable -Wno-unused-function
CFLAGS += -I$(SDL_PATH)/include/SDL2
CFLAGS += -I$(SDL_IMAGE_PATH)/include/SDL2
CFLAGS += -I$(SDL_TTF_PATH)/include/SDL2

LDFLAGS = -L$(SDL_PATH)/lib -L$(SDL_IMAGE_PATH)/lib -L$(SDL_TTF_PATH)/lib -lSDL2 -lSDL2_image -lSDL2_ttf

BIN = puff_clicker

SRC = $(wildcard src/*.c)
OBJ = $(SRC:.c=.o)

all: $(BIN)

$(BIN): $(OBJ)
	$(CC) $(OBJ) -o $(BIN) $(CFLAGS) $(LDFLAGS)
	mv $(OBJ) bin/

clean:
	rm -f bin/*.o

fclean: clean
	rm -f $(BIN)

re: fclean all
