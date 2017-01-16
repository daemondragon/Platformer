#ifndef TEXTURES_MANAGER_HPP
#define TEXTURES_MANAGER_HPP

#include <SFML/Graphics.hpp>
#include <vector>

template <typename Type>
class TexturesManager
{
    public:
        bool    load(const std::string &filename, Type type, unsigned short id)
        {
            int t = (int)type;
            if (textures.size() <= t)
                textures.resize(t + 1);
            if (textures[t].size() <= id)
                textures[t].resize(id + 1);

            return (textures[t][id].loadFromFile(filename));
        }

        sf::Texture&    get(Type type, unsigned short id)
        {
            return (textures[(int)type][id]);
        }
    
    private:
        std::vector<std::vector<sf::Texture>>   textures;
};

#endif
