#include "puff.h"

sprite_t *load_sprite(const char *filepath, SDL_Renderer *renderer)
{
    SDL_Surface *surface = IMG_Load(filepath);
    if (!surface) {
        LOG_ERROR("Erreur chargement image: %s\n", IMG_GetError());
        return NULL;
    }

    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (!texture) {
        LOG_ERROR("Erreur texture: %s\n", SDL_GetError());
        SDL_FreeSurface(surface);
        return NULL;
    }

    int original_w = surface->w;
    int original_h = surface->h;
    SDL_FreeSurface(surface);

    // Taille réduite (ex: moitié)
    int new_w = original_w / 2;
    int new_h = original_h / 2;

    sprite_t *sprite = malloc(sizeof(sprite_t));
    sprite->texture = texture;
    sprite->dest_rect.w = new_w;
    sprite->dest_rect.h = new_h;

    // Centrage
    sprite->dest_rect.x = (SCREEN_WIDTH - new_w) / 2;
    sprite->dest_rect.y = (SCREEN_HEIGHT - new_h) / 2;

    return sprite;
}

