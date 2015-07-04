#ifndef TILESET_H
#define TILESET_H

#include <SDL2/SDL.h>
#include <vector>
#include <string>

#include "Image.h"
#include "TileOffset.h"
#include "Terrain.h"
#include "Property.h"
#include "Tile.h"

using std::string;
using std::vector;

class Tileset
{
    public:
        Tileset();
        ~Tileset();

        int firstgid;
        string source;
        string name;
        int tilewidth;
        int tileheight;
        int spacing;
        int margin;

        TileOffset* offset;
        Image* image;

        vector<Tile*> tiles;
        vector<Terrain*> terrainTypes;
        vector<Property*> properties;
};

#endif // TILESET_H
