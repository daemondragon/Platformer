#ifndef PHYSIC_HPP
#define PHYSIC_HPP

#include <queue>

#include "game.hpp"

class TileCollision
{
    public:
        enum class Axis
        {
            X, Y
        };

        TileCollision(Character &character, const Vector2f &tile_position,
                  Axis axis, float penetration);

        friend bool operator<(const TileCollision &c1, const TileCollision &c2);

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
    private:
        void            update(RigidBody &body, float delta_time) const;
        void            move(World &world, float delta_time) const;
        void            resolveCollisions(World &world) const;
        void            clearAllAccumulators(World &world) const ;

        //Only foreground are used for physic (if tile.id != 0 -> solid)
        std::priority_queue<TileCollision>  generateCollisions(const Terrain &terrain, Character &body) const;
        void                                resolve(std::priority_queue<TileCollision> collisions) const;
        void                                resolve(const TileCollision &collision) const;

        Vector2f        gravity;
        //Never try to correct more than max_resolutions collisions per frames, even if they are no longer valid
        unsigned char   max_resolutions;
        float           update_step;
        float           remaining_time;
};

#endif
