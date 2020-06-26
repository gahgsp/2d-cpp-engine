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
#include "Map.h"
#include "../components/ColliderComponent.h"
#include "../components/ProjectileEmitterComponent.h"
#include "../components/TextLabelComponent.h"

EntityManager manager;
AssetManager* Game::assetManager = new AssetManager(&manager);
SDL_Renderer* Game::renderer;
SDL_Event Game::event;
SDL_Rect Game::camera = {0, 0, WINDOW_WIDTH, WINDOW_HEIGHT};
Map* map;

Entity* player = NULL;

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

    if (TTF_Init() != 0) {
        std::cerr << "Error initializing SDL TTF." << std::endl;
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

    LoadLevel(1);

    isRunning = true;
    return;

}

void Game::LoadLevel(int levelIndex) {
    sol::state lua;
    lua.open_libraries(sol::lib::base, sol::lib::os, sol::lib::math);

    std::string levelName = "Level" + std::to_string(levelIndex);
    lua.script_file("../assets/scripts/" + levelName + ".lua");

    // Loading Assets from Lua level file.
    sol::table levelData = lua[levelName];
    sol::table levelAssets = levelData["assets"];

    unsigned int assetIndex = 0;
    while (true) {
        sol::optional<sol::table> existsAssetIndexNode = levelAssets[assetIndex];
        if (existsAssetIndexNode == sol::nullopt) {
            break;
        } else {
            sol::table asset = levelAssets[assetIndex];
            std::string assetType = asset["type"];
            if (assetType.compare("texture") == 0) {
                std::string assetName = asset["id"];
                std::string assetFile = asset["file"];
                assetManager->AddTexture(assetName, assetFile.c_str());
            }
            if (assetType.compare("font") == 0) {
                std::string assetName = asset["id"];
                std::string assetFile = asset["file"];
                int fontSize = asset["fontSize"];
                assetManager->AddFont(assetName, assetFile.c_str(), fontSize);
            }
        }
        assetIndex++;
    }

    // Loading Map from Lua level file.
    sol::table levelMap = levelData["map"];
    std::string mapTextureName = levelMap["textureAssetId"];
    std::string mapFile = levelMap["file"];

    map = new Map(mapTextureName, static_cast<int>(levelMap["scale"]), static_cast<int>(levelMap["tileSize"]));
    map->LoadMap(mapFile, static_cast<int>(levelMap["mapSizeX"]), static_cast<int>(levelMap["mapSizeY"]));

    // Loading Entities from Lua level file.
    sol::table entities = levelData["entities"];
    unsigned int entityIndex = 0;
    while (true) {
        sol::optional<sol::table> existsEntityIndexNode = entities[entityIndex];
        if (existsEntityIndexNode == sol::nullopt) {
            break;
        } else {
            sol::table entity = entities[entityIndex];
            std::string entityName = entity["name"];
            LayerType entityLayerType = static_cast<LayerType>(static_cast<int>(entity["layer"]));

            // Creating a new entity.
            auto& newEntity(manager.AddEntity(entityName, entityLayerType));

            // Adding the Transform component.
            sol::optional<sol::table> existsTransformIndexNode = entity["components"]["transform"];
            if (existsTransformIndexNode != sol::nullopt) {
                newEntity.AddComponent<TransformComponent>(
                        static_cast<int>(entity["components"]["transform"]["position"]["x"]),
                        static_cast<int>(entity["components"]["transform"]["position"]["y"]),
                        static_cast<int>(entity["components"]["transform"]["velocity"]["x"]),
                        static_cast<int>(entity["components"]["transform"]["velocity"]["y"]),
                        static_cast<int>(entity["components"]["transform"]["width"]),
                        static_cast<int>(entity["components"]["transform"]["height"]),
                        static_cast<int>(entity["components"]["transform"]["scale"])
                );
            }

            // Adding the Sprite component.
            sol::optional<sol::table> existsSpriteIndexNode = entity["components"]["sprite"];
            if (existsSpriteIndexNode != sol::nullopt) {
                std::string textureId = entity["components"]["sprite"]["textureAssetId"];
                bool isAnimated = entity["components"]["sprite"]["animated"];
                if (isAnimated) {
                    newEntity.AddComponent<SpriteComponent>(
                            textureId,
                            static_cast<int>(entity["components"]["sprite"]["frameCount"]),
                            static_cast<int>(entity["components"]["sprite"]["animationSpeed"]),
                            static_cast<bool>(entity["components"]["sprite"]["hasDirections"]),
                            static_cast<bool>(entity["components"]["sprite"]["fixed"])
                    );
                } else {
                    newEntity.AddComponent<SpriteComponent>(textureId);
                }
            }

            // Adding the Collider component.
            sol::optional<sol::table> existsColliderIndexNode = entity["components"]["collider"];
            if (existsColliderIndexNode != sol::nullopt) {
                std::string colliderTag = entity["components"]["collider"]["tag"];
                newEntity.AddComponent<ColliderComponent>(
                        colliderTag,
                        static_cast<int>(entity["components"]["transform"]["position"]["x"]),
                        static_cast<int>(entity["components"]["transform"]["position"]["y"]),
                        static_cast<int>(entity["components"]["transform"]["width"]),
                        static_cast<int>(entity["components"]["transform"]["height"])
                );
            }

            // Adding the Keyboard component.
            sol::optional<sol::table> existsInputIndexNode = entity["components"]["input"];
            if (existsInputIndexNode != sol::nullopt) {
                sol::optional<sol::table> existsKeyboardIndexNode = entity["components"]["input"]["keyboard"];
                if (existsKeyboardIndexNode != sol::nullopt) {
                    std::string upKey = entity["components"]["input"]["keyboard"]["up"];
                    std::string rightKey = entity["components"]["input"]["keyboard"]["right"];
                    std::string downKey = entity["components"]["input"]["keyboard"]["down"];
                    std::string leftKey = entity["components"]["input"]["keyboard"]["left"];
                    std::string shootKey = entity["components"]["input"]["keyboard"]["shoot"];
                    newEntity.AddComponent<KeyboardComponent>(upKey, rightKey, downKey, leftKey, shootKey);
                }
            }

            // Adding the Projectile Emitter component.
            sol::optional<sol::table> existsProjectileEmitterIndexNode = entity["components"]["projectileEmitter"];
            if (existsProjectileEmitterIndexNode != sol::nullopt) {
                int parentEntityXPos = entity["components"]["transform"]["position"]["x"];
                int parentEntityYPos = entity["components"]["transform"]["position"]["y"];
                int parentEntityWidth = entity["components"]["transform"]["width"];
                int parentEntityHeight = entity["components"]["transform"]["height"];
                int projectileWidth = entity["components"]["projectileEmitter"]["width"];
                int projectileHeight = entity["components"]["projectileEmitter"]["height"];
                int projectileSpeed = entity["components"]["projectileEmitter"]["speed"];
                int projectileRange = entity["components"]["projectileEmitter"]["range"];
                int projectileAngle = entity["components"]["projectileEmitter"]["angle"];
                bool projectileShouldLoop = entity["components"]["projectileEmitter"]["shouldLoop"];
                std::string textureAssetId = entity["components"]["projectileEmitter"]["textureAssetId"];
                Entity& projectile(manager.AddEntity("Projectile", PROJECTILE_LAYER));
                projectile.AddComponent<TransformComponent>(
                        parentEntityXPos + (parentEntityWidth / 2),
                        parentEntityYPos + (parentEntityHeight / 2),
                        0,
                        0,
                        projectileWidth,
                        projectileHeight,
                        1
                );
                projectile.AddComponent<SpriteComponent>(textureAssetId);
                projectile.AddComponent<ProjectileEmitterComponent>(
                        projectileSpeed,
                        projectileAngle,
                        projectileRange,
                        projectileShouldLoop
                );
                projectile.AddComponent<ColliderComponent>(
                        "Projectile",
                        parentEntityXPos,
                        parentEntityYPos,
                        projectileWidth,
                        projectileHeight
                );
            }

            // Adding the Label component.
            sol::optional<sol::table> existsLabelIndexNode = entity["components"]["label"];
            if (existsLabelIndexNode != sol::nullopt) {
                newEntity.AddComponent<TextLabelComponent>(
                        entity["components"]["label"]["position"]["x"],
                        entity["components"]["label"]["position"]["y"],
                        entity["components"]["label"]["text"],
                        entity["components"]["label"]["fontFamily"],
                        SDL_Color {
                            .r =  entity["components"]["label"]["color"]["r"],
                            .g =  entity["components"]["label"]["color"]["g"],
                            .b =  entity["components"]["label"]["color"]["b"],
                            .a =  entity["components"]["label"]["color"]["a"]
                        });
            }
        }
        entityIndex++;
    }

    player = manager.GetEntityByName("Player");
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

    HandleCameraMovement();
    CheckCollisions();
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

void Game::HandleCameraMovement() {
   TransformComponent* playerTransform = player->GetComponent<TransformComponent>();
    camera.x = playerTransform->position.x - (WINDOW_WIDTH / 2);
    camera.y = playerTransform->position.y - (WINDOW_HEIGHT / 2);

    // Clamping the values of the camera.
    camera.x = camera.x < 0 ? 0 : camera.x;
    camera.y = camera.y < 0 ? 0 : camera.y;
    camera.x = camera.x > camera.w ? camera.w : camera.x;
    camera.y = camera.y > camera.h ? camera.h : camera.y;
}

void Game::CheckCollisions() {
    CollisionType collisionType = manager.CheckCollisions();
    if (collisionType == PLAYER_ENEMY_COLLISION) {
        ProcessGameOver();
    }
    if (collisionType == PLAYER_PROJECTILE_COLLISION) {
        ProcessGameOver();
    }
    if (collisionType == PLAYER_LEVEL_COMPLETE_COLLISION) {
        ProcessLevelComplete();
    }
}

void Game::ProcessGameOver() {
    std::cout << "Game Over!" << std::endl;
    isRunning = false;
}

void Game::ProcessLevelComplete() {
    // TODO: Should load next level!
    // LoadLevel(2);
    std::cout << "Congratulations! You finished the level!" << std::endl;
    isRunning = false;
}

void Game::Destroy() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}