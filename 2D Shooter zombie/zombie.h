#pragma once

#include "Character.h"
#include "Player.h"
#include <vector>
#include <SDL2/SDL.h> 

extern int zombiesKilled;

enum ZombieState {
    Z_MOVING,
    Z_DEATH
};

class Zombie : public Character
{
public:
    Zombie(int x, int y, int w, int h, float speed);

    void Update(float deltaTime, const Player& player, const vector<Obstacle>& walls);
    void Render(SDL_Renderer* renderer, SDL_Texture* idleTex, SDL_Texture* deathTex);

    void TakeDamage(int damage) override;

private:
    ZombieState m_state = Z_MOVING;
    float m_animTimer = 0.0f;
    int m_currentFrame = 0;

    void AIsearch(const Player& player, const vector<Obstacle>& walls);
    bool IsPathBlocked(float targetX, float targetY, const vector<Obstacle>& walls);
};