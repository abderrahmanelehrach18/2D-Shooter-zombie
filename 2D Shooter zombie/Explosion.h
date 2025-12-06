#pragma once

#include "GameObject.h"
#include <SDL2/SDL.h>

class Explosion : public GameObject {
public:
    Explosion(float x, float y, int w, int h);

    void Update(float deltaTime) override;



    void Render(SDL_Renderer* renderer, SDL_Texture* texture);

    bool IsFinished() const { return m_isFinished; }

private:

    void Render(SDL_Renderer* renderer)override;

    static constexpr int FRAME_WIDTH = 96;
    static constexpr int FRAME_HEIGHT = 80;
    static constexpr int FRAME_COUNT = 8;
    static constexpr float FRAME_DURATION = 0.12f;

    static constexpr int SCALE_FACTOR = 3;

    float m_animTimer = 0.0f;
    int m_currentFrame = 0;
    bool m_isFinished = false;
};