#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include "rigid_body.hpp"
#include "object.hpp"

class Action;

class CharacterInfos
{
    public:
        CharacterInfos();

        float   move_velocity;
        float   jump_velocity;
};

class Character : public Object<CharacterInfos>
{
    public:
        enum class Direction
        {
            Left,
            Right
        };

        Character();

        void        perform(const Action &action);

        RigidBody   body;
        Direction   direction;
        bool        on_ground;
};

#endif
