#include "character_renderer.hpp"

#include "event_manager.hpp"

CharacterRenderer::CharacterRenderer()
{
    EventManager<DeadCharacter>::addListener([this](const DeadCharacter &dead){this->addDeadCharacter(dead);});
}

void CharacterRenderer::loadTextures()
{
    textures.load("data/images/character/death.png", 0);
}

void CharacterRenderer::addDeadCharacter(const DeadCharacter &character)
{
    dead_characters.push_back(std::pair<sf::Vector2f, float>(
        sf::Vector2f(character.character->body.position.x, character.character->body.position.y),
        character.respawn_time));
}

void CharacterRenderer::update(float delta_time)
{
    for (auto it = dead_characters.begin(); it != dead_characters.end();)
    {
        (*it).second -= delta_time;

        if ((*it).second <= 0.f)
            it = dead_characters.erase(it);
        else
            ++it;
    }
}

void CharacterRenderer::render(sf::RenderWindow &screen, sf::Vector2u tile_size, World &world)
{
    renderCharacters(screen, tile_size, world);
    renderDeadCharacters(screen, tile_size, world);
}

void CharacterRenderer::renderDeadCharacters(sf::RenderWindow &screen, sf::Vector2u tile_size, World &world)
{
    sf::Sprite sprite;
    sf::Texture texture = textures.get(0);
    sprite.setTexture(texture);
    int nb_frames = texture.getSize().x / texture.getSize().y;

    for (auto &it : dead_characters)
    {
        int nb = (int)((it.second / 2.5f) * nb_frames) % nb_frames;
        sprite.setTextureRect(sf::IntRect(nb * texture.getSize().y, 0, texture.getSize().y, texture.getSize().y));
        sprite.setPosition(it.first.x * tile_size.x, it.first.y * tile_size.y);

        screen.draw(sprite);
    }
}

void CharacterRenderer::renderCharacters(sf::RenderWindow &screen, sf::Vector2u tile_size, World &world)
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
