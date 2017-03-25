#include "split_screen.hpp"

SplitScreen::SplitScreen(sf::RenderWindow &window, float optimal_ratio) : window(window)
{
    setOptimalRatio(optimal_ratio);
}

void SplitScreen::addViews(size_t nb_views)
{
    if (nb_views > 0)
    {
        views.resize(views.size() + nb_views);
        updateViews();
    }
}

void SplitScreen::removeViews(size_t nb_views)
{
    if (nb_views > 0 && views.size() > nb_views)
    {
        views.resize(views.size() - nb_views);
        updateViews();
    }
}

int SplitScreen::getNbViews() const
{
    return (views.size());
}

sf::View SplitScreen::getView(int i)
{
    return (views[i]);
}

void SplitScreen::setOptimalRatio(float optimal_ratio)
{
    if (optimal_ratio <= 0.f)
        optimal_ratio = 1.77;

    this->optimal_ratio = optimal_ratio;
}

void SplitScreen::updateViews()
{
    if (views.size() > 0)
        updateViewsWithDisposition(findViewsDisposition());
}

#include <iostream>

sf::Vector2u SplitScreen::findViewsDisposition()
{
    sf::Vector2u best_disposition(views.size(), 1);
    float best_score = getDispositionScore(best_disposition);

    for (size_t y = 2; y <= views.size(); ++y)
    {
        int x = std::ceil(views.size() * 1.f / y);
        float current_score = getDispositionScore(sf::Vector2u(x, y));
        if (current_score > best_score && (views.size() > x * (y - 1)))//To prevent having unused rows in extreme case.
        {
            best_score = current_score;
            best_disposition = sf::Vector2u(x, y);
        }
    }
    return (best_disposition);
}

float SplitScreen::getDispositionScore(const sf::Vector2u &disposition)
{
    float view_size_x = 1.f * window.getSize().x / disposition.x;
    float view_size_y = 1.f * window.getSize().y / disposition.y;

    return (1.f / std::abs(view_size_x / view_size_y - optimal_ratio));
}

void SplitScreen::updateViewsWithDisposition(const sf::Vector2u &disposition)
{
    sf::Vector2f viewport_size(1.f / disposition.x, 1.f / disposition.y);
    sf::Vector2f view_size(window.getSize().x * viewport_size.x, window.getSize().y * viewport_size.y);

    for (size_t i = 0; i < views.size(); ++i)
    {
        views[i].setSize(view_size);
        views[i].setViewport(sf::FloatRect(i % disposition.x * viewport_size.x,
                                           i / disposition.x * viewport_size.y,
                                           viewport_size.x,
                                           viewport_size.y));
    }
}

