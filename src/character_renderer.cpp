#include "character_renderer.hpp"

void CharacterRenderer::loadTextures()
{

}

void CharacterRenderer::render(sf::RenderWindow &screen, sf::Vector2u tile_size, World &world)
{
    for (auto &character : world.characters)
    {
        sf::RectangleShape rectangle(sf::Vector2f(tile_size.x * character->body.size.x,
                                                  tile_size.y * character->body.size.y));
        rectangle.setFillColor(sf::Color(0, 255, 0));
        rectangle.setPosition(character->body.position.x * tile_size.x,
                              character->body.position.y * tile_size.y);
        screen.draw(rectangle);

        sf::CircleShape aim(tile_size.x / 8);
        aim.setFillColor(sf::Color(255, 0, 0));

        sf::Vector2f relative_position;
        if ((int)Bow::Direction::Top & (int)character->bow.direction)
            relative_position.y = -1.f;
        else if ((int)Bow::Direction::Bottom & (int)character->bow.direction)
            relative_position.y = 1.f;

        if ((int)Bow::Direction::Front & (int)character->bow.direction)
            relative_position.x = (character->direction == Character::Direction::Left ? -1.f : 1.f);

        aim.setPosition((character->body.position.x + character->body.size.x / 2 + relative_position.x) * tile_size.x,
                        (character->body.position.y + character->body.size.y / 2 + relative_position.y) * tile_size.y);

        screen.draw(aim);
    }
}
