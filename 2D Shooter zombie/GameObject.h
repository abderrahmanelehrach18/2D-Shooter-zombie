#pragma once
#include <sdl2/SDL.h>
#include "Obstacle.h"

class GameObject {
public:
    virtual ~GameObject() = default;

    virtual void Update(float deltaTime) = 0;
    virtual void Render(SDL_Renderer* renderer) = 0;
    SDL_Rect getRect() { return this->m_rect; };

protected:
    SDL_Rect m_rect;
};