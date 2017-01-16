#include "collisions.hpp"

namespace Collisions
{

float getPenetrationOnXAxis(const RigidBody &b1, const RigidBody &b2)
{
    if (b1.position.x < b2.position.x)
    {
        float result = b2.position.x - b1.position.x - b1.size.x;
        return (result < 0.f ? result : 0.f);
    }
    else
    {
        float result = b1.position.x - b2.position.x - b2.size.x;
        return (result < 0.f ? result : 0.f);
    }
}

float getPenetrationOnYAxis(const RigidBody &b1, const RigidBody &b2)
{
    if (b1.position.y < b2.position.y)
    {
        float result = b2.position.y - b1.position.y - b1.size.y;
        return (result < 0.f ? result : 0.f);
    }
    else
    {
        float result = b1.position.y - b2.position.y - b2.size.y;
        return (result < 0.f ? result : 0.f);
    }
}

bool collide(const RigidBody &b1, const RigidBody &b2)
{
    return (getPenetrationOnXAxis(b1, b2) != 0.f &&
            getPenetrationOnYAxis(b1, b2) != 0.f);
}

//Both followinf function don't check if the body body collide. If not, body are moved as if there was one.
//Both body can be moved to correct the collision
void resolveWithDynamic(RigidBody &b1, RigidBody &b2)
{
    Vector2f    penetration(getPenetrationOnXAxis(b1, b2),
                            getPenetrationOnYAxis(b1, b2));

    if (penetration.x > penetration.y)
    {// X axis collision
        float center_x = (b1.position.x + b2.position.x) * 0.5f;
        if (b1.position.x < b2.position.x)
        {
            b1.position.x = center_x - b1.size.x;
            b2.position.x = center_x;
        }
        else
        {
            b1.position.x = center_x;
            b2.position.x = center_x - b2.size.x;
        }
        b1.velocity.x = b2.velocity.x = (b1.velocity.x + b2.velocity.x) * 0.5f;
    }
    else
    {// Y axis collision
        float center_y = (b1.position.y + b2.position.y) * 0.5f;
        if (b1.position.y < b2.position.y)
        {
            b1.position.y = center_y - b1.size.y;
            b2.position.y = center_y;
        }
        else
        {
            b1.position.y = center_y;
            b2.position.y = center_y - b2.size.y;
        }

        b1.velocity.y = b2.velocity.y = (b1.velocity.y + b2.velocity.y) * 0.5f;
    }
}

//Only the first body can be moved to correct the collision
void resolveWithStatic(RigidBody &b1, const RigidBody &b2)
{
    Vector2f    penetration(getPenetrationOnXAxis(b1, b2),
                            getPenetrationOnYAxis(b1, b2));

    if (penetration.x > penetration.y)
    {// X axis collision
        if (b1.position.x < b2.position.x)
            b1.position.x = b2.position.x - b1.size.x;
        else
            b1.position.x = b2.position.x + b2.size.x;

        b1.velocity.x = 0.f;
    }
    else
    {// Y axis collision
        if (b1.position.y < b2.position.y)
            b1.position.y = b2.position.y - b1.size.y;
        else
            b1.position.y = b2.position.y + b2.size.y;

        b1.velocity.y = 0.f;
    }
}

}
