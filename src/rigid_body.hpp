#ifndef RIGID_BODY_HPP
#define RIGID_BODY_HPP

#include "vector2.hpp"

class RigidBody
{
    public:
        Vector2f    position;//Top Left position
        Vector2f    size;

        Vector2f    velocity;
        Vector2f    acceleration;

        Vector2f    temp_velocity;//velocity that last only one frame

        void        clearAccumulators()
        {
            temp_velocity.clear();
        }
};

#endif
