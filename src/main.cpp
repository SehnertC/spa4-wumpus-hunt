#include <iostream>
#include "Map.h"
#include "Player.h"
#include "Arrow.h"
#include "MagicOrb.h"

void displayHelp() {
    std::cout << "\n--- HUNT THE WUMPUS - GAME RULES ---\n";
    std::cout << "Goal: Find and defeat the Wumpus hidden in the caves.\n";
    std::cout << "Hazards: Beware of pits, bats, and trapdoors.\n";
    std::cout << "Commands:\n";
    std::cout << "  N/E/S/W - Move North, East, South, or West.\n";
    std::cout << "  A - Shoot an arrow.\n";
    std::cout << "  M - Display the map (Debug mode).\n";
    std::cout << "  H - Display this help message.\n";
    std::cout << "  Q - Quit the game.\n";
    std::cout << "Clues:\n";
    std::cout << "  You will receive clues about nearby hazards to help navigate safely.\n";
    std::cout << "-------------------------------------\n";
}

int main() {
    int gridSize = 5; // Define grid size for the map
    Map gameMap(gridSize);
    // Associate player with the map
    Player player(&gameMap);
    gameMap.setPlayer(&player);
    gameMap.generateMap();

    bool gameRunning = true;
    char command;
    std::cout << "Welcome to Hunt the Wumpus! Enter 'H' for help.\n";

    while (gameRunning && player.isAlive()) {
        std::cout << "Enter command (N/E/S/W to move, A to shoot, M for map, H for help, Q to quit): ";
        std::cin >> command;
        std::cin.clear();
        command = std::tolower(command);

        switch (command) {
            case 'n':
            case 'e':
            case 's':
            case 'w':
                player.move(command);
                break;
            case 'a': {
                char direction;
                std::cout << "Enter direction to shoot (N/E/S/W): ";
                std::cin >> direction;
                std::cin.clear();
                player.useWeapon(std::tolower(direction));
                break;
            }
            case 'm':
                gameMap.displayMap(); // Display map reflecting player's position
                break;
            case 'h':
                displayHelp();
                break;
            case 'q':
                gameRunning = false;
                break;
            default:
                std::cout << "Invalid command. Enter 'H' for help.\n";
        }
    }

    if (!player.isAlive()) {
        std::cout << "Game over! Better luck next time.\n";
    } else {
        std::cout << "Thanks for playing!\n";
    }

    return 0;
}
