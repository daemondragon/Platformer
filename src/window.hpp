#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "textures_manager.hpp"
#include "game.hpp"

class Window : public Module
{
    public:
        Window(unsigned short width, unsigned short height, std::string title);

        void            setTileSize(sf::Vector2u tile_size);
        sf::Vector2u    getTileSize() const;

        void            setZoom(unsigned char zoom);
        void            centerViewAt(sf::View &view, Terrain &terrain,
                                     Vector2f center);

        void            update(World &world, bool &quit);

    private:

        void    processInput(World &world, bool &quit);

        void    render(World &world, sf::View &view);
        void    render(Terrain &terrain, Terrain::Ground ground);
        void    render(Character &character);

        void    loadTextures();

        sf::Clock           clock;
        sf::RenderWindow    screen;
        sf::Vector2u        tile_size;
        unsigned char       zoom;
        sf::View            view;

        enum class TextureType
        {
            Background,
            Foreground,
            Character
        };

        TexturesManager<TextureType>     textures;
};

#endif
