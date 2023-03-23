
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdlib.h>
#include <time.h>
#include <SDL2/SDL_mixer.h>


typedef struct {

    int x;
    int y;
    SDL_Surface* image;
    SDL_Rect weapon_rect;
    SDL_Texture* weapon_texture;
    int damage;
    int range;
    int speed;
    int ammo;
    int reload_time;
    Mix_Chunk* fire_sound;
    Mix_Chunk* reload_sound;
}Weapon;

Weapon* createWeaponSprite(SDL_Renderer* weapon_renderer, const char* weaponimagePath, int x, int y, int damage, int speed, int range, int ammo, int reload_time);
void draw_Weapon(SDL_Renderer* weapon_renderer, Weapon* weapon);
void destroyWeapon(Weapon* weapon);