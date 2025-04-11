#include "puff.h"

sprite_t *load_sprite(const char *filepath, SDL_Renderer *renderer)
{
    SDL_Surface *surface = IMG_Load(filepath);
    if (!surface) {
        LOG_ERROR("Erreur chargement image: %s\n", IMG_GetError());
        return NULL;
    }

    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    if (!texture) {
        LOG_ERROR("Erreur texture: %s\n", SDL_GetError());
        return NULL;
    }

    sprite_t *sprite = malloc(sizeof(sprite_t));
    sprite->texture = texture;
    sprite->dest_rect.x = 100;  // position par défaut
    sprite->dest_rect.y = 100;
    SDL_QueryTexture(texture, NULL, NULL, &sprite->dest_rect.w, &sprite->dest_rect.h);

    return sprite;
}
