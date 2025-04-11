#include "puff.h"


upgrade_t upgrades[UPGRADE_COUNT] = {
    {"Puff renforcé", 10, UPGRADE_TAFF_PER_CLICK, 1.0f, {20, 20, 300, 60}},
    {"Double taff", 50, UPGRADE_TAFF_PER_CLICK, 2.0f, {20, 120, 300, 60}},
    {"Chicha automatique", 500, UPGRADE_AUTO_TAFF, 0.1f, {20, 260, 300, 60}},
    {"Vape bot", 1000, UPGRADE_AUTO_TAFF, 1.0f, {20, 330, 300, 60}},
    {"Puffmaster 3000", 5000, UPGRADE_AUTO_TAFF, 10.0f, {20, 400, 300, 60}},
};


void apply_upgrade(upgrade_t *upgrade, player_t *player) {

    switch (upgrade->type) {
        case UPGRADE_TAFF_PER_CLICK:
            player->taffs += upgrade->value;
            break;
        case UPGRADE_AUTO_TAFF:
            player->taffs_per_second += upgrade->value;
            break;
        case UPGRADE_MULTIPLIER:
            player->taff_multiplier *= upgrade->value;
            break;
    }

}
