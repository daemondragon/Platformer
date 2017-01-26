#include "window.hpp"

#include "character_actions.hpp"
#include "game.hpp"

Window::Window(unsigned short width, unsigned short height, std::string title) :
    screen(sf::VideoMode(width, height), title), tile_size(8, 8), zoom(1)
{
    //Show loading screen ?
    view = screen.getView();
    loadTextures();
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

void Window::update(World &world, bool &quit)
{
    world.delta_time = clock.getElapsedTime().asSeconds();
    clock.restart();

    centerViewAt(view, world.terrain,
                 world.characters.front()->body.position + world.characters.front()->body.size * 0.5f);
    render(world, view);

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
    screen.clear();

    render(world.terrain, Terrain::Ground::Back);

    for (auto &character : world.characters)
        render(*character);

    render(world.terrain, Terrain::Ground::Fore);

    screen.display();
}

void Window::render(Terrain &terrain, Terrain::Ground ground)
{
    sf::Sprite sprite;
    sf::Texture texture = textures.get(
                              ground == Terrain::Ground::Back ?
                                  TextureType::Background : TextureType::Foreground,
                              0);//0 is the ground variant (will be change later)

    sprite.setTexture(texture);
    int nb_tiles_width = texture.getSize().x / tile_size.x;

    for (int y = 0; y < terrain.getHeight(); ++y)
    {
        for (int x = 0; x < terrain.getWidth(); ++x)
        {
            Tile tile = terrain.get(ground, x, y);
            if (tile.id)
            {
                sprite.setTextureRect(sf::IntRect(tile.id % nb_tiles_width * tile_size.x,
                                                  tile.id / nb_tiles_width * tile_size.y,
                                                  tile_size.x, tile_size.y));
                sprite.setPosition(x * tile_size.x, y * tile_size.y);
                screen.draw(sprite);
            }
        }
    }
}

void Window::render(Character &character)
{
    sf::RectangleShape rectangle(sf::Vector2f(tile_size.x * character.body.size.x,
                                              tile_size.y * character.body.size.y));
    rectangle.setFillColor(sf::Color(0, 255, 0));
    rectangle.setPosition(character.body.position.x * tile_size.x,
                          character.body.position.y * tile_size.y);
    screen.draw(rectangle);
}

void Window::loadTextures()
{
    textures.load("data/background/0.png", TextureType::Background, 0);
    textures.load("data/background/1.png", TextureType::Background, 1);
    textures.load("data/background/2.png", TextureType::Background, 2);
    textures.load("data/background/3.png", TextureType::Background, 3);
    textures.load("data/background/4.png", TextureType::Background, 4);

    textures.load("data/foreground/0.png", TextureType::Foreground, 0);
    textures.load("data/foreground/1.png", TextureType::Foreground, 1);
    textures.load("data/foreground/2.png", TextureType::Foreground, 2);
    textures.load("data/foreground/3.png", TextureType::Foreground, 3);
    textures.load("data/foreground/4.png", TextureType::Foreground, 4);
}



void KeyboardController::update(Character &character)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        character.perform(Move(Character::Direction::Left));
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        character.perform(Move(Character::Direction::Right));
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        character.perform(Jump());
}

