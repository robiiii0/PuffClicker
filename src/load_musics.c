#include "puff.h"

music_t *load_music() {
    music_t *music = malloc(sizeof(music_t));
    if (!music) return NULL;

    music->menu = Mix_LoadMUS("assets/menu.ogg");
    music->gameplay = Mix_LoadMUS("assets/gameplay.ogg");
    music->victory = Mix_LoadMUS("assets/victory.ogg");
    music->defeat = Mix_LoadMUS("assets/defeat.ogg");

    if (!music->menu || !music->gameplay || !music->victory || !music->defeat) {
        printf("Erreur chargement musique : %s\n", Mix_GetError());
        // Tu peux gérer ça proprement ici
        free(music);
        return NULL;
    }

    return music;
}
