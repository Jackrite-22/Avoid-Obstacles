#ifndef PLAYER_H
#define PLAYER_H

#include <SDL.h>

class Player {
public:
    void init(int x, int y, int w, int h, SDL_Renderer* renderer);
    void handleInput(const Uint8* keystates);
    void render(SDL_Renderer* renderer);
    SDL_Rect getRect() const;
    void clean();

private:
    SDL_Rect rect;
    int speed = 5;
    SDL_Texture* texture;
};

#endif
