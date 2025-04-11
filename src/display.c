#include "puff.h"


void display_text(game_t *game)
{
    char buffer[50];
    snprintf(buffer, sizeof(buffer), "%.2f taffs", game->player->taffs);  
    SDL_Color textColor = {0, 0, 0, 255};  

    SDL_Surface* textSurface = TTF_RenderText_Solid(game->font, buffer, textColor);
    if (!textSurface) {
        printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
        return;
    }

    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(game->renderer, textSurface);
    if (!textTexture) {
        printf("Unable to create texture from surface! SDL_Error: %s\n", SDL_GetError());
        SDL_FreeSurface(textSurface);  
        return;
    }

    int textWidth = textSurface->w;
    int textHeight = textSurface->h;
    SDL_Rect renderQuad = {(SCREEN_WIDTH - textWidth) / 2, 50, textWidth, textHeight};

    SDL_RenderCopy(game->renderer, textTexture, NULL, &renderQuad);

    // Nettoyage
    SDL_DestroyTexture(textTexture);
    SDL_FreeSurface(textSurface);
}

void display_taffs_per_second(game_t *game)
{
    SDL_Color textColor = {0, 0, 0, 255};
    char buffer[50];
    snprintf(buffer, sizeof(buffer), "Taffs/sec: %.2f", game->player->taffs_per_second);

    SDL_Surface* surface = TTF_RenderText_Solid(game->font, buffer, textColor);
    if (!surface) {
        printf("Erreur texte taffs/sec: %s\n", TTF_GetError());
        return;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(game->renderer, surface);
    if (!texture) {
        printf("Erreur texture texte taffs/sec: %s\n", SDL_GetError());
        SDL_FreeSurface(surface);
        return;
    }

    SDL_Rect rect = {
        (SCREEN_WIDTH * 4) / 6,
        (SCREEN_HEIGHT - surface->h) / 10,
        
        surface->w,
        surface->h
    };

    SDL_RenderCopy(game->renderer, texture, NULL, &rect);

    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
}


void run_game(game_t *game)
{
    SDL_Event event;
    Uint32 last_tick = SDL_GetTicks(); 



    while (!game->quit)
    {
        while (SDL_PollEvent(&event))
            handle_event(event, game);

        Uint32 current_tick = SDL_GetTicks();
        if (current_tick - last_tick >= 1000) {
            game->player->taffs += game->player->taffs_per_second;
            last_tick = current_tick;

            LOG_INFO("Gain passif: %.2f taffs (total: %.2f)\n", 
                     game->player->taffs_per_second, 
                     game->player->taffs);
        }

        SDL_SetRenderDrawColor(game->renderer, 189, 189, 189, 255);
        SDL_RenderClear(game->renderer);

        if (game->puff_animating) {
            Uint32 now = SDL_GetTicks();
            Uint32 elapsed = now - game->puff_anim_start;
        
            if (elapsed >= 200) {
                // Animation terminée
                game->puff_animating = false;
                game->puff->dest_rect.w = game->puff->original_w;
                game->puff->dest_rect.h = game->puff->original_h;
                game->puff->dest_rect.x = (SCREEN_WIDTH - game->puff->dest_rect.w) / 2;
                game->puff->dest_rect.y = (SCREEN_HEIGHT - game->puff->dest_rect.h) / 2;
            } else {
                // Phase d'animation : réduction puis retour
                float progress = elapsed / 200.0f; // 0.0 à 1.0
                float scale = 1.0f - 0.1f * sinf(progress * M_PI); // effet "smooth"
        
                game->puff->dest_rect.w = game->puff->original_w * scale;
                game->puff->dest_rect.h = game->puff->original_h * scale;
                game->puff->dest_rect.x = (SCREEN_WIDTH - game->puff->dest_rect.w) / 2;
                game->puff->dest_rect.y = (SCREEN_HEIGHT - game->puff->dest_rect.h) / 2;
            }
        }

        SDL_RenderCopy(game->renderer, game->puff->texture, NULL, &game->puff->dest_rect);
        display_text(game);  // (si display_text fonctionne bien)
        display_taffs_per_second(game);

        SDL_RenderPresent(game->renderer);
        SDL_Delay(16);  // ~60 FPS
    }
}
