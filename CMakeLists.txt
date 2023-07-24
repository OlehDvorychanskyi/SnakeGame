cmake_minimum_required(VERSION 3.0)
project(Snake LANGUAGES CXX)

set(SOURCES
    src/main.cpp
    src/Game.cpp
    src/Snake.cpp
    src/Cell.cpp
    src/Fruit.cpp
    src/World.cpp
    src/NumberGenerator.cpp
)

set(HEADERS 
    src/Game.h
    src/Snake.h
    src/Cell.h
    src/Fruit.h
    src/World.h
    src/NumberGenerator.h
)

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