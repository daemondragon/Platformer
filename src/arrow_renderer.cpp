#include "arrow_renderer.hpp"

void ArrowRenderer::loadTextures()
{
    textures.load("data/images/character/arrows.png", 0);
}

void ArrowRenderer::render(sf::RenderWindow &screen, sf::Vector2u tile_size, World &world)
{
    for (auto &arrow : world.arrows)
    {
        Vector2f direction = (arrow->body.velocity.squareLength() > 0 ? arrow->body.velocity.normalized() : Vector2f(0, 0));

        sf::Sprite sprite;
        sf::Texture texture = textures.get(0);

        sprite.setTexture(texture);
        sprite.setOrigin(texture.getSize().x, texture.getSize().y / 2);
        sprite.rotate(arrow->body.velocity.y < 0 ? 360 - 57.2957795131 * std::acos(direction.x) :
                                                         57.2957795131 * std::acos(direction.x));
        sprite.setPosition(arrow->body.position.x * tile_size.x,
                           arrow->body.position.y * tile_size.y);

        screen.draw(sprite);
    }
}
