#include "animations.hpp"

Animations::Animations(sf::Texture &texture) : texture(texture)
{
}

void Animations::addAnimation(unsigned short id, float time)
{
    if (id >= animations.size())
        animations.resize(id + 1);

    animations[id].time = (time <= 0.f ? 1.f : time);
}

void Animations::addFrameTo(unsigned short anim_id, const sf::IntRect &frame)
{
    animations[anim_id].frames.push_back(frame);
}

float Animations::getTime(unsigned short anim_id) const
{
    return (animations[anim_id].time);
}

unsigned short Animations::getNbFrame(unsigned short anim_id) const
{
    return (animations[anim_id].frames.size());
}

sf::Sprite Animations::getFrame(unsigned short anim_id, unsigned short frame_id) const
{
    sf::Sprite sprite;
    sprite.setTexture(texture);
    sprite.setTextureRect(animations[anim_id].frames[frame_id]);
    return (sprite);
}




AnimatedSprite::AnimatedSprite(Animations &anim) :
    animations(anim), current_time(0.f), current_animation(0)
{
}

void AnimatedSprite::setCurrentAnimation(unsigned short anim_id)
{
    current_animation = anim_id;
    resetFrame();
}

void AnimatedSprite::update(float delta_time)
{
    current_time += delta_time;

    float current_anim_time = animations.getTime(current_animation);
    while (current_time >= current_anim_time)
        current_time -= current_anim_time;
}

void AnimatedSprite::resetFrame()
{
    current_time = 0.f;
}

sf::Sprite AnimatedSprite::getCurrentFrame() const
{
    return (animations.getFrame(current_animation,
                                current_time / animations.getTime(current_animation)));
}
