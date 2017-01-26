#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include <memory>

#include "controller.hpp"
#include "rigid_body.hpp"
#include "bow.hpp"
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

        void                        perform(const Action &action);

        RigidBody                   body;
        Direction                   direction;
        bool                        on_ground;
        Bow                         bow;

        std::shared_ptr<Controller> controller;
};

#endif
