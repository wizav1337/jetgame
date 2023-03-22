
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdlib.h>
#include <time.h>



typedef struct {

    SDL_Texture* asset_texture;
    SDL_Rect asset_rect;
    const char name;
    int speed;
    Uint32 last_update;
} GroundAssets;

GroundAssets* createAssetSprite(SDL_Renderer* asset_renderer, const char* assetimagePath, int x, int y, const char* name, int speed);
void drawAssets(SDL_Renderer* asset_renderer, GroundAssets* assets);
void destroyAssets(GroundAssets* assets);

