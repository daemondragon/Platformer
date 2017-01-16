#ifndef TERRAIN_HPP
#define TERRAIN_HPP

#include <vector>

#include "tile.hpp"

class Terrain
{
	public:
	    enum class Ground
	    {
	        Back = 0, Fore = 1
	    };

        Terrain();
        Terrain(unsigned short width, unsigned short height);

        bool    create(unsigned short width, unsigned short height);
		bool	isInside(unsigned short x, unsigned short y) const;

		unsigned short	getWidth() const;
		unsigned short	getHeight() const;

		Tile&           get(Ground ground, unsigned short x, unsigned short y);
		const Tile&		get(Ground ground, unsigned short x, unsigned short y) const;
		Tile&			tryAndGet(Ground ground, unsigned short x, unsigned short y);
		const Tile&		tryAndGet(Ground ground, unsigned short x, unsigned short y) const;
		void			set(const Tile &tile, Ground ground, unsigned short x, unsigned short y);
		void			tryAndSet(const Tile &tile, Ground ground, unsigned short x, unsigned short y);

	private:
	    unsigned short width;
	    unsigned short height;

	    std::vector<Tile>   tiles;
};

#endif
