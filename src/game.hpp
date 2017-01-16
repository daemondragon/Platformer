#ifndef MODULE_HPP
#define MODULE_HPP

#include <vector>

#include "world.hpp"

class Module
{
    public:
        virtual void update(World &world, bool &quit) = 0;
};

class Game
{
    public:
        void    add(Module &module);
        void    runLoop();

        World   world;

    private:
        std::vector<Module*>    modules;
};

#endif
