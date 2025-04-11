#include "puff.h"


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
        // end draw
        SDL_Delay(16);  // ~60 FPS
        SDL_RenderPresent(game->renderer);
    }
}