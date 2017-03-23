#include "bow.hpp"

Bow::Bow() : direction(Bow::Direction::Front)
{
}

void Bow::rotateQuiver()
{
    if (arrows.size() <= 0)
        return;

    arrows.push_back(std::move(arrows.front()));
    arrows.pop_front();
}
