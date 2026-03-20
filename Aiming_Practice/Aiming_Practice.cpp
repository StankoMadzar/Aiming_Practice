#include <iostream>
#include <filesystem>
#include "Game.h"

int main()
{
    // Init srand;
    std::srand(static_cast<unsigned>(time(NULL)));
    std::cout << "Current path is: " << std::filesystem::current_path() << std::endl;

    // Init Game
    Game game;

    // Game Loop
    while (game.running() && !game.getEndGame())
    {
        // Update
        game.update();

        // Render
        game.render();
    }
    
    return 0;
}
