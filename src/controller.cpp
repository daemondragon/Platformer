#include "controller.hpp"

#include <iostream>
#include <fstream>

#include "event_manager.hpp"
#include "parser.hpp"

Controller::Controller()
{
    loadCharactersInfos("data/infos/characters.txt");

    EventManager<TileCollision>::addListener([this](const TileCollision &col){this->placeOnGround(col);});
}

bool Controller::loadCharactersInfos(const std::string &filename)
{
    std::ifstream file(filename, std::ifstream::in);
    if (!file.is_open())
    {
        std::cout << "Can't open " << filename << " for parsing" << std::endl;
        return (false);
    }
    else
        std::cout << "Opened " << filename << " for parsing" << std::endl;

    Character::clearAllInfos();

    Parser parser('#', '[', ']');

    CharacterInfos infos;
    unsigned short current_id = 0;

    std::string line;
    while (std::getline(file, line))
    {
        std::string key;
        std::string value;

        if (parser.parseLine(line, key, value))
        {
            try
            {
                if (key == "ID")
                {
                        Character::setInfosFor(infos, current_id);
                        current_id = std::stoi(value);
                        infos = CharacterInfos();
                }
                else if (key == "MOVE_VELOCITY")
                    infos.move_velocity = std::stof(value);
                else if (key == "JUMP_VELOCITY")
                     infos.jump_velocity = std::stof(value);
                else
                     std::cout << "Warning while parsing: " << key << " isn't a key" << std::endl;                   
            }
            catch (std::exception &e)
            {
                std::cout << "Error while parsing " << filename << "->" << key << ": " << e.what() << std::endl;
            }
        }
    }
    Character::setInfosFor(infos, current_id);

    return (true);
}

void Controller::update(World &world, bool &quit)
{
}

void Controller::placeOnGround(const TileCollision &col)
{
    if (col.character && col.axis == TileCollision::Axis::Y && col.tile_position.y > col.character->body.position.y)
        col.character->on_ground = true;
}
