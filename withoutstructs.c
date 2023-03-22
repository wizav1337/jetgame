#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

int main(int argc, char* argv[]) {
    // Initialize SDL and the image subsystem
    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_PNG);

    // Create a window and renderer
    SDL_Window* window = SDL_CreateWindow("SDL App", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    // Load the PNG image
    SDL_Surface* imageSurface = IMG_Load("image.png");
    if (!imageSurface) {
        printf("Error loading image: %s\n", IMG_GetError());
        return 1;
    }

    // Create a texture from the image surface
    SDL_Texture* imageTexture = SDL_CreateTextureFromSurface(renderer, imageSurface);
    SDL_FreeSurface(imageSurface);

    // Set the rect to the size of the image
    SDL_Rect imageRect = { 0, 0, 0, 0 };
    SDL_QueryTexture(imageTexture, NULL, NULL, &imageRect.w, &imageRect.h);

    // Set the position of the rect
    imageRect.x = (640 - imageRect.w) / 2;
    imageRect.y = (480 - imageRect.h) / 2;

    // Clear the renderer
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // Draw the image texture to the renderer
    SDL_RenderCopy(renderer, imageTexture, NULL, &imageRect);

    // Render the changes to the screen
    SDL_RenderPresent(renderer);

    // Wait for the user to close the window
    SDL_Event event;
    while (1) {
        if (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                break;
            }
        }
    }

    // Clean up resources and quit SDL
    SDL_DestroyTexture(imageTexture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();
    return 0;
}
