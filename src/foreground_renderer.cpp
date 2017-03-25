#include "foreground_renderer.hpp"

void ForegroundRenderer::loadTextures()
{
    textures.load("data/images/foreground/0.png", 0);
    textures.load("data/images/foreground/1.png", 1);
    textures.load("data/images/foreground/2.png", 2);
    textures.load("data/images/foreground/3.png", 3);
    textures.load("data/images/foreground/4.png", 4);
}

void ForegroundRenderer::render(sf::RenderWindow &screen, sf::Vector2u tile_size, World &world)
{
    sf::Sprite sprite;
    sf::Texture texture = textures.get(world.terrain.getWorldType());

    sprite.setTexture(texture);
    int nb_tiles_width = texture.getSize().x / tile_size.x;

    for (int y = 0; y < world.terrain.getHeight(); ++y)
    {
        for (int x = 0; x < world.terrain.getWidth(); ++x)
        {
            Tile tile = world.terrain.get(Terrain::Ground::Fore, x, y);
            if (tile.id)
            {
                sprite.setTextureRect(sf::IntRect(tile.id % nb_tiles_width * tile_size.x,
                                                  tile.id / nb_tiles_width * tile_size.y,
                                                  tile_size.x, tile_size.y));
                sprite.setPosition(x * tile_size.x, y * tile_size.y);
                screen.draw(sprite);
            }
        }
    }
}
