cmake_minimum_required(VERSION 3.0)
project(Snake)

include_directories("${CMAKE_SOURCE_DIR}/SFML/include")

set(SOURCES
    src/main.cpp
)

set(HEADERS 

)

set(EXE_DIR ${CMAKE_BINARY_DIR}/Game)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Game)

set(SFML_DIR "${CMAKE_SOURCE_DIR}/SFML/lib/cmake/SFML")
find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})
target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-audio sfml-window sfml-system)

if (WIN32)
    set(SFML_DLL_DIR "${CMAKE_SOURCE_DIR}/SFML/bin")
    file(GLOB SFML_DLLS "${SFML_DLL_DIR}/*.dll")
    file(COPY ${SFML_DLLS} DESTINATION ${CMAKE_BINARY_DIR}/Game)
endif()