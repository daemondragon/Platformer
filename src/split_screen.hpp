#ifndef SPLIT_SCREEN_HPP
#define SPLIT_SCREEN_HPP

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class SplitScreen
{
    public:
        SplitScreen(sf::RenderWindow &window, float optimal_ratio);

        void        addViews(size_t nb_views = 1);
        void        removeViews(size_t nb_views = 1);

        int         getNbViews() const;
        sf::View    getView(int i);

        void        setOptimalRatio(float optimal_ratio);

        //To call when window size have been changed or player have been removed or added
        void        updateViews();

    private:
        sf::Vector2u    findViewsDisposition();
        //Higher is better
        float           getDispositionScore(const sf::Vector2u &disposition);
        void            updateViewsWithDisposition(const sf::Vector2u &disposition);


        sf::RenderWindow        &window;
        float                   optimal_ratio;
        std::vector<sf::View>   views;
};

#endif
