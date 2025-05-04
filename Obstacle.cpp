#include "Obstacle.h"
#include <SDL_image.h>

void Obstacle::init(int x, int y, int w, int h, SDL_Renderer* renderer) {
    rect = {x, y, w, h};
    SDL_Surface* surface = IMG_Load("stone.png");
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
}

void Obstacle::update() {
    rect.y += speed;
}

void Obstacle::render(SDL_Renderer* renderer) {
    SDL_RenderCopy(renderer, texture, NULL, &rect);
}

SDL_Rect Obstacle::getRect() const {
    return rect;
}

void Obstacle::clean() {
    SDL_DestroyTexture(texture);
}

void Obstacle::setSpeed(int s) {
    speed = s;
}
