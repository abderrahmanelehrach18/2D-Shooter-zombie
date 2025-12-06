#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include "GData.h"
#include "Player.h"
#include "zombie.h"
#include "Bullet.h"
#include "Obstacle.h"
#include "Explosion.h"

class Player;
class Zombie;
class Bullet;
class Explosion;

using namespace std;

class Game {
public:
    Game();
    ~Game() { Cleanup(); }

    bool Initialize();
    void Run();

    SDL_Renderer* GetRenderer() const { return renderer; }
    SDL_Texture* GetZombieDeathTexture() const { return zombieDeathTexture; }
    SDL_Texture* GetZombieIdleTexture() const { return zombieIdleTexture; }
    SDL_Texture* GetPlayerTexture() const { return playerTexture; }
    int GetMouseX() const { return mouseX; }
    int GetMouseY() const { return mouseY; }

    static Game* GetInstance() { return instance; }

    static void ShowControlsAndCredits();

private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    bool isRunning;

    Player* player;
    vector<Obstacle> walls;
    vector<Zombie> zombies;
    vector<Bullet> bullets;
    vector<Explosion> explosions;

    SDL_Texture* playerTexture;
    SDL_Texture* zombieIdleTexture;
    SDL_Texture* zombieDeathTexture;

    int mouseX;
    int mouseY;
    float spawnTimer;
    float elapsedGameTime;

    static float TIME_BETWEEN_SPAWNS;
    static float MIN_SPAWN_INTERVAL;
    static float DIFFICULTY_RATE;

    bool InitSDLSystems();
    bool CreateWindowAndRenderer();
    bool LoadTextures();
    void Cleanup();

    void GameLoop();
    void UpdateGame(float deltaTime, int shootX, int shootY);
    void RenderFrame();
    void HandleFrameStart(float& deltaTime, Uint32& lastTicks, int& shootX, int& shootY);
    void SpawnZombie();
    vector<Obstacle> CreateMap();

    static Game* instance;


};

extern Game* g_game;