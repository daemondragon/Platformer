#ifndef BOW_HPP
#define BOW_HPP

#include <memory>
#include <list>

#include "arrow.hpp"

class Bow
{
    public:
                                Bow();

        void                    rotateQuiver();

        enum class Direction
        {
            Top         = 0x01,
            Front       = 0x02,
            Bottom      = 0x04,
            TopFront    = 0x03,
            BottomFront = 0x06,
        };

        Direction                           direction;
        std::list<std::unique_ptr<Arrow>>   arrows;
};

#endif
