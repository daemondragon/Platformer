#ifndef CHARACTER_ACTIONS_HPP
#define CHARACTER_ACTIONS_HPP

#include "character.hpp"

class Action
{
    public:
        virtual void perform(Character &character) const = 0;
};

class Jump : public Action
{
    public:
        virtual void perform(Character &character) const;
};

class Move : public Action
{
    public:
        Move(Character::Direction direction);

        virtual void perform(Character &character) const;
    private:
        Character::Direction direction;
};

class Aim : public Action
{
    public:
        Aim(const Vector2f &direction);

        virtual void perform(Character &character) const;

    private:
        Vector2f direction;
};

class StopAim : public Action
{
    public:
        virtual void perform(Character &character) const;
};
#endif
