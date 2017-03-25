#include "HUD_renderer.hpp"

void HUDRenderer::loadTextures()
{
    textures.load("data/images/character/arrows.png", 0);
}

void HUDRenderer::render(sf::RenderWindow &screen, sf::Vector2u tile_size, World &world)
{
    sf::Sprite sprite;
    sf::Texture texture = textures.get(0);
    Vector2f arrow_size(texture.getSize().x / 2, texture.getSize().y / 2);
    sprite.setTexture(texture);
    sprite.setOrigin(arrow_size.x * 2, arrow_size.y * 2);
    sprite.rotate(90);
    sprite.scale(0.5f, 0.5f);

    for (auto &character : world.characters)
    {
        int nb_arrows = character->bow.arrows.size();
        Vector2f offset((character->body.position.x + character->body.size.x / 2) * tile_size.x - (nb_arrows / 2 + (nb_arrows % 2 == 0 ? 1 : 1.5f)) * arrow_size.x,
                         character->body.position.y * tile_size.y - arrow_size.y);

        for (int i = 0; i < nb_arrows; ++i)
        {
            sprite.setPosition(offset.x + i * arrow_size.x, offset.y);
            screen.draw(sprite);
        }
    }
}
