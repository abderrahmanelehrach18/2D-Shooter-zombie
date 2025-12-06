#include "Character.h"
#include <cmath>
#include <iostream>

Character::Character(int x, int y, int w, int h)
    : m_speed(300.0f),
    m_posX((float)x),
    m_posY((float)y),
    m_health(1),
    m_maxHealth(1)
{
    m_rect.x = x;
    m_rect.y = y;
    m_rect.w = w;
    m_rect.h = h;
}

void Character::TakeDamage(int damage) {
    m_health -= damage;
    if (m_health < 0) {
        m_health = 0;
    }
}

void Character::RenderHealthBar(SDL_Renderer* renderer, bool isPlayer) {
    if (m_health <= 0) return;

    if (!isPlayer && m_health == m_maxHealth) return;

    const int BAR_WIDTH = m_rect.w;
    const int BAR_HEIGHT = 5;
    const int BAR_Y_OFFSET = 10;

    int barX = m_rect.x;
    int barY = m_rect.y - BAR_HEIGHT - BAR_Y_OFFSET;

    float healthRatio = (float)m_health / m_maxHealth;

    if (healthRatio < 0.0f) healthRatio = 0.0f;
    if (healthRatio > 1.0f) healthRatio = 1.0f;

    SDL_Rect bgRect = { barX, barY, BAR_WIDTH, BAR_HEIGHT };

    SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255);
    SDL_RenderFillRect(renderer, &bgRect);

    int healthBarFillWidth = (int)(BAR_WIDTH * healthRatio);
    SDL_Rect fillRect = { barX, barY, healthBarFillWidth, BAR_HEIGHT };

    if (healthRatio > 0.6f) {
        SDL_SetRenderDrawColor(renderer, 0, 200, 0, 255);
    }
    else if (healthRatio > 0.3f) {
        SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
    }
    else {
        SDL_SetRenderDrawColor(renderer, 200, 0, 0, 255);
    }

    SDL_RenderFillRect(renderer, &fillRect);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderDrawRect(renderer, &bgRect);
}


void Character::Update(float deltaTime) {
    this->windowCollision();
    this->newPosition();
}

void Character::Render(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderFillRect(renderer, &this->m_rect);
}

void Character::ApplyDeltaTimeX(float deltaTime) {
    this->m_posX += this->m_dirX * this->m_speed * deltaTime;
}

void Character::ApplyDeltaTimeY(float deltaTime) {
    this->m_posY += this->m_dirY * this->m_speed * deltaTime;
}

void Character::RevertMovementX(float deltaTime) {
    this->m_posX -= this->m_dirX * this->m_speed * deltaTime;
}

void Character::RevertMovementY(float deltaTime) {
    this->m_posY -= this->m_dirY * this->m_speed * deltaTime;
}

void Character::windowCollision() {
    if (this->m_posX < 0) {
        this->m_posX = 0;
    }
    if (this->m_posX + m_rect.w > GData::WINDOW_WIDTH) {
        this->m_posX = (float)GData::WINDOW_WIDTH - m_rect.w;
    }

    if (this->m_posY < 0) {
        this->m_posY = 0;
    }
    if (this->m_posY + m_rect.h > GData::WINDOW_HEIGHT) {
        this->m_posY = (float)GData::WINDOW_HEIGHT - m_rect.h;
    }
}

void Character::newPosition() {
    this->m_rect.x = (int)this->m_posX;
    this->m_rect.y = (int)this->m_posY;
}

void Character::Movement(float moveX, float moveY)
{
    float length = std::sqrt(moveX * moveX + moveY * moveY);

    if (length > 0) {
        this->m_dirX = moveX / length;
        this->m_dirY = moveY / length;
    }
    else {
        this->m_dirX = 0.0f;
        this->m_dirY = 0.0f;
    }
}

bool Character::CheckCollision(const SDL_Rect& otherRect) {
    bool xOverlap = (m_posX + m_rect.w > otherRect.x) && (m_posX < otherRect.x + otherRect.w);
    bool yOverlap = (m_posY + m_rect.h > otherRect.y) && (m_posY < otherRect.y + otherRect.h);

    return xOverlap && yOverlap;
}