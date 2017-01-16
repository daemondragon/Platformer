#ifndef COLLISIONS_HPP
#define COLLISIONS_HPP

#include "rigid_body.hpp"

namespace Collisions
{

float   getPenetrationOnXAxis(const RigidBody &b1, const RigidBody &b2);
float   getPenetrationOnYAxis(const RigidBody &b1, const RigidBody &b2);

bool    collide(const RigidBody &b1, const RigidBody &b2);

//Both followinf function don't check if the body body collide. If not, body are moved as if there was one.
//Both body can be moved to correct the collision
void    resolveWithDynamic(RigidBody &b1, RigidBody &b2);
//Only the first body can be moved to correct the collision
void    resolveWithStatic(RigidBody &b1, const RigidBody &b2);

}

#endif
