#include "sprite.h"

Sprite* createSprite(SDL_Renderer* renderer, const char* imagePath, int x, int y, const char* name) {
    Sprite* sprite = malloc(sizeof(Sprite));
    sprite->name = name;
    if (!sprite) {
        printf("Error allocating memory for sprite\n");
        return NULL;
    }
    SDL_Surface* imageSurface = IMG_Load(imagePath);
    if (!imageSurface) {
        printf("Error loading image: %s\n", IMG_GetError());
        free(sprite);
        return NULL;
    }
    sprite->texture = SDL_CreateTextureFromSurface(renderer, imageSurface);
    SDL_FreeSurface(imageSurface);
    if (!sprite->texture) {
        printf("Error creating texture: %s\n", SDL_GetError());
        free(sprite);
        return NULL;
    }
    SDL_QueryTexture(sprite->texture, NULL, NULL, &sprite->rect.w, &sprite->rect.h);
    sprite->rect.x = x;
    sprite->rect.y = y;
    return sprite;
}

void drawSprite(SDL_Renderer* renderer, Sprite* sprite) {

if (strcmp(sprite->name, "sprite1") == 0) {
        sprite->rect.w *= 2;
        sprite->rect.h *= 2;
    }

if (strcmp(sprite->name, "sprite3") == 0) {
        sprite->rect.w *= 4;
        sprite->rect.h *= 4;
    }

    SDL_RenderCopy(renderer, sprite->texture, NULL, &sprite->rect);
}

void destroySprite(Sprite* sprite) {
    SDL_DestroyTexture(sprite->texture);
    free(sprite);
}
