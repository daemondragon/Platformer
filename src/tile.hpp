#ifndef TILE_HPP
#define TILE_HPP

class Tile
{
    public:
        Tile(unsigned short id = 0);

        bool    isSolid() const;

        unsigned short id;
};

#endif
