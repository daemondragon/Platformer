#ifndef TERRAIN_HPP
#define TERRAIN_HPP

#include <vector>
#include <string>

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
		void            setWorldType(unsigned short type);
		unsigned short  getWorldType() const;

		Tile&           get(Ground ground, unsigned short x, unsigned short y);
		const Tile&		get(Ground ground, unsigned short x, unsigned short y) const;
		Tile&			tryAndGet(Ground ground, unsigned short x, unsigned short y);
		const Tile&		tryAndGet(Ground ground, unsigned short x, unsigned short y) const;
		void			set(const Tile &tile, Ground ground, unsigned short x, unsigned short y);
		void			tryAndSet(const Tile &tile, Ground ground, unsigned short x, unsigned short y);

        bool            save(const std::string &filename) const;
        bool            load(const std::string &filename);

	private:
	    unsigned short width;
	    unsigned short height;
	    unsigned short world_type;

	    std::vector<Tile>   tiles;
};

#endif
