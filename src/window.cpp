#include "window.hpp"

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
    for (auto &arrow : world.arrows)
        render(*arrow);

    render(world.terrain, Terrain::Ground::Fore);

    renderHUD(world);

    screen.display();
}

void Window::render(Terrain &terrain, Terrain::Ground ground)
{
    sf::Sprite sprite;
    sf::Texture texture = textures.get(
                              ground == Terrain::Ground::Back ?
                                  TextureType::Background : TextureType::Foreground,
                              terrain.getWorldType());

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

    sf::CircleShape aim(tile_size.x / 8);
    aim.setFillColor(sf::Color(255, 0, 0));

    sf::Vector2f relative_position;
    if ((int)Bow::Direction::Top & (int)character.bow.direction)
        relative_position.y = -1.f;
    else if ((int)Bow::Direction::Bottom & (int)character.bow.direction)
        relative_position.y = 1.f;

    if ((int)Bow::Direction::Front & (int)character.bow.direction)
        relative_position.x = (character.direction == Character::Direction::Left ? -1.f : 1.f);

    aim.setPosition((character.body.position.x + character.body.size.x / 2 + relative_position.x) * tile_size.x,
                          (character.body.position.y + character.body.size.y / 2 + relative_position.y) * tile_size.y);

    screen.draw(aim);
}

void Window::render(Arrow &arrow)
{
    Vector2f direction = arrow.body.velocity.normalized();

    sf::Sprite sprite;
    sf::Texture texture = textures.get(TextureType::Arrow, 0);

    sprite.setTexture(texture);
    sprite.setOrigin(texture.getSize().x, texture.getSize().y / 2);
    sprite.rotate(arrow.body.velocity.y < 0 ? 360 - 57.2957795131 * std::acos(direction.x) :
                                                    57.2957795131 * std::acos(direction.x));
    sprite.setPosition(arrow.body.position.x * tile_size.x,
                       arrow.body.position.y * tile_size.y);

    screen.draw(sprite);
}

void Window::renderHUD(World &world)
{
    sf::Sprite sprite;
    sf::Texture texture = textures.get(TextureType::Arrow, 0);
    Vector2f arrow_size(texture.getSize().x / 2, texture.getSize().y / 2);
    sprite.setTexture(texture);
    sprite.setOrigin(arrow_size.x * 2, arrow_size.y * 2);
    sprite.rotate(90);
    sprite.scale(0.5f, 0.5f);

    for (auto &character : world.characters)
    {
        int nb_arrows = character->bow.arrows.size();
        Vector2f offset((character->body.position.x + character->body.size.x / 2) * tile_size.x - (nb_arrows / 2 + (nb_arrows % 2 == 0 ? 1 : 1.5f)) * arrow_size.x,
                         character->body.position.y * tile_size.y - arrow_size.y);
        int i = 0;
        for (auto &arrow : character->bow.arrows)
        {
            ++i;
            sprite.setPosition(offset.x + i * arrow_size.x, offset.y);
            screen.draw(sprite);
        }
    }
}

void Window::loadTextures()
{
    textures.load("data/images/background/0.png", TextureType::Background, 0);
    textures.load("data/images/background/1.png", TextureType::Background, 1);
    textures.load("data/images/background/2.png", TextureType::Background, 2);
    textures.load("data/images/background/3.png", TextureType::Background, 3);
    textures.load("data/images/background/4.png", TextureType::Background, 4);

    textures.load("data/images/foreground/0.png", TextureType::Foreground, 0);
    textures.load("data/images/foreground/1.png", TextureType::Foreground, 1);
    textures.load("data/images/foreground/2.png", TextureType::Foreground, 2);
    textures.load("data/images/foreground/3.png", TextureType::Foreground, 3);
    textures.load("data/images/foreground/4.png", TextureType::Foreground, 4);

    textures.load("data/images/arrows.png", TextureType::Arrow, 0);
}

