#ifndef LOGIC_HPP
#define LOGIC_HPP

#include <string>

#include "physic.hpp"
#include "game.hpp"

//Handle all the game logic
class Logic : public Module
{
    public:
        //load infos files and set everything
        Logic();

        virtual void update(World &world, bool &quit);

    private:
        void removeDeadCharacters(World &world);
    
        void placeOnGround(const TileCollision &col);
        void stomp(const CharactersCollision &col);
    
        bool loadTilesInfos(const std::string &filename);
        bool loadCharactersInfos(const std::string &filename);
};

#endif
