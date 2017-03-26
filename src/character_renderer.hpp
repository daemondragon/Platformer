#ifndef CHARACTER_RENDERER_HPP
#define CHARACTER_RENDERER_HPP

#include "window.hpp"

class CharacterRenderer : public Renderer
{
    public:
        CharacterRenderer();

        virtual void loadTextures();
        virtual void update(float delta_time);
        virtual void render(sf::RenderWindow &screen, sf::Vector2u tile_size, World &world);


        void    addDeadCharacter(const DeadCharacter &character);
    private:
        void    renderDeadCharacters(sf::RenderWindow &screen, sf::Vector2u tile_size, World &world);
        void    renderCharacters(sf::RenderWindow &screen, sf::Vector2u tile_size, World &world);

        std::list<std::pair<sf::Vector2f, float>>   dead_characters;
};

#endif
