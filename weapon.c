#include "weapon.h"

Weapon *createWeaponSprite(SDL_Renderer *weapon_renderer, const char *weaponimagePath, int x, int y, int damage, int speed, int range, int ammo, int reload_time){
    Weapon* weapon = malloc(sizeof(Weapon));
    if (!weapon){
        printf("Error allocating memory for the asset\n");
    }
    SDL_Surface* weaponImageSurface = IMG_Load(weaponimagePath);
    if (!weaponimagePath) {
        printf("Error loading image: %S\n", IMG_GetError());
    }
    weapon->weapon_texture = SDL_CreateTextureFromSurface(weapon_renderer, weaponImageSurface);
    SDL_FreeSurface(weaponImageSurface);
    if (!weapon->weapon_texture) {
        printf("Error creating texture: %s\n", SDL_GetError());
        free(weapon);
        return NULL;
    }

    SDL_QueryTexture(weapon->weapon_texture, NULL, NULL, &weapon->weapon_rect.w, &weapon->weapon_rect.h);
    weapon->weapon_rect.x = x;
    weapon->weapon_rect.y = y;
    weapon->speed = speed;
    weapon->damage = damage;
    weapon->ammo = ammo;
    weapon->range = range;
    weapon->reload_time = reload_time;

    return weapon;
}

void draw_Weapon(SDL_Renderer* weapon_renderer, Weapon* weapon)
{
    SDL_RenderCopy(weapon_renderer, weapon->weapon_texture, NULL, &weapon->weapon_rect);
}


void destroyWeapon(Weapon *weapon){
    SDL_DestroyTexture(weapon->weapon_texture);
    free(weapon);
}

