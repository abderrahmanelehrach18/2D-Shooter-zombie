#pragma once
#include <SDL2/SDL.h>
#include <vector>

using namespace std;

struct Obstacle {
    SDL_Rect rect;
    Obstacle(int x, int y, int w, int h) : rect({ x, y, w, h }) {}

    const SDL_Rect& GetRect() const { return rect; }
};