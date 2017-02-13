#include "logic.hpp"

#include <iostream>
#include <fstream>

#include "event_manager.hpp"
#include "parser.hpp"

Logic::Logic()
{
    loadCharactersInfos("data/infos/characters.txt");

    EventManager<TileCollision>::addListener([this](const TileCollision &col){this->placeOnGround(col);});
    EventManager<CharactersCollision>::addListener([this](const CharactersCollision &col){this->stomp(col);});
}

bool Logic::loadCharactersInfos(const std::string &filename)
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

void Logic::update(World &world, bool &quit)
{
    removeDeadCharacters(world);

    for (auto &character : world.characters)
        if (character->controller)
            character->controller->update(*character);
}

void Logic::removeDeadCharacters(World &world)
{
    for (auto it = world.characters.begin(); it != world.characters.end();)
    {
        if ((*it)->isDead())
        {
            //raise event ?
            it = world.characters.erase(it);
        }
        else
             ++it;
    }
}

void Logic::placeOnGround(const TileCollision &col)
{
    if (col.character && col.axis == Collisions::Axis::Y && col.tile_position.y > col.character->body.position.y)
        col.character->on_ground = true;
}

void Logic::stomp(const CharactersCollision &col)
{
    if (col.axis == Collisions::Axis::Y)
    {
        if (col.c1->body.position.y < col.c2->body.position.y)
        {
            col.c2->kill();
            col.c1->body.velocity.y -= col.c1->getInfos().jump_velocity;
        }
        else
        {
            col.c1->kill();
            col.c2->body.velocity.y -= col.c2->getInfos().jump_velocity;
        }
    }
}
