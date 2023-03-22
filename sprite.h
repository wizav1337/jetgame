
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdlib.h>

typedef struct {
    SDL_Texture* texture;
    SDL_Rect rect;
    const char* name;
} Sprite;

Sprite* createSprite(SDL_Renderer* renderer, const char* imagePath, int x, int y, const char* name);
void drawSprite(SDL_Renderer* renderer, Sprite* sprite);
void destroySprite(Sprite* sprite);
