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

Aim::Aim(const Vector2f &direction)
{
    if (direction.x != 0.f || direction.y != 0.f)
        this->direction = direction.normalized();
}

void Aim::perform(Character &character) const
{
    if (direction.x == 0.f && direction.y == 0.f)
    {
        character.bow.direction = Bow::Direction::Front;
        return;
    }

    float ratio = std::abs(direction.x / direction.y);
    if (ratio < 0.5 || ratio > 2.5)
    {
        character.direction = (direction.x < 0.f ? Character::Direction::Left :
                                                   Character::Direction::Right);
        if (std::abs(direction.x) > std::abs(direction.y))
            character.bow.direction = Bow::Direction::Front;
        else   
            character.bow.direction = (direction.y < 0.f ? Bow::Direction::Top :
                                                           Bow::Direction::Bottom);
    }
    else
    {//Diagonal
        character.direction = (direction.x < 0.f ? Character::Direction::Left :
                                                   Character::Direction::Right);
        character.bow.direction = (direction.y < 0.f ? Bow::Direction::TopFront :
                                                       Bow::Direction::BottomFront);
    }
}

void StopAim::perform(Character &character) const
{
    character.bow.direction = Bow::Direction::Front;
}

