#ifndef HUD_RENDERER_HPP
#define HUD_RENDERER_HPP

#include "window.hpp"

class HUDRenderer : public Renderer
{
    public:
        virtual void loadTextures();
        virtual void render(sf::RenderWindow &screen, sf::Vector2u tile_size, World &world);
};

#endif
