#pragma once
#include "GameObject.h"
#include "GData.h"
#include <cmath>
#include "Obstacle.h"
#include <SDL2/SDL.h>

class Character : public GameObject {
public:
    Character(int x, int y, int w, int h);
    virtual ~Character() = default;

    void Update(float deltaTime) override;
    void Render(SDL_Renderer* renderer) override;

    void RenderHealthBar(SDL_Renderer* renderer, bool isPlayer);

    bool CheckCollision(const SDL_Rect& otherRect);
    void ApplyDeltaTimeX(float deltaTime);
    void ApplyDeltaTimeY(float deltaTime);
    void RevertMovementX(float deltaTime);
    void RevertMovementY(float deltaTime);

    virtual void TakeDamage(int damage);
    bool IsAlive() const { return m_health > 0; }

    float GetPosX() const { return m_posX; }
    float GetPosY() const { return m_posY; }
    int GetW() const { return m_rect.w; }
    int GetH() const { return m_rect.h; }

    int GetMaxHealth() const { return m_maxHealth; }

protected:
    float m_speed;
    float m_posX;
    float m_posY;
    float m_dirX = 0.0f;
    float m_dirY = 0.0f;

    int m_health;
    int m_maxHealth;

    void Movement(float moveX, float moveY);
    void windowCollision();
    void newPosition();
};