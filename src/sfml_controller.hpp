#ifndef SFML_CONTROLLER_HPP
#define SFML_CONTROLLER_HPP

#include "character.hpp"

class KeyboardController : public Controller
{
    public:
        virtual void    update(Character &character);
};

class GamepadController : public Controller
{
    public:
                        //threshold [0.f:1.f], usually 0.5, lower is more sensitive
                        GamepadController(unsigned short id, float threshold = 0.5f);
        virtual void    update(Character &character);

    protected:
        bool            passThreshold(const Vector2f &input_axis);

        unsigned short  id;
        float           threshold;
};

#endif
