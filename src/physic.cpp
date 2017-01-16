#include "physic.hpp"

#include "event_manager.hpp"

Collision::Collision(Character &character, const Vector2f &tile_position, Axis axis, float penetration) :
    axis(axis), character(&character), tile_position(tile_position), penetration(penetration)
{
}

bool operator<(const Collision &c1, const Collision &c2)
{
    return (c1.penetration < c2.penetration);
}

Physic::Physic() : 
    gravity(Vector2f(0.f, 9.81f)), max_resolutions(3), update_step(0.016f), remaining_time(0.f)
{
}

void Physic::setMaxResolutions(unsigned char max)
{
    if (max <= 0)
        max = 1;

    max_resolutions = max;
}

unsigned char Physic::getMaxResolutions() const
{
    return (max_resolutions);
}

void Physic::setGravity(const Vector2f &gravity)
{
    this->gravity = gravity;
}

Vector2f Physic::getGravity() const
{
    return (gravity);
}

void Physic::setUpdateStep(float step)
{
    update_step = step <= 0.f ? 0.016f : step;
}

float Physic::getUpdateStep() const
{
    return (update_step);
}

void Physic::update(World &world, bool &quit)
{
    remaining_time += world.delta_time;
    while (remaining_time >= update_step)
    {
        for (auto &character : world.characters)
        {
            update(character->body, update_step);
            resolve(generateCollisions(world.terrain, *character));
        }

        remaining_time -= update_step;
    }

    for (auto &character : world.characters)
        clearAccumulators(character->body);
}

void Physic::update(RigidBody &body, float delta_time)
{
    body.position += (body.velocity + body.temp_velocity) * delta_time +
                     body.acceleration * delta_time * delta_time * 0.5;
    //adding acceleration to position to have a better movement over irregulate frames
    body.velocity += (body.acceleration + gravity) * delta_time;
}

void Physic::clearAccumulators(RigidBody &body)
{
    body.temp_velocity.clear();
}

bool Physic::collide(const RigidBody &b1, const RigidBody &b2)
{
    return (getPenetrationOnXAxis(b1, b2) != 0.f &&
            getPenetrationOnYAxis(b1, b2) != 0.f);
}

std::priority_queue<Collision> Physic::generateCollisions(const Terrain &terrain, Character &character)
{
    std::priority_queue<Collision> collisions;

    RigidBody tile;
    tile.size = Vector2f(1.f, 1.f);

    Vector2f start = character.body.position;
    Vector2f end = character.body.position + character.body.size;

    for (int y = start.y; y <= end.y; ++y)
    {
        for (int x = start.x; x <= end.x; ++x)
        {
            if (terrain.isInside(x, y) &&
                terrain.get(Terrain::Ground::Back, x, y).getInfos().solid)
            {
                tile.position = Vector2f(x, y);

                Vector2f penetration(getPenetrationOnXAxis(character.body, tile),
                                     getPenetrationOnYAxis(character.body, tile));

                if (penetration.x < 0.f && penetration.y < 0.f)
                {
                    collisions.push(Collision(character,
                                              tile.position,
                                              penetration.x > penetration.y ?
                                                  Collision::Axis::X : Collision::Axis::Y,
                                              std::abs(penetration.x * penetration.y)));
                }
            }
        }
    }
    return (collisions);
}

void Physic::resolve(std::priority_queue<Collision> collisions)
{
    unsigned char nb_resolutions = 0;

    while (!collisions.empty() && nb_resolutions < max_resolutions)
    {
        resolve(collisions.top());
        collisions.pop();
        ++nb_resolutions;
    }
}

void Physic::resolve(const Collision &collision)
{
    RigidBody tile;
    tile.size = Vector2f(1.f, 1.f);
    tile.position = collision.tile_position;

    if (!collision.character || !collide(collision.character->body, tile))
        return;

    if (collision.axis == Collision::Axis::X)
    {
        if (collision.character->body.position.x < collision.tile_position.x)
            collision.character->body.position.x =
                (int)(collision.character->body.position.x + collision.character->body.size.x) -
                    collision.character->body.size.x;
        else
            collision.character->body.position.x = (int)(collision.character->body.position.x + 1);

        collision.character->body.velocity.x = 0.f;
    }
    else
    {
        if (collision.character->body.position.y < collision.tile_position.y)
            collision.character->body.position.y =
                (int)(collision.character->body.position.y + collision.character->body.size.y) -
                    collision.character->body.size.y;
        else
            collision.character->body.position.y = (int)(collision.character->body.position.y + 1);

        collision.character->body.velocity.y = 0.f;
    }

    EventManager<Collision>::fire(collision);
}

float Physic::getPenetrationOnXAxis(const RigidBody &b1, const RigidBody &b2)
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

float Physic::getPenetrationOnYAxis(const RigidBody &b1, const RigidBody &b2)
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

