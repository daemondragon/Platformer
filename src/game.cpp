#include "game.hpp"

void Game::add(Module &module)
{
    modules.push_back(&module);
}

void Game::runLoop()
{
    bool quit = false;

    while (!quit)
    {
        for (auto &module : modules)
            module->update(world, quit);
    }
}

