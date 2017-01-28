#include "sfml_controller.hpp"

#include "character_actions.hpp"

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

void KeyboardController::update(Character &character)
{
    if (!sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {//Move
        character.perform(StopAim());

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            character.perform(Move(Character::Direction::Left));
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            character.perform(Move(Character::Direction::Right));
    }
    else
    {//Aim
        Vector2f direction;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            direction.x -= 1.f;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            direction.x += 1.f;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            direction.y -= 1.f;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            direction.y += 1.f;

        character.perform(Aim(direction));
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        character.perform(Jump());
}

GamepadController::GamepadController(unsigned short id, float threshold) : id(id), threshold(threshold)
{
}

void GamepadController::update(Character &character)
{
    if (!sf::Joystick::isConnected(id))
        return;

    if (!sf::Joystick::isButtonPressed(id, 1))
    {//Move
        character.perform(StopAim());

        float direction = sf::Joystick::getAxisPosition(id, sf::Joystick::Axis::X) / 100.f;
        if (std::abs(direction) >= threshold)
            character.perform(Move(direction < 0.f ? Character::Direction::Left :
                                                     Character::Direction::Right));
    }
    else
    {//Aim
        Vector2f aim_direction(sf::Joystick::getAxisPosition(id, sf::Joystick::Axis::X),
                               sf::Joystick::getAxisPosition(id, sf::Joystick::Axis::Y));
        if (passThreshold(aim_direction))
            character.perform(Aim(aim_direction));   
    }

    if (sf::Joystick::isButtonPressed(id, 0))
        character.perform(Jump());
}

bool GamepadController::passThreshold(const Vector2f &input_axis)
{
    return (std::abs(input_axis.x / 100.f) >= threshold ||
            std::abs(input_axis.y / 100.f) >= threshold);
}

