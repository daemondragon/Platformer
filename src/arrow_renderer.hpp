#ifndef ARROW_RENDERER_HPP
#define ARROW_RENDERER_HPP

#include "window.hpp"

class ArrowRenderer : public Renderer
{
    public:
        virtual void loadTextures();
        virtual void render(sf::RenderWindow &screen, sf::Vector2u tile_size, World &world);
};

#endif
