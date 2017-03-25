#include "window.hpp"

#include "event_manager.hpp"
#include "game.hpp"

#include "background_renderer.hpp"
#include "foreground_renderer.hpp"
#include "character_renderer.hpp"
#include "arrow_renderer.hpp"
#include "HUD_renderer.hpp"

Window::Window(unsigned short width, unsigned short height, std::string title) :
    screen(sf::VideoMode(width, height), title), tile_size(8, 8), zoom(1)
{
    //Show loading screen ?
    view = screen.getView();

    addRenderer(std::move(std::unique_ptr<BackgroundRenderer>   (new BackgroundRenderer())));
    addRenderer(std::move(std::unique_ptr<CharacterRenderer>    (new CharacterRenderer())));
    addRenderer(std::move(std::unique_ptr<ArrowRenderer>        (new ArrowRenderer())));
    addRenderer(std::move(std::unique_ptr<ForegroundRenderer>   (new ForegroundRenderer())));
    addRenderer(std::move(std::unique_ptr<HUDRenderer>          (new HUDRenderer())));
}

void Window::setTileSize(sf::Vector2u tile_size)
{
    this->tile_size.x = tile_size.x > 0 ? tile_size.x : 1;
    this->tile_size.y = tile_size.y > 0 ? tile_size.y : 1;
}

sf::Vector2u Window::getTileSize() const
{
    return (tile_size);
}

void Window::setZoom(unsigned char zoom)
{
    this->zoom = zoom > 0 ? zoom : 1;
    view.zoom(1.f / this->zoom);
}

void Window::setDesiredFPS(unsigned char fps)
{
    screen.setFramerateLimit(fps);
}

void Window::centerViewAt(sf::View &view, Terrain &terrain, Vector2f center)
{
    sf::Vector2f half_terrain_size(view.getSize().x / (tile_size.x * 2),
                                   view.getSize().y / (tile_size.y * 2));

    if (center.x < half_terrain_size.x)
        center.x = half_terrain_size.x;
    else if (center.x > terrain.getWidth() - half_terrain_size.x)
        center.x = terrain.getWidth() - half_terrain_size.x;

    if (center.y < half_terrain_size.y)
        center.y = half_terrain_size.y;
    else if (center.y > terrain.getHeight() - half_terrain_size.y)
        center.y = terrain.getHeight() - half_terrain_size.y;

    center.x *= tile_size.x;
    center.y *= tile_size.y;

    view.setCenter(center.x, center.y);
}

void Window::addRenderer(std::unique_ptr<Renderer> renderer)
{
    renderer->loadTextures();
    renderers.push_back(std::move(renderer));
}

void Window::update(World &world, bool &quit)
{
    world.delta_time = clock.getElapsedTime().asSeconds();
    clock.restart();
    screen.clear();

    centerViewAt(view, world.terrain,
                 world.characters.front()->body.position + world.characters.front()->body.size * 0.5f);
    render(world, view);

    screen.display();

    //To allow physic to takes place before drawing world
    processInput(world, quit);
}

void Window::processInput(World &world, bool &quit)
{
    sf::Event event;
    while (screen.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            screen.close();
            quit = true;
        }
        else if (event.type == sf::Event::Resized)
        {
            view.setSize(event.size.width, event.size.height);
            view.zoom(1.f / zoom);
        }
    }
}

void Window::render(World &world, sf::View &view)
{
    screen.setView(view);

    for (auto &renderer : renderers)
        renderer->render(screen, tile_size, world);
}

