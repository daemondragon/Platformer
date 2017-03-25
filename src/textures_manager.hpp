#ifndef TEXTURES_MANAGER_HPP
#define TEXTURES_MANAGER_HPP

#include <SFML/Graphics.hpp>
#include <vector>

class TexturesManager
{
    public:
        bool    load(const std::string &filename, unsigned short id)
        {
            if (textures.size() <= id)
                textures.resize(id + 1);

            return (textures[id].loadFromFile(filename));
        }

        sf::Texture&    get(unsigned short id)
        {
            return (textures[id]);
        }

    private:
        std::vector<sf::Texture>   textures;
};

#endif
