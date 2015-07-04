#ifndef TILE_H
#define TILE_H

#include <string>
#include <vector>

class Frame;
class Property;

class Tile
{
    public:
        Tile();
        ~Tile();

         int id;
         std::string terrain; //La vdd que no estoy seguro de este atributo ;'D
         float probability;

         std::vector<Frame*> animations;
         std::vector<Property*> properties;
};

#endif // TILE_H
