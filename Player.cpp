#include "Player.h"
#include <SDL_image.h>

void Player::init(int x, int y, int w, int h, SDL_Renderer* renderer) {
    rect = {x, y, w, h};
    SDL_Surface* surface = IMG_Load("pngegg.png");
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
}

void Player::handleInput(const Uint8* keystates) {
    if (keystates[SDL_SCANCODE_UP]) {
        if (rect.y > 0) {
            rect.y -= speed;
        }
    }

    if (keystates[SDL_SCANCODE_DOWN]) {
        if (rect.y + rect.h < 600) {
            rect.y += speed;
        }
    }

    if (keystates[SDL_SCANCODE_LEFT]) {
        if (rect.x > 0) {
            rect.x -= speed;
        }
    }

    if (keystates[SDL_SCANCODE_RIGHT]) {
        if (rect.x + rect.w < 800) {
            rect.x += speed;
        }
    }
}


void Player::render(SDL_Renderer* renderer) {
    SDL_RenderCopy(renderer, texture, NULL, &rect);
}

SDL_Rect Player::getRect() const {
    return rect;
}

void Player::clean() {
    SDL_DestroyTexture(texture);
}

