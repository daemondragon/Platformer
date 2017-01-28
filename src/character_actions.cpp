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

Aim::Aim(Vector2f direction)
{
    if (direction.x == 0.f && direction.y == 0.f)
        return;

    direction.normalize();
    float ratio = std::abs(direction.x / direction.y);
    if (ratio < 0.5 || ratio > 2.5)
    {
        global_direction = (direction.x < 0.f ? Character::Direction::Left :
                                                Character::Direction::Right);
        if (std::abs(direction.x) > std::abs(direction.y))
            local_direction = Bow::Direction::Front;
        else   
            local_direction = (direction.y < 0.f ? Bow::Direction::Top :
                                                   Bow::Direction::Bottom);
    }
    else
    {//Diagonal
        global_direction = (direction.x < 0.f ? Character::Direction::Left :
                                               Character::Direction::Right);
        local_direction = (direction.y < 0.f ? Bow::Direction::TopFront :
                                               Bow::Direction::BottomFront);
    }

}

void Aim::perform(Character &character) const
{
    character.direction = global_direction;
    character.bow.direction = local_direction;
}
