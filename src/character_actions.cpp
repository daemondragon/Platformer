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

void FireArrow::perform(Character &character) const
{
    if (character.bow.arrows.empty())
        return;

    std::unique_ptr<Arrow> arrow = std::move(character.bow.arrows.front());
    character.bow.arrows.pop_front();
    
    arrow->body.position = character.body.position;
    if ((int)character.bow.direction & (int)Bow::Direction::Top)
        arrow->body.velocity.y = -1.f;
    else if ((int)character.bow.direction & (int)Bow::Direction::Bottom)
        arrow->body.velocity.y = -1.f;
    else
        arrow->body.velocity.y = 0;

    if ((int)character.bow.direction & (int)Bow::Direction::Front)
        arrow->body.velocity.x = (character.direction == Character::Direction::Left ? -1 : 1);
    else
        arrow->body.velocity.x = 0;

    arrow->body.velocity.normalize();
}

