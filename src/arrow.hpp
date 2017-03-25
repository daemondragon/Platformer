#ifndef ARROW_HPP
#define ARROW_HPP

#include "rigid_body.hpp"

class Character;

class Arrow
{
    public:
        virtual void    hit(Character &character);

        RigidBody       body;
        Vector2f        previous_velocity;
};

#endif
