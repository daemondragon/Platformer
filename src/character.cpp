#include "character.hpp"

#include "character_actions.hpp"

CharacterInfos::CharacterInfos() : move_velocity(1.f), jump_velocity(3.f)
{
}

Character::Character() : direction(Direction::Right), on_ground(true), is_dead(false)
{
    body.size = Vector2f(0.95, 1.95);
}

void Character::perform(const Action &action)
{
    action.perform(*this);
}

bool Character::isDead() const
{
    return (is_dead);
}

void Character::kill()
{
    is_dead = true;
}
