#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include "Player.h"
#include "Obstacle.h"

const int maxStones = 10000;
const int Spawn = 300;
const int stoneSpeed = 10;

class Game {
public:
    Game();
    ~Game();
    bool init(const char* title, int width, int height);
    void run();
    void clean();

private:
    void handleEvents();
    void update();
    void render();
    void checkCollisions();

    SDL_Texture* backgroundTexture;
    SDL_Window* window;
    SDL_Renderer* renderer;
    bool isRunning;
    Player player;
    Obstacle obstacles[maxStones];
    int numStones;
    int lastSpawnTime;
};

#endif
