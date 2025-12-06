#include "Zombie.h"
#include <vector>
#include <iostream>
#include <cmath>

using std::vector;

const int FRAME_WIDTH = 21;
const int FRAME_HEIGHT = 22;
const int MOVE_FRAME_COUNT = 5;
const float MOVE_SPEED = 0.12f;

Zombie::Zombie(int x, int y, int w, int h, float speed) : Character(x, y, w, h)
{
    m_speed = speed;
    m_health = 5;
    m_maxHealth = 5;
    m_state = Z_MOVING;
    m_animTimer = 0.0f;
    m_currentFrame = 0;
}

void Zombie::TakeDamage(int damage)
{
    m_health -= damage;
    if (m_health <= 0) {
        m_health = 0;
        zombiesKilled++;
    }
}

void Zombie::Update(float deltaTime, const Player& player, const vector<Obstacle>& walls)
{
    m_animTimer += deltaTime;

    if (m_state == Z_MOVING) {
        AIsearch(player, walls);

        this->ApplyDeltaTimeX(deltaTime);
        for (const auto& wall : walls) {
            if (this->CheckCollision(wall.rect)) {
                this->RevertMovementX(deltaTime);
                break;
            }
        }

        this->ApplyDeltaTimeY(deltaTime);
        for (const auto& wall : walls) {
            if (this->CheckCollision(wall.rect)) {
                this->RevertMovementY(deltaTime);
                break;
            }
        }
    }

    if (m_animTimer >= MOVE_SPEED) {
        m_currentFrame = (m_currentFrame + 1) % MOVE_FRAME_COUNT;
        m_animTimer = 0.0f;
    }

    this->windowCollision();
    this->newPosition();
}

void Zombie::Render(SDL_Renderer* renderer, SDL_Texture* idleTex, SDL_Texture* deathTex)
{
    SDL_Texture* currentTex = idleTex;

    if (currentTex) {
        SDL_Rect srcRect = {
            m_currentFrame * FRAME_WIDTH,
            0,
            FRAME_WIDTH,
            FRAME_HEIGHT
        };

        SDL_RendererFlip flip = SDL_FLIP_NONE;
        if (m_dirX > 0) {
            flip = SDL_FLIP_HORIZONTAL;
        }
        else if (m_dirX < 0) {
            flip = SDL_FLIP_NONE;
        }

        SDL_RenderCopyEx(renderer, currentTex, &srcRect, &m_rect, 0.0, NULL, flip);
    }
    else {
        SDL_SetRenderDrawColor(renderer, 0, 150, 0, 255);
        SDL_RenderFillRect(renderer, &this->m_rect);
    }

    RenderHealthBar(renderer, false);
}

void Zombie::AIsearch(const Player& player, const vector<Obstacle>& walls)
{
    float targetX = player.GetPosX() + player.GetW() * 0.5f;
    float targetY = player.GetPosY() + player.GetH() * 0.5f;

    if (!this->IsPathBlocked(targetX, targetY, walls)) {
        float moveX = targetX - m_posX;
        float moveY = targetY - m_posY;
        this->Movement(moveX, moveY);
    }
    else {
        this->Movement(1.0f, 0.0f);
    }
}

bool Zombie::IsPathBlocked(float targetX, float targetY, const vector<Obstacle>& walls)
{
    float distance_X = targetX - this->m_posX;
    float distance_Y = targetY - this->m_posY;

    float testX = m_posX + distance_X * 0.5f;
    float testY = m_posY + distance_Y * 0.5f;

    SDL_Rect testRect = { (int)testX,(int)testY,1,1 };

    for (const auto& wall : walls) {
        if (CheckCollision(wall.rect)) {
            return true;
        }
    }

    return false;
}