cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 20)
project(game LANGUAGES CXX VERSION 0.0.1)

file(GLOB_RECURSE SOURCES ${CMAKE_SOURCE_DIR}/src/*.cpp)



add_executable(${PROJECT_NAME} ${SOURCES})

add_custom_target(copy_assets
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/assets ${CMAKE_CURRENT_BINARY_DIR}/assets
        )
add_dependencies(${PROJECT_NAME} copy_assets)

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/src)
target_link_libraries(${PROJECT_NAME} PRIVATE sfml-system sfml-window sfml-graphics sfml-audio)