#include "character_actions.hpp"

void Jump::perform(Character &character) const
{
    if (character.on_ground)
    {
        character.body.velocity.y -= character.getInfos().jump_velocity;
        character.on_ground = false;
    }
}

Move::Move(Character::Direction direction) : direction(direction)
{
}

void Move::perform(Character &character) const
{
    character.direction = direction;
    character.body.temp_velocity.x += (direction == Character::Direction::Left ?
        -character.getInfos().move_velocity :
         character.getInfos().move_velocity);
}
