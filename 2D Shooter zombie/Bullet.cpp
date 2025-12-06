#include "Bullet.h"

Bullet::Bullet(float startX, float startY, float dirX, float dirY, int size, float speed)
    : m_posX(startX), m_posY(startY), m_dirX(dirX), m_dirY(dirY), m_speed(speed)
{
    m_rect.x = (int)startX;
    m_rect.y = (int)startY;
    m_rect.w = size;
    m_rect.h = size;
}

void Bullet::Update(float deltaTime) {
    m_posX += m_dirX * m_speed * deltaTime;
    m_posY += m_dirY * m_speed * deltaTime;
    newPosition();
}

void Bullet::Render(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
    SDL_RenderFillRect(renderer, &m_rect);
}

void Bullet::newPosition() {
    m_rect.x = (int)m_posX;
    m_rect.y = (int)m_posY;
}

bool Bullet::IsOffScreen() const {
    return m_posX < 0 || m_posX > GData::WINDOW_WIDTH ||
        m_posY < 0 || m_posY > GData::WINDOW_HEIGHT;
}

bool Bullet::CheckCollision(const SDL_Rect& otherRect) const {
    if (m_rect.x + m_rect.w <= otherRect.x || m_rect.x >= otherRect.x + otherRect.w) {
        return false;
    }
    if (m_rect.y + m_rect.h <= otherRect.y || m_rect.y >= otherRect.y + otherRect.h) {
        return false;
    }
    return true;
}