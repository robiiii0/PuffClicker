#include "puff.h"
#include <SDL_image.h>

#include "puff.h"
#include <SDL_image.h>

void load_parallax_layers(SDL_Renderer* renderer, game_t *game) {
    // Chargement des textures pour chaque jeu de parallax (parallax_init[0], parallax_init[1], parallax_init[2])
    for (int i = 0; i < PARALLAX_NUMBERS; i++) {
        // Chargement des textures
        game->parallax_init[i].parallax_layers[0].texture = IMG_LoadTexture(renderer, "assets/paralax/craftpix-891123-free-pixel-art-street-2d-backgrounds/PNG/City2/Bright/Sky.png");
        game->parallax_init[i].parallax_layers[1].texture = IMG_LoadTexture(renderer, "assets/paralax/craftpix-891123-free-pixel-art-street-2d-backgrounds/PNG/City2/Bright/houses3.png");
        game->parallax_init[i].parallax_layers[2].texture = IMG_LoadTexture(renderer, "assets/paralax/craftpix-891123-free-pixel-art-street-2d-backgrounds/PNG/City2/Bright/houses1.png");
        game->parallax_init[i].parallax_layers[3].texture = IMG_LoadTexture(renderer, "assets/paralax/craftpix-891123-free-pixel-art-street-2d-backgrounds/PNG/City2/Bright/back.png");
        game->parallax_init[i].parallax_layers[4].texture = IMG_LoadTexture(renderer, "assets/paralax/craftpix-891123-free-pixel-art-street-2d-backgrounds/PNG/City2/Bright/minishop&callbox.png");
        game->parallax_init[i].parallax_layers[5].texture = IMG_LoadTexture(renderer, "assets/paralax/craftpix-891123-free-pixel-art-street-2d-backgrounds/PNG/City2/Bright/road&lamps.png");

        // Vérification du chargement des textures
        for (int j = 0; j < PARALLAX_LAYER_COUNT; j++) {
            if (game->parallax_init[i].parallax_layers[j].texture == NULL) {
                printf("Erreur : Texture %d non chargée pour parallax_init[%d]\n", j, i);
            } else {
                printf("Texture %d chargée avec succès pour parallax_init[%d]: %s\n", j, i, SDL_GetError());
            }
        }
    }

    // Obtention de la taille de l'écran
    int screen_width, screen_height;
    SDL_GetRendererOutputSize(renderer, &screen_width, &screen_height);
    printf("Taille de l'écran: %d x %d\n", screen_width, screen_height);

    // Initialisation des propriétés des couches de parallax
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < PARALLAX_LAYER_COUNT; j++) {
            // Obtenir les dimensions des textures
            SDL_QueryTexture(game->parallax_init[i].parallax_layers[j].texture, NULL, NULL, 
                             &game->parallax_init[i].parallax_layers[j].src_rect.w, 
                             &game->parallax_init[i].parallax_layers[j].src_rect.h);

            // Adapter la taille de la destination à la taille de l'écran
            game->parallax_init[i].parallax_layers[j].dest_rect.w = screen_width;
            game->parallax_init[i].parallax_layers[j].dest_rect.h = screen_height;

            // Définir la position horizontale des couches (parallax)
            if (i == 0) {
                game->parallax_init[i].parallax_layers[j].x = 0.0f;  // Première couche à x = 0
            } else if (i == 1) {
                game->parallax_init[i].parallax_layers[j].x = screen_width / 2 ;  // Deuxième couche à x = screen_width
            } else if (i == 2) {
                game->parallax_init[i].parallax_layers[j].x = screen_width;  // Troisième couche à x = 2 * screen_width
            }
        }

        // Vitesse de défilement pour chaque jeu de parallax
        game->parallax_init[i].parallax_layers[0].speed = 230.0f;  // Exemple de vitesse pour chaque couche
        game->parallax_init[i].parallax_layers[1].speed = 250.0f;
        game->parallax_init[i].parallax_layers[2].speed = 270.0f;
    }
}




void update_parallax(game_t *game, float delta_time) {
    int screen_width, screen_height;
    SDL_GetRendererOutputSize(game->renderer, &screen_width, &screen_height); // Use game->renderer
    for (int i = 0; i < PARALLAX_NUMBERS; i++) {
        for (int j = 0; j < PARALLAX_LAYER_COUNT; j++) {
            // Mise à jour de la position horizontale de chaque couche
            game->parallax_init[i].parallax_layers[j].x -= game->parallax_init[i].parallax_layers[j].speed * delta_time;

            // Si la position de la couche dépasse sa propre largeur, on la réinitialise
            if (game->parallax_init[i].parallax_layers[j].x < -game->parallax_init[i].parallax_layers[j].src_rect.w) {
                game->parallax_init[i].parallax_layers[j].x = screen_width;
            }
        }
    }
}




void render_parallax(game_t *game) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < PARALLAX_LAYER_COUNT; j++) {
            parallax_layer_t *layer = &game->parallax_init[i].parallax_layers[j];

            if (layer->texture == NULL) {
                printf("Erreur : Texture de la couche %d, parallax_init[%d] est NULL\n", j, i);
                continue;
            }

            layer->dest_rect.x = (int)layer->x;

            // Rendu de la texture sur l'écran
            SDL_RenderCopy(game->renderer, layer->texture, &layer->src_rect, &layer->dest_rect);
        }
    }
}


