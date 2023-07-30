cmake_minimum_required(VERSION 3.0)
project(Snake LANGUAGES CXX)

set(SOURCES
    src/main.cpp
    src/General/Game.cpp
    src/General/PositionConverter.cpp
    src/General/NumberGenerator.cpp
    
    src/InGame/Snake.cpp
    src/InGame/DrawableCell.cpp
    src/InGame/World.cpp
    src/InGame/Grid.cpp
    src/InGame/DataCell.cpp
    src/InGame/LightShader.cpp
)

set(HEADERS 
    src/General/Game.h
    src/General/PositionConverter.h
    src/General/NumberGenerator.h

    src/InGame/Snake.h
    src/InGame/DrawableCell.h
    src/InGame/World.h
    src/InGame/Grid.h
    src/InGame/DataCell.h
    src/InGame/LightShader.h
)

include_directories(${CMAKE_SOURCE_DIR}/src/General)
include_directories(${CMAKE_SOURCE_DIR}/src/InGame)
include_directories(${CMAKE_SOURCE_DIR}/src/MainMenu)

set(EXE_DIR ${CMAKE_BINARY_DIR}/Game)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Game)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})
target_link_libraries(${PROJECT_NAME} PRIVATE sfml-graphics)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)
if (WIN32 AND BUILD_SHARED_LIBS)
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:${PROJECT_NAME}> $<TARGET_FILE_DIR:${PROJECT_NAME}> COMMAND_EXPAND_LISTS)
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(${PROJECT_NAME} PRIVATE -DDEBUG_MODE)
else()
    target_compile_definitions(${PROJECT_NAME} PRIVATE -DRELEASE_MODE)
    set_target_properties(${PROJECT_NAME} PROPERTIES WIN32_EXECUTABLE TRUE)
endif()

install(TARGETS ${PROJECT_NAME})