#include "Game.h"
#include <iostream>


float Game::TIME_BETWEEN_SPAWNS = 5.0f;
float Game::MIN_SPAWN_INTERVAL = 0.5f;
float Game::DIFFICULTY_RATE = 0.03f;

Game* Game::instance = nullptr;
Game* g_game = nullptr;

int zombiesKilled = 0;

Game::Game() : window(nullptr), renderer(nullptr), isRunning(true),
player(nullptr), playerTexture(nullptr), zombieIdleTexture(nullptr),
zombieDeathTexture(nullptr), mouseX(0), mouseY(0),
spawnTimer(0.0f), elapsedGameTime(0.0f) {
    instance = this;
    g_game = this;
    srand((unsigned int)time(0));
}

bool Game::Initialize() {
    if (!InitSDLSystems()) return false;
    if (!CreateWindowAndRenderer()) return false;
    if (!LoadTextures()) return false;

    const int startX = 720;
    const int startY = GData::WINDOW_HEIGHT / 2 - 25;
    player = new Player(startX, startY, 70, 60);

    walls = CreateMap();

    return true;
}

void Game::Run() {
    GameLoop();

    cout << "Zombies killed: " << zombiesKilled << endl;
}

bool Game::InitSDLSystems() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        cout << "SDL init! Error: " << SDL_GetError() << endl;
        return false;
    }

    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        cout << "SDL init! Error: " << IMG_GetError() << endl;
        SDL_Quit();
        return false;
    }
    return true;
}

bool Game::CreateWindowAndRenderer() {
    window = SDL_CreateWindow("2D shooter zombie : LEHRACH ABDERRAHMANE",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        GData::WINDOW_WIDTH, GData::WINDOW_HEIGHT,
        SDL_WINDOW_SHOWN);

    if (window == nullptr) {
        cout << "Window could not be created! SDL Error: " << SDL_GetError() << endl;
        SDL_Quit();
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if (renderer == nullptr) {
        cout << "Renderer could not be created! SDL Error: " << SDL_GetError() << endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return false;
    }

    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    return true;
}

bool Game::LoadTextures() {
    playerTexture = IMG_LoadTexture(renderer, "assets/topdownpack.png");
    if (playerTexture == nullptr) {
        cout << "Player texture loading failed: " << IMG_GetError() << endl;
        return false;
    }

    zombieIdleTexture = IMG_LoadTexture(renderer, "assets/Idle_Fly.png");
    if (zombieIdleTexture == nullptr) {
        cout << "Zombie Idle texture loading failed: " << IMG_GetError() << endl;
        return false;
    }

    zombieDeathTexture = IMG_LoadTexture(renderer, "assets/Attack_Death.png");
    if (zombieDeathTexture == nullptr) {
        cout << "Zombie Death texture loading failed: " << IMG_GetError() << endl;
        return false;
    }

    return true;
}

void Game::Cleanup() {
    delete player;

    if (playerTexture) SDL_DestroyTexture(playerTexture);
    if (zombieIdleTexture) SDL_DestroyTexture(zombieIdleTexture);
    if (zombieDeathTexture) SDL_DestroyTexture(zombieDeathTexture);

    if (renderer) SDL_DestroyRenderer(renderer);
    if (window) SDL_DestroyWindow(window);

    IMG_Quit();
    SDL_Quit();
}

void Game::GameLoop() {
    float deltaTime = 0.0f;
    Uint32 lastTicks = SDL_GetTicks();

    while (isRunning) {
        int shootX = 0, shootY = 0;
        HandleFrameStart(deltaTime, lastTicks, shootX, shootY);
        UpdateGame(deltaTime, shootX, shootY);
        RenderFrame();
    }
}

void Game::HandleFrameStart(float& deltaTime, Uint32& lastTicks, int& shootX, int& shootY) {
    Uint32 nowTicks = SDL_GetTicks();
    deltaTime = (nowTicks - lastTicks) * 0.001f;
    lastTicks = nowTicks;

    SDL_GetMouseState(&mouseX, &mouseY);

    shootX = 0;
    shootY = 0;

    SDL_Event event;
    while (SDL_PollEvent(&event) != 0) {
        if (event.type == SDL_QUIT) {
            isRunning = false;
        }
        if (event.type == SDL_MOUSEBUTTONDOWN) {
            shootX = event.button.x;
            shootY = event.button.y;
        }
    }
}

void Game::UpdateGame(float deltaTime, int shootX, int shootY) {
    const Uint8* keyState = SDL_GetKeyboardState(NULL);

    if (!player->IsAlive()) {
        cout << "GAME OVER!" << endl;
        isRunning = false;
        return;
    }

    if (shootX != 0 || shootY != 0) {
        float pX = player->GetPosX() + player->GetW() / 2.0f;
        float pY = player->GetPosY() + player->GetH() / 2.0f;

        float dirX = (float)shootX - pX;
        float dirY = (float)shootY - pY;

        float length = std::sqrt(dirX * dirX + dirY * dirY);
        if (length > 0) {
            dirX /= length;
            dirY /= length;
        }

        bullets.emplace_back(pX, pY, dirX, dirY, 10, 500.0f);
    }

    spawnTimer += deltaTime;
    elapsedGameTime += deltaTime;

    float currentSpawnInterval = TIME_BETWEEN_SPAWNS - (elapsedGameTime * DIFFICULTY_RATE);
    if (currentSpawnInterval < MIN_SPAWN_INTERVAL) {
        currentSpawnInterval = MIN_SPAWN_INTERVAL;
    }

    if (spawnTimer >= currentSpawnInterval) {
        spawnTimer = 0.0f;
        int zombiesToSpawn = 1;
        if (elapsedGameTime > 30.0f) zombiesToSpawn = 2;
        if (elapsedGameTime > 60.0f) zombiesToSpawn = 3;

        for (int i = 0; i < zombiesToSpawn; ++i) {
            SpawnZombie();
        }
    }

    player->HandleInput(keyState);

    player->ApplyDeltaTimeX(deltaTime);
    for (const auto& wall : walls) {
        if (player->CheckCollision(wall.rect)) {
            player->RevertMovementX(deltaTime);
            break;
        }
    }

    player->ApplyDeltaTimeY(deltaTime);
    for (const auto& wall : walls) {
        if (player->CheckCollision(wall.rect)) {
            player->RevertMovementY(deltaTime);
            break;
        }
    }

    for (auto it = bullets.begin(); it != bullets.end(); ) {
        it->Update(deltaTime);
        bool hit = false;
        bool wallHit = false;

        for (const auto& wall : walls) {
            if (it->CheckCollision(wall.rect)) {
                wallHit = true;
                break;
            }
        }

        for (int i = (int)zombies.size() - 1; i >= 0; --i) {
            if (zombies[i].CheckCollision(it->GetRect())) {
                zombies[i].TakeDamage(1);
                hit = true;

                if (!zombies[i].IsAlive()) {
                    float zX = zombies[i].GetPosX() + zombies[i].GetW() / 2.0f;
                    float zY = zombies[i].GetPosY() + zombies[i].GetH() / 2.0f;
                    explosions.emplace_back(zX, zY, 63, 66);
                    zombies.erase(zombies.begin() + i);
                }
                break;
            }
        }

        if (hit || wallHit || it->IsOffScreen()) {
            it = bullets.erase(it);
        }
        else {
            ++it;
        }
    }

    for (auto exp_it = explosions.begin(); exp_it != explosions.end(); ) {
        exp_it->Update(deltaTime);
        if (exp_it->IsFinished()) {
            exp_it = explosions.erase(exp_it);
        }
        else {
            ++exp_it;
        }
    }

    for (auto& zombie : zombies) {
        zombie.Update(deltaTime, *player, walls);

        if (zombie.CheckCollision(player->getRect()) && !player->IsInvulnerable()) {
            player->TakeDamage(1);
            player->StartInvulnerability();
        }
    }

    player->Update(deltaTime);
}

void Game::RenderFrame() {
    SDL_SetRenderDrawColor(renderer, 132, 142, 164, 255);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 48, 48, 96, 255);

    for (const auto& wall : walls) {
        SDL_RenderFillRect(renderer, &wall.rect);
    }

    for (auto& exp : explosions) {
        exp.Render(renderer, zombieDeathTexture);
    }

    for (auto& zombie : zombies) {
        zombie.Render(renderer, zombieIdleTexture, zombieDeathTexture);
    }

    for (auto& b : bullets) {
        b.Render(renderer);
    }
    player->Render(renderer);

    SDL_RenderPresent(renderer);
}

void Game::SpawnZombie() {
    float spawnX, spawnY;
    const float margin = 50.0f;

    if (rand() % 2 == 0) {
        spawnX = (float)(rand() % GData::WINDOW_WIDTH);
        if (rand() % 2 == 0) {
            spawnY = -margin;
        }
        else {
            spawnY = (float)GData::WINDOW_HEIGHT + margin;
        }
    }
    else {
        spawnY = (float)(rand() % GData::WINDOW_HEIGHT);
        if (rand() % 2 == 0) {
            spawnX = -margin;
        }
        else {
            spawnX = (float)GData::WINDOW_WIDTH + margin;
        }
    }

    zombies.emplace_back(spawnX, spawnY, 63, 66, 150.0f);
}

vector<Obstacle> Game::CreateMap() {
    vector<Obstacle> walls;

    walls.emplace_back(250, 300, 100, 200);
    walls.emplace_back(610, 300, 100, 200);
    walls.emplace_back(80, 80, 20, 200);
    walls.emplace_back(80, 440, 20, 200);
    walls.emplace_back(860, 80, 20, 200);
    walls.emplace_back(860, 440, 20, 200);
    walls.emplace_back(400, 100, 20, 150);
    walls.emplace_back(400, 100, 160, 20);
    walls.emplace_back(540, 570, 20, 150);
    walls.emplace_back(380, 570, 160, 20);

    return walls;
}

void Game::ShowControlsAndCredits()
{
    std::cout << "        ZOMBIE SHOOTER GAME\n\n";
    std::cout << "CONTROLS:\n";
    std::cout << "  Movement: W/A/S/D or Z/Q/S/D keys\n";
    std::cout << "  Aiming: With your Mouse\n";
    std::cout << "  Shooting: Left Mouse Button\n";
    std::cout << "  Exit:     Close window\n\n";
    std::cout << "OBJECTIVE:\n";
    std::cout << "  Survive as long as possible!\n";
    std::cout << "  Shoot zombies before they reach you.\n";
    std::cout << "  Zombies spawn faster over time.\n\n";
    std::cout << "Created by: LEHRACH ABDERRAHMANE\n\n";

    system("pause");
}