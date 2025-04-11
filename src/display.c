#include "puff.h"


void display_upgrades(game_t *game)
{
    int count = UPGRADE_COUNT;
    SDL_Renderer *renderer = game->renderer;
    TTF_Font *font = game->upgrade_font;

    SDL_Color bgColor = {0, 0, 0, 255};      // gris foncé
    SDL_Color textColor = {255, 255, 255, 255}; // blanc

    for (int i = 0; i < count; i++) {
        // Affiche le fond de la box
        SDL_SetRenderDrawColor(renderer, bgColor.r, bgColor.g, bgColor.b, bgColor.a);
        SDL_RenderFillRect(renderer, &upgrades[i].box);

        // Affiche le nom
        char buffer[64];
        snprintf(buffer, sizeof(buffer), "%s - %d taffs", upgrades[i].name, upgrades[i].cost);
        SDL_Surface *surface = TTF_RenderText_Blended(font, buffer, textColor);
        SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);

        int textW, textH;
        SDL_QueryTexture(texture, NULL, NULL, &textW, &textH);
        SDL_Rect textRect = {
            upgrades[i].box.x + 10,
            upgrades[i].box.y + (upgrades[i].box.h - textH) / 2,
            textW,
            textH
        };

        SDL_RenderCopy(renderer, texture, NULL, &textRect);

        SDL_FreeSurface(surface);
        SDL_DestroyTexture(texture);
    }
}

void display_text(game_t *game)
{
    // Afficher le texte (Taffs)
    char buffer[50];
    snprintf(buffer, sizeof(buffer), "%d taffs", game->player->taffs);

    SDL_Color textColor = {0, 0, 0, 255};  // Couleur du texte (noir)
    // Créer la surface de texte
    SDL_Surface* textSurface = TTF_RenderText_Solid(game->font, buffer, textColor);
    if (!textSurface) {
        printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
        return;
    }

    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(game->renderer, textSurface);
    if (!textTexture) {
        printf("Unable to create texture from surface! SDL_Error: %s\n", SDL_GetError());
        return;
    }

    int textWidth = textSurface->w;
    int textHeight = textSurface->h;
    SDL_Rect renderQuad = {(SCREEN_WIDTH - textWidth) / 2, 50, textWidth, textHeight};

    // Rendre le texte
    SDL_RenderCopy(game->renderer, textTexture, NULL, &renderQuad);

}

void run_game(game_t *game)
{
    while (!game->quit)
    {
        SDL_Event event;

        while (SDL_PollEvent(&event))
            handle_event(event, game);

        if (game->quit)
            break;

        SDL_SetRenderDrawColor(game->renderer, 189, 189, 189, 255);
        SDL_RenderClear(game->renderer);
        // draw everything here
        SDL_RenderCopy(game->renderer, game->puff->texture, NULL, &game->puff->dest_rect);
        display_text(game);
        display_upgrades(game);
        // end draw
        SDL_Delay(16);  // ~60 FPS
        SDL_RenderPresent(game->renderer);
    }
}