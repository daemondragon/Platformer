#include "character.hpp"

#include "character_actions.hpp"

CharacterInfos::CharacterInfos() : move_velocity(1.f), jump_velocity(3.f)
{
}

Character::Character() : direction(Direction::Right), on_ground(true)
{
    body.size = Vector2f(0.95, 1.95);
}

void Character::perform(const Action &action)
{
    action.perform(*this);
}
