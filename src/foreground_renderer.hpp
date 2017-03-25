#ifndef FOREGROUND_RENDERER
#define FOREGROUND_RENDERER

#include "textures_manager.hpp"
#include "window.hpp"

class ForegroundRenderer : public Renderer
{
    public:
        virtual void loadTextures();
        virtual void render(sf::RenderWindow &screen, sf::Vector2u tile_size, World &world);
};

#endif
