#ifndef PHYSIC_HPP
#define PHYSIC_HPP

#include <queue>

#include "game.hpp"

class Collision
{
    public:
        enum class Axis
        {
            X, Y
        };

        Collision(Character &character, const Vector2f &tile_position,
                  Axis axis, float penetration);

        friend bool operator<(const Collision &c1, const Collision &c2);

        Axis        axis;
        Character   *character;
        Vector2f    tile_position;
        float       penetration;
};

class Physic : public Module
{
    public:
        Physic();

        //max resolutions per body
        void            setMaxResolutions(unsigned char max);
        unsigned char   getMaxResolutions() const;
        void            setGravity(const Vector2f &gravity);
        Vector2f        getGravity() const;
        void            setUpdateStep(float step);
        float           getUpdateStep() const;

        void            update(World &world, bool &quit);

        bool            collide(const RigidBody &b1, const RigidBody &b2);
    private:
        void            update(RigidBody &body, float delta_time);
        void            clearAccumulators(RigidBody &body);

        //Only background are used for physic
        std::priority_queue<Collision>  generateCollisions(const Terrain &terrain, Character &body);
        void                            resolve(std::priority_queue<Collision> collisions);
        void                            resolve(const Collision &collision);

        static float    getPenetrationOnXAxis(const RigidBody &b1, const RigidBody &b2);
        static float    getPenetrationOnYAxis(const RigidBody &b1, const RigidBody &b2);
        

        Vector2f        gravity;
        //Never try to correct more than max_resolutions collisions per frames, even if they are no longer valid
        unsigned char   max_resolutions;
        float           update_step;
        float           remaining_time;
};

#endif
