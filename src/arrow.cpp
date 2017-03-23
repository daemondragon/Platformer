#include "arrow.hpp"

#include "character.hpp"

void Arrow::hit(Character &character)
{
    character.kill();
}
