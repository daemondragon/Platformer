#ifndef CHARACTER_RENDERER_HPP
#define CHARACTER_RENDERER_HPP

#include "window.hpp"

class CharacterRenderer : public Renderer
{
    public:
        virtual void loadTextures();
        virtual void render(sf::RenderWindow &screen, sf::Vector2u tile_size, World &world);
};

#endif
