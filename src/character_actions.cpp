#include "character_actions.hpp"

#include "event_manager.hpp"
#include "logic.hpp"

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

    FiredArrow fired_arrow;
    fired_arrow.arrow = std::move(character.bow.arrows.front());
    character.bow.arrows.pop_front();

    if ((int)character.bow.direction & (int)Bow::Direction::Top)
        fired_arrow.arrow->body.velocity.y = -1.f;
    else if ((int)character.bow.direction & (int)Bow::Direction::Bottom)
        fired_arrow.arrow->body.velocity.y = 1.f;
    else
        fired_arrow.arrow->body.velocity.y = 0;

    if ((int)character.bow.direction & (int)Bow::Direction::Front)
        fired_arrow.arrow->body.velocity.x = (character.direction == Character::Direction::Left ? -1 : 1);
    else
        fired_arrow.arrow->body.velocity.x = 0;

    fired_arrow.arrow->body.velocity.normalize();
    fired_arrow.arrow->body.velocity *= 10;


    fired_arrow.arrow->body.position = character.body.position + character.body.size * 0.5f;
    if (fired_arrow.arrow->body.velocity.x < 0.f)
        fired_arrow.arrow->body.position.x -= character.body.size.x;
    else if (fired_arrow.arrow->body.velocity.x > 0.f)
        fired_arrow.arrow->body.position.x += character.body.size.x;

    if (fired_arrow.arrow->body.velocity.y < 0.f)
        fired_arrow.arrow->body.position.y -= character.body.size.y;
    else if (fired_arrow.arrow->body.velocity.y > 0.f)
        fired_arrow.arrow->body.position.y += character.body.size.y;

    EventManager<FiredArrow>::fire(fired_arrow);
}

