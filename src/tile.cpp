#include "tile.hpp"

Tile::Tile(unsigned short id) : id(id)
{
}

bool Tile::isSolid() const
{
    return (id != 0);
}
