#pragma once
#include "Character.h"
#include <SDL2/SDL.h>

class Player :
    public Character
{
public:
    Player(int x, int y, int w, int h);

    void StartInvulnerability();
    void Update(float deltaTime) override;

    bool IsInvulnerable() const { return m_isInvulnerable; }

    void Render(SDL_Renderer* renderer) override;
    void HandleInput(const Uint8* keyState);

private:
    bool m_isInvulnerable = false;
    float m_invulnerabilityTimer = 0.0f;
    const float INVULNERABILITY_DURATION = 1.0f;

    float m_animTimer = 0.0f;
    int m_currentFrame = 0;
    const float FRAME_DURATION = 0.15f;

    float m_lastDirX = 0.0f;
    float m_lastDirY = 1.0f;

    const int SPRITE_W = 17;
    const int SPRITE_H = 12;
    const int FRAME_COUNT = 5;

    const int WALK_COLUMN_X = 0;
};