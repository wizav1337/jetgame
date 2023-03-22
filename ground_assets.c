#include "ground_assets.h"

GroundAssets* createAssetSprite(SDL_Renderer *asset_renderer, const char *assetimagePath, int x, int y, const char *name, int speed){
    GroundAssets* assets = malloc(sizeof(GroundAssets));
    if (!assets) {
        printf("Error allocating memory fo the asset\n");
        return NULL;
    }
    SDL_Surface* assetImageSurface = IMG_Load(assetimagePath);
    if (!assetimagePath) {
        printf("Error loading image: %S\n", IMG_GetError());
        free(assets);
        return NULL;
    }
    assets->asset_texture = SDL_CreateTextureFromSurface(asset_renderer, assetImageSurface);
    SDL_FreeSurface(assetImageSurface);
    if (!assets->asset_texture) {
        printf("Error creating texture: %s\n", SDL_GetError());
        free(assets);
        return NULL;
    }

    SDL_QueryTexture(assets->asset_texture, NULL, NULL, &assets->asset_rect.w, &assets->asset_rect.h);
    assets->asset_rect.x = x;
    assets->asset_rect.y = y;
    assets->last_update = SDL_GetTicks();
    assets->speed = speed;
    return assets;

}

void drawAssets(SDL_Renderer* asset_renderer, GroundAssets *assets){
 
 
 SDL_RenderCopy(asset_renderer, assets->asset_texture, NULL, &assets->asset_rect);

}

void destroyAssets(GroundAssets *assets){
    SDL_DestroyTexture(assets->asset_texture);
    free(assets);

}
