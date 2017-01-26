#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP

class Character;

//a controller can be anything : a keyboard, a gamepads, an AI..
class Controller
{
    public:
        virtual void update(Character &character) = 0;
};

#endif
