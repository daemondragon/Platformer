#ifndef TILE_HPP
#define TILE_HPP

#include "object.hpp"

class TileInfos
{
    public:
        TileInfos();

        bool    solid;
        bool    transparent;
};

class Tile : public Object<TileInfos>
{
    public:
        Tile(unsigned short id = 0);

    private:
};

#endif
