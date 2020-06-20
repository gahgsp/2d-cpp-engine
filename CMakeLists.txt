cmake_minimum_required(VERSION 3.15)
project(engine2d)

set(CMAKE_CXX_STANDARD 14)

include_directories(${PROJECT_SOURCE_DIR}/include)
link_directories(${PROJECT_SOURCE_DIR}/lib)

add_executable(engine2d main.cpp Constants.h Game.h Game.cpp Component.cpp Component.h Entity.cpp Entity.h EntityManager.cpp EntityManager.h components/TransformComponent.cpp components/TransformComponent.h)

target_link_libraries(engine2d SDL2main SDL2)