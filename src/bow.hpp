#ifndef BOW_HPP
#define BOW_HPP

#include <list>

class Bow
{
    public:
        Bow();

        enum class Direction
        {
            Top         = 0x01,
            Front       = 0x02,
            Bottom      = 0x04,
            TopFront    = 0x03,
            BottomFront = 0x06,
        };
        
        Direction   direction;
};

#endif
