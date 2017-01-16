#include <iostream>

#include "parser.hpp"
#include "terrain.hpp"
#include "game.hpp"
#include "world.hpp"
#include "window.hpp"
#include "physic.hpp"
#include "controller.hpp"
#include "event_manager.hpp"

int main(int argc, char *argv[])
{
    Game game;
    game.world.terrain.create(30, 20);
    for (int y = 0; y < game.world.terrain.getHeight(); ++y)
    {
        for (int x = 0; x < game.world.terrain.getWidth(); ++x)
        {
            if (x == 0 || x + 1 == game.world.terrain.getWidth() ||
                y == 0 || y + 1 == game.world.terrain.getHeight())
            {
                game.world.terrain.set(Tile(1), Terrain::Ground::Back, x, y);
            }
        }
    }

    game.world.characters.push_back(std::move(std::unique_ptr<Character>(new Character())));
    game.world.characters.front()->body.position = Vector2f(2.f, 4.f);
    game.world.characters.front()->body.size = Vector2f(0.95, 1.95);

    Window window(640, 480, "squarevilles");
    window.setTileSize(sf::Vector2u(8, 8));
    window.setZoom(4);

    Physic physic;
    physic.setGravity(Vector2f(0.f, 4.5f));
    physic.setMaxResolutions(5);
    physic.setUpdateStep(0.033);// ~30 updates/second

    Controller controller;

    game.add(window);
    game.add(physic);
    game.add(controller);

    game.runLoop();    
}
