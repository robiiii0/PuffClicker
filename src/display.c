#include "puff.h"


void draw_settings_button(SDL_Renderer *renderer, settings_button_t *button, TTF_Font *font) {
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);  // Couleur verte
    SDL_RenderFillRect(renderer, &button->rect);

    // Dessiner le texte du bouton
    SDL_Color textColor = {255, 255, 255, 255};  // Blanc et complètement opaque

    SDL_Surface *textSurface = TTF_RenderText_Solid(font, button->label, textColor);  // Utilisation de button->label
    SDL_Texture *textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    SDL_FreeSurface(textSurface);

    // Positionner le texte au centre du bouton
    int textWidth = 0, textHeight = 0;
    SDL_QueryTexture(textTexture, NULL, NULL, &textWidth, &textHeight);
    SDL_Rect textRect = {button->x + (button->w - textWidth) / 2, button->y + (button->h - textHeight) / 2, textWidth, textHeight};

    SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
    SDL_DestroyTexture(textTexture);
}


void render_text(SDL_Renderer *renderer, TTF_Font *font, const char *text, SDL_Color color, int x, int y)
{
    SDL_Surface *surface = TTF_RenderText_Solid(font, text, color);
    if (!surface) {
        LOG_ERROR("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
        return;
    }

    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (!texture) {
        LOG_ERROR("Unable to create texture from surface! SDL_Error: %s\n", SDL_GetError());
        SDL_FreeSurface(surface);
        return;
    }

    int textW, textH;
    SDL_QueryTexture(texture, NULL, NULL, &textW, &textH);
    SDL_Rect rect = { x, y, textW, textH };

    SDL_RenderCopy(renderer, texture, NULL, &rect);

    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
}

void display_upgrades(game_t *game)
{
    int count = UPGRADE_COUNT;
    SDL_Renderer *renderer = game->renderer;
    TTF_Font *font = game->upgrade_font;

    SDL_Color bgColor = {0, 0, 0, 255};      // gris foncé
    SDL_Color textColor = {255, 255, 255, 255}; // blanc

    for (int i = 0; i < count; i++) {
        // Affiche le fond de la box
        if (game->player->taffs < upgrades[i].cost) {
            bgColor = (SDL_Color){150, 150, 150, 255};  // Trop cher : gris clair
        } else {
            bgColor = (SDL_Color){0, 128, 255, 255};  // Disponible : bleu
        }

        SDL_SetRenderDrawColor(renderer, bgColor.r, bgColor.g, bgColor.b, bgColor.a);
        SDL_RenderFillRect(renderer, &upgrades[i].box);

        // Affiche le nom
        char buffer[64];
        snprintf(buffer, sizeof(buffer), "%s - %d taffs", upgrades[i].name, upgrades[i].cost);

        render_text(renderer, font, buffer, textColor, upgrades[i].box.x + 10, upgrades[i].box.y + 10);

        // Affiche la tooltip
        float mouse_x = game->mouse_pos.x;
        float mouse_y = game->mouse_pos.y;
        if (mouse_x >= upgrades[i].box.x && mouse_x <= upgrades[i].box.x + upgrades[i].box.w &&
            mouse_y >= upgrades[i].box.y && mouse_y <= upgrades[i].box.y + upgrades[i].box.h) {

            // Affiche le fond de la tooltip
            SDL_Rect tooltip_bg = {
                upgrades[i].box.x + upgrades[i].box.w + 10,
                mouse_y,
                400,  // Largeur de la tooltip
                150    // Hauteur de la tooltip
            };

            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderFillRect(renderer, &tooltip_bg);

            char buffer[64];
            snprintf(buffer, sizeof(buffer), "+%.2f taffs/click | Tu as %d", upgrades[i].value, upgrades[i].owned);
            render_text(renderer, font, buffer, (SDL_Color){255,255,255, 255}, upgrades[i].box.x + upgrades[i].box.w + 11, mouse_y);


            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 200);

        }

    }

}


void display_text(game_t *game)
{
    char buffer[50];
    snprintf(buffer, sizeof(buffer), "%.2f taffs", game->player->taffs);
    SDL_Color textColor = {0, 0, 0, 255};

    SDL_Surface* textSurface = TTF_RenderText_Solid(game->font, buffer, textColor);
    if (!textSurface) {
        LOG_ERROR("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
        return;
    }

    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(game->renderer, textSurface);
    if (!textTexture) {
        LOG_ERROR("Unable to create texture from surface! SDL_Error: %s\n", SDL_GetError());
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
    snprintf(buffer, sizeof(buffer), "%.2f taffs/s (* %d)", game->player->taffs_per_second * game->player->taff_multiplier, game->player->taff_multiplier);

    SDL_Surface* surface = TTF_RenderText_Solid(game->font, buffer, textColor);
    if (!surface) {
        LOG_ERROR("Erreur texte taffs/sec: %s\n", TTF_GetError());
        return;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(game->renderer, surface);
    if (!texture) {
        LOG_ERROR("Erreur texture texte taffs/sec: %s\n", SDL_GetError());
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

void render_background(game_t *game) {
    if (game->background != NULL) {
        int screen_width, screen_height;
        SDL_GetRendererOutputSize(game->renderer, &screen_width, &screen_height);

        int bg_width = screen_width / 3;
        int bg_height = screen_height;
        int bg_x = (screen_width - bg_width) / 2;
        int bg_y = 0;

        SDL_Rect dest_rect = { bg_x, bg_y, bg_width, bg_height };

        if (SDL_RenderCopy(game->renderer, game->background->texture, NULL, &dest_rect) != 0) {
            LOG_ERROR("Erreur lors de l'affichage du fond d'écran: %s\n", SDL_GetError());
        }
    } else {
        LOG_ERROR("Erreur : Le fond d'écran n'a pas été chargé correctement.\n");
    }
}





void run_game(game_t *game)
{
    SDL_Event event;
    Uint32 last_tick = SDL_GetTicks(); 
    settings_button_t my_button = {
        300, 250, 200, 50,   // Position et taille du bouton
        {300, 250, 200, 50}, // Initialisation de `rect` à la position et taille
        "Paramètres"         // Texte du bouton
    };
    my_button.rect = (SDL_Rect) {my_button.x, my_button.y, my_button.w, my_button.h}; // Initialisation du rectangle

    float scroll_speed = 2.0f;  // Vitesse de défilement globale
    float delta_time = 0.016f;

    while (!game->quit)
    {
        update_delta_time(game); 
        while (SDL_PollEvent(&event))
            handle_event(event, game);

        Uint32 current_tick = SDL_GetTicks();
        if (current_tick - last_tick >= 1000) {
            game->player->taffs += game->player->taffs_per_second * game->player->taff_multiplier;
            last_tick = current_tick;

            LOG_INFO("Gain passif: %.2f taffs (total: %.2f)\n",
                     game->player->taffs_per_second,
                     game->player->taffs);
        }

        SDL_SetRenderDrawColor(game->renderer, 189, 189, 189, 255);
        SDL_RenderClear(game->renderer);
        render_background(game);



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

        get_mouse_position(game);

        display_upgrades(game);

        // draw_settings_button(game->renderer, &my_button, game->font);
        
        // End draw
        SDL_RenderPresent(game->renderer);
    }
}

