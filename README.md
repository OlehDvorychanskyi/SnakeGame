# Snake Game 

## Table of Contents  
- [Introduction](#introduction) 
- [Features](#features) 
- [Installation](#installation) 
- [How to Play](#how-to-play) 
- [Screenshots](#screenshots) 
- [Contributing](#contributing) 
- [License](#license) 

## Introduction 
Welcome to Snake Game, a classic arcade game where you control a snake that grows longer as it eats food and must avoid colliding with the walls of the game board. This Snake Game is implemented using SFML and C++.

## Features  
- Classic gameplay inspired by the original Snake game. 
- Dynamic snake growth. 
- Randomly generated food items for the snake to eat. 
- Score tracking. 
- Dynamic lighting using GLSL shaders.

 ## Installation  
 You have multiple options for downloading and playing the Snake Game.
 
 ### Option 1: Downloading Releases
 1. Visit the [Releases](https://github.com/OlehDvorychanskyi/SnakeGame/releases) page on this repository. 
 2. Browse the available releases and download the one you prefer (usually the latest version). 
 3. Extract the downloaded archive to a location of your choice. 4. Run the game executable to start playing.
 
 ### Option 2: Building with CMake
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

## How to Play  
### Controls  
-  **Arrow Up / W:** Move the snake upwards.
-  **Arrow Down / S:** Move the snake downwards. 
-  **Arrow Left / A:** Move the snake to the left. 
-  **Arrow Right / D:** Move the snake to the right.

### Customizing Gameplay with config.ini
You can customize various aspects of the game using the `config.ini` file. This configuration file allows you to modify parameters such as: 
#### [Window]
-  **width:** Window width. 
-  **height:** Window height.
-  **fullscreen:** A boolean variable that controls fullscreen mode. Value 0 - false, 1 - true.

#### [World]
-  **widthCells:** The number of cells horizontally. 
-  **heightCells:** The number of cells vertically.
-  **fruitsNumber:** The number of fruits. (The maximum number of fruits is 20. You can specify more, but then the remaining fruits will not have dynamic lighting).

#### [Snake]
-  **speed:** The speed at which the snake moves (If you specify, for example, 10, it means that your snake will move at a speed of 10 cells per second).

## Screenshots  
![Screenshot](https://github.com/OlehDvorychanskyi/SnakeGame/blob/main/SnakeGame_screenshot1.jpg)
![Screenshot](https://github.com/OlehDvorychanskyi/SnakeGame/blob/main/SnakeGame_screenshot2.jpg) 

## Contributing 
Contributions are welcome! If you'd like to contribute to the project, follow these steps: 
1. Fork the repository. 
2. Create a new branch for your feature or bug fix. 
3. Make your changes and commit them with descriptive messages. 
4. Push your changes to your fork.
5. Create a pull request to the main repository's `main` branch. 

## License 
This project is licensed under the CC BY-NC - see the [LICENSE](https://github.com/OlehDvorychanskyi/SnakeGame/blob/main/LICENSE.md) file for details.