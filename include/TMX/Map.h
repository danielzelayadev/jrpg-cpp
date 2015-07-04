#ifndef MAP_H
#define MAP_H

#include <vector>
#include <string>

using std::string;
using std::vector;

#include "Tileset.h"
#include "Layer.h"
#include "Property.h"

//Le falta para background color
class Map
{
    public:
        Map(string path);
        ~Map();

        int getTilesX() { return tilesX; }
        int getTilesY() { return tilesY; }
        int getWidth()  { return width; }
        int getHeight() { return height; }
        int getTileWidth() { return tileWidth; }
        int getTileHeight() { return tileHeight; }
        int getLayerCount() { return layers.size(); }
        int getTilesetCount() { return tilesets.size(); }

        Layer* getLayer(string name);
        Layer* getLayer(int i);

        friend class TMXParser;
        friend class MapRenderer;

    private:

        string path;

        float version;
        string orientation;
        int width;
        int height;
        int tilesX;
        int tilesY;
        int tileWidth;
        int tileHeight;
        string renderOrder;

        vector<Tileset*> tilesets;
        vector<Layer*> layers;
        vector<Property*> properties;

        void print();

};

#endif // MAP_H
