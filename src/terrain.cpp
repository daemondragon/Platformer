#include "terrain.hpp"

#include <stdexcept>
#include <fstream>
#include <string>//For std::to_string()

Terrain::Terrain() : width(0), height(0), world_type(0)
{
}

Terrain::Terrain(unsigned short width, unsigned short height)
{
    create(width, height);
}

bool Terrain::create(unsigned short width, unsigned short height)
{
    try
    {
        tiles.resize(width * height * 2, Tile());
    }
    catch (std::exception &e)
    {
        this->width = 0;
        this->height = 0;
        return (false);
    }
    this->width = width;
    this->height = height;

    return (true);
}

bool Terrain::isInside(unsigned short x, unsigned short y) const
{
	return (x < width &&
			y < height);
}

unsigned short Terrain::getWidth() const
{
	return (width);
}

unsigned short Terrain::getHeight() const
{
	return (height);
}

void Terrain::setWorldType(unsigned short type)
{
    world_type = type;
}

unsigned short Terrain::getWorldType() const
{
    return (world_type);
}

Tile& Terrain::get(Ground ground, unsigned short x, unsigned short y)
{
	return (tiles[x + y * width + (int)ground * width * height]);
}

const Tile& Terrain::get(Ground ground, unsigned short x, unsigned short y) const
{
	return (tiles[x + y * width + (int)ground * width * height]);
}

Tile& Terrain::tryAndGet(Ground ground, unsigned short x, unsigned short y)
{
	if (isInside(x, y))
		throw std::logic_error("Terrain::tryAndGet - out of range : (" +
					std::to_string(x) + ";" + 
					std::to_string(y) + ")");

	return (get(ground, x, y));
}

const Tile& Terrain::tryAndGet(Ground ground, unsigned short x, unsigned short y) const
{
	if (isInside(x, y))
		throw std::logic_error("Terrain::tryAndGet - out of range : (" +
					std::to_string(x) + ";" + 
					std::to_string(y) + ")");

	return (get(ground, x, y));
}

void Terrain::set(const Tile &tile, Ground ground, unsigned short x, unsigned short y)
{
	tiles[x + y * width + (int)ground * width * height] = tile;
}

void Terrain::tryAndSet(const Tile &tile, Ground ground, unsigned short x, unsigned short y)
{
	if (isInside(x, y))
		throw std::logic_error("Terrain::tryAndSet - out of range : (" +
					std::to_string(x) + ";" + 
					std::to_string(y) + ")");

    set(tile, ground, x, y);
}

#include <iostream>

bool Terrain::save(const std::string &filename) const
{
    std::ofstream file(filename, std::ofstream::binary);
    if (!file.is_open())
        return (false);

    file.write((const char*)&world_type     , sizeof(unsigned short));
    file.write((const char*)&width          , sizeof(unsigned short));
    file.write((const char*)&height         , sizeof(unsigned short));
    file.write((const char*)&tiles.front()  , sizeof(Tile) * width * height * 2);//2 ground

    return (true);
}

bool Terrain::load(const std::string &filename)
{
    std::ifstream file(filename, std::ifstream::binary);
    if (!file.is_open())
        return (false);

    file.read((char*)&world_type    , sizeof(unsigned short));
    file.read((char*)&width         , sizeof(unsigned short));
    file.read((char*)&height        , sizeof(unsigned short));

    if (!create(width, height))
        return (false);

    file.read((char*)&tiles.front() , sizeof(Tile) * width * height * 2);// (2 ground)

    return (true);
}

