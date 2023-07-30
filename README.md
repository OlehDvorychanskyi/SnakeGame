# SnakeGame

## SnakeGame ScreenShot
![Screenshot](https://github.com/OlehDvorychanskyi/SnakeGame/blob/main/SnakeGame_screenshot.jpg)

## Installation

To play the game, follow these installation steps:

1. Clone the repository to your local machine using Git:

    ```bash
    git clone https://github.com/OlehDvorychanskyi/SnakeGame.git
    ```

2. Navigate to the project's root directory:

    ```bash
    cd SnakeGame
    ```

3. Next, create a build directory and configure CMake based on your desired build configuration. For a release build, enter the following command:

    ```bash
    cmake -S . -B build -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Release
    ```

    For a debug build, use the following command:

    ```bash
    cmake -S . -B build -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Debug
    ```

4. After configuring CMake, build the project using the following command:

    ```bash
    cmake --build build
    ```

The game will now be compiled based on your chosen build configuration (Release or Debug), and the executable will be available in the "build/Game" directory. To run the game, simply execute the generated executable file.
