#include "puff.h"


upgrade_t upgrades[UPGRADE_COUNT] = {
    {"Puff renforce", 10, UPGRADE_TAFF_PER_CLICK, 1.0f, {20, 20, 350, 60}, 0},
    {"Double taff", 50, UPGRADE_TAFF_PER_CLICK, 2.0f, {20, 90, 350, 60}, 0},
    {"Chicha automatique", 500, UPGRADE_AUTO_TAFF, 0.1f, {20, 260, 350, 60}, 0},
    {"Vape bot", 1000, UPGRADE_AUTO_TAFF, 1.0f, {20, 330, 350, 60}, 0},
    {"Puffmaster 3000", 5000, UPGRADE_AUTO_TAFF, 10.0f, {20, 400, 350, 60}, 0},
};


void apply_upgrade(upgrade_t *upgrade, player_t *player)
{
    if (player->taffs < upgrade->cost) {
        LOG_INFO("Not enough taffs to buy %s\n", upgrade->name);
        return;
    }
    player->taffs -= upgrade->cost;
    upgrade->owned += 1;
    switch (upgrade->type) {
        case UPGRADE_TAFF_PER_CLICK:
            player->taffs_per_click += upgrade->value;
            break;
        case UPGRADE_AUTO_TAFF:
            player->taffs_per_second += upgrade->value;
            break;
        case UPGRADE_MULTIPLIER:
            player->taff_multiplier *= upgrade->value;
            break;
    }

    LOG_INFO("Upgrade %s applied !\n", upgrade->name);

}
