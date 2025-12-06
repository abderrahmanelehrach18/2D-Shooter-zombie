#include "Explosion.h"
#include <iostream>

Explosion::Explosion(float x, float y, int w, int h)
{
    m_rect.w = FRAME_WIDTH * SCALE_FACTOR;
    m_rect.h = FRAME_HEIGHT * SCALE_FACTOR;

    m_rect.x = (int)(x - m_rect.w / 2.0f);
    m_rect.y = (int)(y - m_rect.h / 2.0f);

    m_isFinished = false;
    m_animTimer = 0.0f;
    m_currentFrame = 0;
}

void Explosion::Update(float deltaTime) {
    if (m_isFinished) return;

    m_animTimer += deltaTime;

    if (m_animTimer >= FRAME_DURATION) {
        m_animTimer -= FRAME_DURATION;
        m_currentFrame++;

        if (m_currentFrame >= FRAME_COUNT) {
            m_isFinished = true;
            m_currentFrame = FRAME_COUNT - 1;
        }
    }
}

void Explosion::Render(SDL_Renderer* renderer, SDL_Texture* texture) {
    if (m_isFinished || texture == nullptr) return;

    SDL_Rect srcRect = {
        m_currentFrame * FRAME_WIDTH,
        0,
        FRAME_WIDTH,
        FRAME_HEIGHT
    };

    SDL_RenderCopy(renderer, texture, &srcRect, &m_rect);
}

void Explosion::Render(SDL_Renderer* renderer)
{
}