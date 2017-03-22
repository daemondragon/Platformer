#ifndef WORLD_HPP
#define WORLD_HPP

#include <memory>
#include <list>

#include "character.hpp"
#include "terrain.hpp"
#include "arrow.hpp"

class World
{
    public:
        float   delta_time;

        Terrain terrain;
        std::list<std::unique_ptr<Character>>   characters;
        std::list<std::unique_ptr<Arrow>>       arrows;
};

#endif
