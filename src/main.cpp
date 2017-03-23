#include <iostream>

#include "parser.hpp"
#include "terrain.hpp"
#include "game.hpp"
#include "world.hpp"
#include "window.hpp"
#include "physic.hpp"
#include "logic.hpp"
#include "event_manager.hpp"
#include "sfml_controller.hpp"

int main(int argc, char *argv[])
{
    Game game;

    game.world.terrain.create(30, 20);
    game.world.terrain.setWorldType(2);
    for (int y = 0; y < game.world.terrain.getHeight(); ++y)
    {
        for (int x = 0; x < game.world.terrain.getWidth(); ++x)
        {
            if (x == 0 || x + 1 == game.world.terrain.getWidth() ||
                y == 0 || y + 1 == game.world.terrain.getHeight())
            {
                game.world.terrain.set(Tile(1), Terrain::Ground::Fore, x, y);
            }
        }
    }
    //if (!game.world.terrain.save("test.ct"))
        //std::cout << "failed saving" << std::endl;

    std::shared_ptr<KeyboardController> keyboard(new KeyboardController());
    std::shared_ptr<GamepadController> gamepad(new GamepadController(0));

    game.world.characters.push_back(std::move(std::unique_ptr<Character>(new Character())));
    game.world.characters.front()->body.position = Vector2f(2.f, 4.f);
    game.world.characters.front()->body.size = Vector2f(0.95, 1.95);
    game.world.characters.front()->controller = gamepad;
    game.world.characters.front()->bow.arrows.push_back(std::move(std::unique_ptr<Arrow>(new Arrow())));

    game.world.characters.push_front(std::move(std::unique_ptr<Character>(new Character())));
    game.world.characters.front()->body.position = Vector2f(5.f, 3.f);
    game.world.characters.front()->body.size = Vector2f(0.95, 1.95);
    game.world.characters.front()->controller = keyboard;
    game.world.characters.front()->bow.arrows.push_back(std::move(std::unique_ptr<Arrow>(new Arrow())));

    Window window(640, 480, "squarevilles");
    window.setTileSize(sf::Vector2u(16, 16));
    window.setDesiredFPS(120);
    window.setZoom(2);

    Physic physic;
    physic.setGravity(Vector2f(0.f, 9.81f));
    physic.setMaxResolutions(5);
    physic.setUpdateStep(0.033);// ~30 updates/second

    Logic logic;

    game.add(window);
    game.add(physic);
    game.add(logic);

    game.runLoop();
}
