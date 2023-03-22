#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdlib.h>
#include <stdbool.h>
#include "sprite.h"
#include "ground_assets.h"

// Constants and global variables
int buffer_zone = 50;
int identical_asset_number = 6;
const int desired_fps = 120;
const int frame_delay = 5000 / desired_fps;
Uint32 frame_start;
int frame_time;

// Jet Constants and global variables

const int JET_SPEED = 5;
const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 880;

// Function to spawn assets at random positions
void spawn(GroundAssets *asset) {
    asset->asset_rect.x = buffer_zone + rand() % (640 - 2 * buffer_zone);
    asset->asset_rect.y = -50 - rand() % 880; 
}

int main(int argc, char* argv[]) {
    srand(time(NULL));

    // Initialize SDL and the image subsystem
    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_PNG);

    // Create a window and renderer
    SDL_Window* window = SDL_CreateWindow("Jet Figher", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 880, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    // Load and configure background
    SDL_Surface* backgroundSurface = IMG_Load("water.png");
    if (!backgroundSurface) {
        printf("Error loading background image: %s\n", IMG_GetError());
    }
    SDL_Texture* backgroundTexture = SDL_CreateTextureFromSurface(renderer, backgroundSurface);
    SDL_FreeSurface(backgroundSurface);
    if (!backgroundTexture) {
        printf("Error creating background texture: %s\n", SDL_GetError());
    }
    SDL_Rect backgroundRect;
    backgroundRect.x = 0;
    backgroundRect.y = 0;
    backgroundRect.w = 640; 
    backgroundRect.h = 880; 

    // Create jet sprite
    Sprite* sprite1 = createSprite(renderer, "jet.png", 250, 700, "jet");

    // Create and spawn assets
    GroundAssets* assets[identical_asset_number];
    for (int i = 0; i < identical_asset_number; i++) {
        assets[i] = createAssetSprite(renderer, "enemy.png", 170, 170, "spritex%d", 50);
        spawn(assets[i]);
    }

    // Initialize main loop
    bool running = true;
    SDL_Event event;
    while (running) {
        // Handle timing
        frame_start = SDL_GetTicks();

        // Clear the renderer
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // Jet movement

        const Uint8 *keystate = SDL_GetKeyboardState(NULL);
    if (keystate[SDL_SCANCODE_W] || keystate[SDL_SCANCODE_UP]) {
        sprite1->rect.y -= JET_SPEED;
        if (sprite1->rect.y < 0) {
            sprite1->rect.y = 0;
        }
    }
    if (keystate[SDL_SCANCODE_A] || keystate[SDL_SCANCODE_LEFT]) {
        sprite1->rect.x -= JET_SPEED;
        if (sprite1->rect.x < 0) {
            sprite1->rect.x = 0;
        }
    }
    if (keystate[SDL_SCANCODE_S] || keystate[SDL_SCANCODE_DOWN]) {
        sprite1->rect.y += JET_SPEED;
        if (sprite1->rect.y > WINDOW_HEIGHT - sprite1->rect.h) {
            sprite1->rect.y = WINDOW_HEIGHT - sprite1->rect.h;
        }
    }
    if (keystate[SDL_SCANCODE_D] || keystate[SDL_SCANCODE_RIGHT]) {
        sprite1->rect.x += JET_SPEED;
        if (sprite1->rect.x > WINDOW_WIDTH - sprite1->rect.w) {
            sprite1->rect.x = WINDOW_WIDTH - sprite1->rect.w;
        }
    }

        // Render background
        SDL_RenderCopy(renderer, backgroundTexture, NULL, &backgroundRect);

        // Draw a Jet

        drawSprite(renderer, sprite1);

        // Move and render assets
        for (int i = 0; i < identical_asset_number; i++) {
            Uint32 current_time = SDL_GetTicks();
            Uint32 elapsed_time = current_time - assets[i]->last_update;
            assets[i]->asset_rect.y += assets[i]->speed * elapsed_time / 1000.0;

            // Reset position of assets that have gone off the screen
            if (assets[i]->asset_rect.y > 880) {
                spawn(assets[i]);
            }

            drawSprite(renderer, sprite1);
            drawAssets(renderer, assets[i]);
            assets[i]->last_update = current_time;
        }


        // Present rendered frame
        SDL_RenderPresent(renderer);

        // Limit frame rate
            frame_time = SDL_GetTicks() - frame_start;
        if (frame_time < frame_delay) {
            SDL_Delay(frame_delay - frame_time);
        }

        // Check for quit event
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }
    }

    // Clean up resources
    for (int i = 0; i < identical_asset_number; i++) {
        destroyAssets(assets[i]);
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyTexture(backgroundTexture);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();

    return 0;
}

