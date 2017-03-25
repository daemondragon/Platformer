#ifndef BACKGROUND_RENDERER
#define BACKGROUND_RENDERER

#include "textures_manager.hpp"
#include "window.hpp"

class BackgroundRenderer : public Renderer
{
    public:
        virtual void loadTextures();
        virtual void render(sf::RenderWindow &screen, sf::Vector2u tile_size, World &world);
};

#endif
