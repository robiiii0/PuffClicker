
#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <stdbool.h>
#include <unistd.h>

#include <SDL2/SDL.h>

#define LOG_ERROR(...) fprintf(stderr, __VA_ARGS__)
#define LOG_INFO(...) fprintf(stdout, __VA_ARGS__)

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

typedef struct game_s {
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Texture *texture;

    bool quit;
} game_t;



int init_game(game_t *game);
void run_game(game_t *game);
void free_game(game_t *game);
int handle_event(SDL_Event event, game_t *game);