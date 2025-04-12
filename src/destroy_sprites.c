#include "puff.h"
void destroy_sprite(sprite_t *sprite)
{
    if (sprite) {
        SDL_DestroyTexture(sprite->texture);
        free(sprite);
    }
}


