#include "Player.h"
#include "Game.h"

extern Game* g_game;

Player::Player(int x, int y, int w, int h) : Character(x, y, w, h)
{
    m_health = 10;
    m_maxHealth = 10;
}

void Player::Update(float deltaTime) {
    if (m_isInvulnerable) {
        m_invulnerabilityTimer -= deltaTime;
        if (m_invulnerabilityTimer <= 0.0f) {
            m_isInvulnerable = false;
        }
    }

    if (m_dirX != 0.0f || m_dirY != 0.0f) {
        if (m_dirX != 0.0f) {
            m_lastDirX = m_dirX;
        }

        m_animTimer += deltaTime;
        if (m_animTimer >= FRAME_DURATION) {
            m_currentFrame = (m_currentFrame + 1) % FRAME_COUNT;
            m_animTimer -= FRAME_DURATION;
        }
    }
    else {
        m_currentFrame = 0;
        m_animTimer = 0.0f;
    }

    Character::Update(deltaTime);
}

void Player::StartInvulnerability() {
    if (!m_isInvulnerable) {
        m_isInvulnerable = true;
        m_invulnerabilityTimer = INVULNERABILITY_DURATION;
    }
}

void Player::HandleInput(const Uint8* state) {
    float moveX = 0.0f;
    float moveY = 0.0f;

    if (state[SDL_SCANCODE_W]) {
        moveY -= 1.0f;
    }
    if (state[SDL_SCANCODE_S]) {
        moveY += 1.0f;
    }
    if (state[SDL_SCANCODE_A]) {
        moveX -= 1.0f;
    }
    if (state[SDL_SCANCODE_D]) {
        moveX += 1.0f;
    }

    this->Movement(moveX, moveY);
}

void Player::Render(SDL_Renderer* renderer) {
    if (m_health <= 0) return;

    int mouseX = 0, mouseY = 0;
    SDL_Texture* playerTexture = nullptr;
    if (g_game) {
        mouseX = g_game->GetMouseX();
        mouseY = g_game->GetMouseY();
        playerTexture = g_game->GetPlayerTexture();
    }

    if (playerTexture) {
        const int srcX = WALK_COLUMN_X;
        const int srcY = m_currentFrame * (SPRITE_H + 4);
        SDL_Rect srcRect = { srcX, srcY, SPRITE_W, SPRITE_H };

        float pCenterX = m_posX + m_rect.w / 2.0f;
        float pCenterY = m_posY + m_rect.h / 2.0f;

        float deltaX = (float)mouseX - pCenterX;
        float deltaY = (float)mouseY - pCenterY;

        float angleRad = std::atan2(deltaY, deltaX);
        float angleDeg = angleRad * (180.0f / 3.14159265359f);

        if (m_isInvulnerable) {
            int blinkState = (int)(m_invulnerabilityTimer * 10.0f) % 2;
            if (blinkState == 0) {
                goto fallback_render;
            }
        }

        SDL_RenderCopyEx(renderer,
            playerTexture,
            &srcRect,
            &m_rect,
            angleDeg,
            NULL,
            SDL_FLIP_NONE);

        RenderHealthBar(renderer, true);
    }
    else {
    fallback_render:
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
        SDL_RenderFillRect(renderer, &this->m_rect);
    }
}