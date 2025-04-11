
#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <stdbool.h>
#include <unistd.h>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#define LOG_ERROR(...) fprintf(stderr, __VA_ARGS__)
#define LOG_INFO(...) fprintf(stdout, __VA_ARGS__)

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

typedef struct player_s {
    int taffs;
    int taffs_per_click;
    int upgrades;
} player_t;

typedef struct {
    SDL_Texture *texture;
    SDL_Rect dest_rect;
} sprite_t;


//////////////////////////////
// Structure pour les upgrades
//////////////////////////////

#define UPGRADE_COUNT 5

typedef enum upgrade_type_e {
    UPGRADE_TAFF_PER_CLICK,
    UPGRADE_AUTO_TAFF,
    UPGRADE_MULTIPLIER,
} upgrade_type_t;

typedef struct upgrade_s {
    char name[32];
    int cost;
    upgrade_type_t type;
    float value; // Ex: +1 taff par clic, +0.5 taffs/sec, ou x2 production
    SDL_Rect box;
    bool purchased; // pour ne pas la racheter
} upgrade_t;


extern upgrade_t upgrades[UPGRADE_COUNT];


typedef struct game_s {
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Texture *texture;
    TTF_Font *font;
    TTF_Font *upgrade_font;

    sprite_t *puff;

    player_t *player;

    bool quit;
} game_t;



int init_game(game_t *game);
void run_game(game_t *game);
void free_game(game_t *game);
int handle_event(SDL_Event event, game_t *game);
sprite_t *load_sprite(const char *filepath, SDL_Renderer *renderer);
void destroy_sprite(sprite_t *sprite);
