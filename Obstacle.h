#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <SDL.h>

class Obstacle {
public:
    void init(int x, int y, int w, int h, SDL_Renderer* renderer);
    void update();
    void render(SDL_Renderer* renderer);
    SDL_Rect getRect() const;
    void clean();
    void setSpeed(int s);

private:
    SDL_Rect rect;
    int speed = 4;
    SDL_Texture* texture;
};

#endif
