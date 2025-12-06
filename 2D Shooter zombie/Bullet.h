#pragma once
#include "GameObject.h"
#include "GData.h"
#include <SDL2/SDL.h>

class Bullet : public GameObject {
public:
    Bullet(float startX, float startY, float dirX, float dirY, int size, float speed);

    void Update(float deltaTime) override;
    void Render(SDL_Renderer* renderer) override;

    bool IsOffScreen() const;

    const SDL_Rect& GetRect() const { return m_rect; }

    bool CheckCollision(const SDL_Rect& otherRect) const;

protected:
    float m_posX;
    float m_posY;
    float m_dirX;
    float m_dirY;
    float m_speed;

    void newPosition();
};