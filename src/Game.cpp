//
// Created by Kelvin on 18/06/2020.
//

#include <iostream>

#include "Constants.h"
#include "Game.h"
#include "AssetManager.h"
#include "EntityManager.h"
#include "Entity.h"

#include "../lib/glm/glm.hpp"

#include "../components/TransformComponent.h"
#include "../components/SpriteComponent.h"
#include "../components/KeyboardComponent.h"

EntityManager manager;
AssetManager* Game::assetManager = new AssetManager(&manager);
SDL_Renderer* Game::renderer;
SDL_Event Game::event;

Game::Game() {
    this->isRunning = false;
}

Game::~Game() {}

bool Game::IsRunning() const {
    return this->isRunning;
}

void Game::Initialize(int width, int height) {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        std::cerr << "Error initializing SDL." << std::endl;
    }

    window = SDL_CreateWindow(NULL, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height,
                              SDL_WINDOW_BORDERLESS);
    if (!window) {
        std::cerr << "Error creating SDL window." << std::endl;
        return;
    }

    renderer = SDL_CreateRenderer(window, -1, 0);
    if (!renderer) {
        std::cerr << "Error creating SDL renderer." << std::endl;
        return;
    }

    LoadLevel(0);

    isRunning = true;
    return;

}

void Game::LoadLevel(int levelIndex) {
    // Start including new assets to the AssetManager list.
    assetManager->AddTexture("Tank-Image", std::string("../assets/images/tank-big-right.png").c_str());
    assetManager->AddTexture("Chopper-Image", std::string("../assets/images/chopper-spritesheet.png").c_str());
    assetManager->AddTexture("Radar-Image", std::string("../assets/images/radar.png").c_str());

    // Start including entities and also its components.
    Entity& chopperEntity(manager.AddEntity("Chopper"));
    chopperEntity.AddComponent<TransformComponent>(240, 100, 0, 0, 32, 32, 1);
    chopperEntity.AddComponent<SpriteComponent>("Chopper-Image", 2, 90, true, false);
    chopperEntity.AddComponent<KeyboardComponent>("up", "right", "down", "left", "space");

    Entity& tankEntity(manager.AddEntity("Tank"));
    tankEntity.AddComponent<TransformComponent>(0, 0, 20, 30, 32, 32, 1);
    tankEntity.AddComponent<SpriteComponent>("Tank-Image");

    Entity& radarEntity(manager.AddEntity("Radar"));
    radarEntity.AddComponent<TransformComponent>(720, 15, 0, 0, 64, 64, 1);
    radarEntity.AddComponent<SpriteComponent>("Radar-Image", 8, 150, false, true);
}

void Game::ProcessInput() {
    SDL_PollEvent(&event);

    switch(event.type) {
        case SDL_QUIT:
            isRunning = false;
            break;
        case SDL_KEYDOWN:
            if (event.key.keysym.sym == SDLK_ESCAPE) {
                isRunning = false;
            }
            break;
        default:
            break;
    }
}

void Game::Update() {
    // Time to delay the process until it reaches the target frame time in milliseconds.
    int timeToWait = FRAME_TARGET_TIME - (SDL_GetTicks() - ticksLastFrame);

    // Only delays if we are too fast to process this specific frame.
    if (timeToWait > 0 && timeToWait <= FRAME_TARGET_TIME) {
        SDL_Delay(timeToWait);
    }

    // Difference in ticks from last frame converted to seconds.
    float deltaTime = (SDL_GetTicks() - ticksLastFrame) / 1000.0f;

    // Clamp deltaTime to a maximum value.
    deltaTime = (deltaTime > 0.05f) ? 0.05f : deltaTime;

    // Sets the new ticks for the current frame to be used in the next pass.
    ticksLastFrame = SDL_GetTicks();

    // Update all the entities and therefore it's components.
    manager.Update(deltaTime);
}

void Game::Render() {
    SDL_SetRenderDrawColor(renderer, 21, 21, 21, 255);
    SDL_RenderClear(renderer);

    if (manager.HasNoEntities()) {
        return;
    }

    manager.Render();

    SDL_RenderPresent(renderer);
}

void Game::Destroy() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}