#ifndef REX_PAINT_H
#define REX_PAINT_H
#include <iostream>
#include "zlib.h"
#include "zconf.h"

//As of v1.02, there is a maximum of four layers in an .xp file
#define REXPAINT_MAX_NUM_LAYERS 4

namespace xp {
	typedef unsigned char uchar;
	typedef unsigned int uint;

	struct RexTile {
		/*This layout matches that of the .xp file*/
		uint  character;  //Why this is an unsigned int I have no idea
		uchar fore_red;
		uchar fore_green;
		uchar fore_blue;
		uchar back_red;
		uchar back_green;
		uchar back_blue;
		/*WARNING: Despite this layout matching the RexPaint representation,
		           your compiler will probably pad this out to 12 bytes (4*3)
				   instead of 10. Anyway, don't count on sizeof == 10.*/
	};

	struct RexLayer {
		RexTile* tiles;

		RexLayer(int width, int height)
			:tiles(new RexTile[width*height]) {}

		~RexLayer() {
			delete[] tiles;
			tiles = NULL;
		}
	};

	class RexFile {
	private:
		int version;
		int width, height, num_layers;
	public:
		RexFile(std::string const& filename); //Load an .xp file
		RexFile(int _version, int _width, int _height, int _num_layers); //Create a blank RexFile with the specified properties
		~RexFile();
		void save(std::string const& filename); //Save this object into a valid .xp file that RexPaint can load.

		inline int getVersion() { return version; };
		inline int getWidth() { return width; };
		inline int getHeight() { return height; };
		inline int getNumLayers() { return num_layers; };

		RexLayer* layers[REXPAINT_MAX_NUM_LAYERS];
		inline RexTile* getTile(int layer, int x, int y) { return &layers[layer]->tiles[x + (y * width)]; };

	private:
		RexFile(); //No default constructor.
	};

}

#endif //REX_PAINT_H
