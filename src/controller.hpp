#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP

#include <string>

#include "physic.hpp"
#include "game.hpp"

class Controller : public Module
{
    public:
        //load infos files and set everything
        Controller();

        virtual void update(World &world, bool &quit);

        void placeOnGround(const TileCollision &col);

    private:
        bool loadTilesInfos(const std::string &filename);
        bool loadCharactersInfos(const std::string &filename);
};

#endif
