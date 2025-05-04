#include "Game.h"
#include <SDL_image.h>
#include <cstdlib>
#include <ctime>

Game::Game() {
    window = nullptr;
    renderer = nullptr;
    isRunning = false;
    numStones = 0;
    lastSpawnTime = 0;
}

Game::~Game() {}

bool Game::init(const char* title, int width, int height) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        return false;
    }

    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        return false;
    }

    window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);
    if (!window) return false;

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) return false;

    SDL_Surface* backgroundSurface = IMG_Load("forest.jpg");
    if (!backgroundSurface) {
        return false;
    }

    backgroundTexture = SDL_CreateTextureFromSurface(renderer, backgroundSurface);
    SDL_FreeSurface(backgroundSurface);

    srand(static_cast<unsigned int>(time(nullptr)));

    player.init(375, 500, 50, 50, renderer);
    isRunning = true;
    return true;
}
void Game::run() {
    while (isRunning) {
        handleEvents();
        update();
        render();
        SDL_Delay(16);
    }
}
void Game::handleEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            isRunning = false;
        }
    }
    const Uint8* keystates = SDL_GetKeyboardState(nullptr);
    player.handleInput(keystates);
}
void Game::update() {

    int currentTime = SDL_GetTicks();

    if (currentTime - lastSpawnTime >= Spawn && numStones < maxStones) {

        int x = rand() % (800 - 50);

        obstacles[numStones].init(x, 0, 50, 50, renderer);

        obstacles[numStones].setSpeed(stoneSpeed);

        numStones++;

        lastSpawnTime = currentTime;
    }


    for (int i = 0; i < numStones; i++) {
        obstacles[i].update();
    }


    checkCollisions();
}


void Game::render() {

    SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL);


    player.render(renderer);


    for (int i = 0; i < numStones; ++i) {
        obstacles[i].render(renderer);
    }

    SDL_RenderPresent(renderer);
}

void Game::checkCollisions() {
    SDL_Rect playerRect = player.getRect();
    for (int i = 0; i < numStones; ++i) {
        SDL_Rect stoneRect = obstacles[i].getRect();
        if (SDL_HasIntersection(&playerRect, &stoneRect)) {
            isRunning = false;
        }
    }
}

void Game::clean() {
    player.clean();
    for (int i = 0; i < numStones; ++i) {
        obstacles[i].clean();
    }

    SDL_DestroyTexture(backgroundTexture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();
}


