
#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <stdbool.h>
#include <unistd.h>
#include <SDL_mixer.h>


#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#define LOG_ERROR(...) fprintf(stderr, __VA_ARGS__)
#define LOG_INFO(...) fprintf(stdout, __VA_ARGS__)

#define PARALLAX_LAYER_COUNT 6
#define PARALLAX_NUMBERS 3


#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

typedef struct player_s {
    float taffs;
    float taffs_per_click;
    float taffs_per_second;
    int taff_multiplier;
    int upgrades;
} player_t;

typedef struct {
    SDL_Texture *texture;
    SDL_Rect dest_rect;

    int original_w;
    int original_h;

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


typedef struct settings_button_s {
    int x, y, w, h;         // Position et taille du bouton
    SDL_Rect rect;          // Rectangle pour le bouton
    const char *label;      // Texte du bouton
} settings_button_t;

typedef struct upgrade_s {
    char name[32];
    int cost;
    upgrade_type_t type;
    float value;
    SDL_Rect box;
    int owned;
} upgrade_t;


typedef struct parallax_layer_t {
    SDL_Texture* texture;
    SDL_Rect src_rect;
    SDL_Rect dest_rect;
    float speed;         // Vitesse de défilement
    float scroll_speed;  // Vitesse de défilement sur l'axe X
    float x;             // Position horizontale
    int width;
    int height;
} parallax_layer_t;

typedef struct parallax_init_t {
    parallax_layer_t parallax_layers[PARALLAX_LAYER_COUNT];
} parallax_init_t;


typedef struct music_s {
    Mix_Music *menu;
    Mix_Music *gameplay;
    Mix_Music *victory;
    Mix_Music *defeat;
} music_t;




extern upgrade_t upgrades[UPGRADE_COUNT];


typedef struct mouse_pos_s {
    float x;
    float y;
} mouse_pos_t;

typedef struct game_s {
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Texture *texture;
    TTF_Font *font;
    TTF_Font *upgrade_font;

    sprite_t *background;

    sprite_t *puff;

    player_t *player;

    bool quit;
    float delta_time;

    mouse_pos_t mouse_pos;

    Uint32 puff_anim_start;  // temps du dernier clic
    parallax_init_t parallax_init[PARALLAX_NUMBERS];
    bool puff_animating;
    music_t *music;
} game_t;



int init_game(game_t *game);
void run_game(game_t *game);
void free_game(game_t *game);
int handle_event(SDL_Event event, game_t *game);
sprite_t *load_sprite(const char *filepath, SDL_Renderer *renderer, bool size_reduction);
void destroy_sprite(sprite_t *sprite);

void update_delta_time(game_t* game);
music_t *load_music();
void free_music(music_t *music);
void apply_upgrade(upgrade_t *upgrade, player_t *player);
void get_mouse_position(game_t *game);
