# Game-SFML

**Game-SFML** is a 2D turn-based RPG prototype developed as a final project for the **Multimedia Systems** discipline at the **Universidade Estadual de Roraima (UERR)**. Built with **C++** and **SFML 3.0.0**, the project demonstrates core game development concepts including state management, animation systems, and interactive logic.

## Key Features

* **Turn-Based Combat System**: Implements a structured battle loop (Player Turn -> Player Action -> Enemy Turn -> Enemy Action) managed by a turn-specific state machine.
* **Finite State Machine (FSM)**: Uses a `GameState` enum to cleanly transition between the **Menu**, **Combat**, and **Game Over** scenes.
* **Custom Animation Engine**: Features an `Animator` class that handles texture loading from PNG files and manages frame-by-frame animation playback with support for looping and speed multipliers.
* **Object-Oriented Architecture**: Utilizes an `Entity` class to encapsulate game logic, linking health management (HP) directly with the animated visual representation.
* **Dynamic UI Elements**: Real-time rendering of health bars using `sf::RectangleShape` and game text via `sf::Text` that update dynamically during gameplay.
* **Cross-Scene Input Handling**: Uses the SFML 3.0 event pattern to provide context-sensitive controls, allowing keys like "Z" to perform different actions depending on the active scene.

## Technical Stack

* **Language**: C++.
* **Library**: SFML 3.0.0.
* **Compiler**: MinGW (g++).
* **Development Environment**: Visual Studio Code.

## Controls

* **[Z]**: Start game (Menu) or execute an attack (Combat).
* **[G]**: Force a Game Over for testing purposes.
* **[Esc]**: Close the game application.

## Project Structure

* **/include**: Header files (`.hpp`) containing class definitions for the Animator, Entity, and utility functions.
* **/src**: Implementation files (`.cpp`) for core game logic.
* **/assets**: Game resources including textures (`.png`) and fonts (`.ttf`).
* **main.cpp**: Entry point containing the main game loop and scene management.

