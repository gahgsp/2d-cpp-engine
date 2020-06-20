cmake_minimum_required(VERSION 3.15)
project(engine2d)

set(CMAKE_CXX_STANDARD 14)

include_directories(${PROJECT_SOURCE_DIR}/include)
link_directories(${PROJECT_SOURCE_DIR}/lib)

add_executable(engine2d main.cpp src/Constants.h src/Game.h src/Game.cpp src/Component.cpp src/Component.h src/Entity.cpp src/Entity.h src/EntityManager.cpp src/EntityManager.h components/TransformComponent.cpp components/TransformComponent.h src/TextureManager.cpp src/TextureManager.h src/AssetManager.cpp src/AssetManager.h components/SpriteComponent.cpp components/SpriteComponent.h)

target_link_libraries(engine2d SDL2main SDL2 SDL2_image)