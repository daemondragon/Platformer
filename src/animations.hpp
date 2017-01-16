#ifndef ANIMATIONS_HPP
#define ANIMATIONS_HPP

#include <SFML/Graphics.hpp>

#include <vector>

class Animations
{
    public:
                    Animations(sf::Texture &texture);

        void        addAnimation(unsigned short id, float time);
        void        addFrameTo(unsigned short anim_id, const sf::IntRect &frame);

        float           getTime(unsigned short anim_id) const;
        unsigned short  getNbFrame(unsigned short anim_id) const;
        sf::Sprite      getFrame(unsigned short anim_id, unsigned short frame_id) const;

    private:
        struct Anim
        {
            std::vector<sf::IntRect>    frames;
            float                       time;
        };
        sf::Texture                 &texture;
        std::vector<Anim>           animations;
};

class AnimatedSprite
{
    public:
        AnimatedSprite(Animations &anim);

        void    setCurrentAnimation(unsigned short anim_id);

        void    update(float delta_time);
        void    resetFrame();

        sf::Sprite  getCurrentFrame() const;

    private:
        Animations      &animations;
        float           current_time;
        unsigned short  current_animation;
};

#endif
