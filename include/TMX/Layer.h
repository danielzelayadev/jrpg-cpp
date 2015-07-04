#ifndef LAYER_H
#define LAYER_H

#include <vector>
#include <string>

class Property;
class Data;

using std::vector;
using std::string;

class Layer
{
    public:
        Layer(int tilesX, int tilesY);
        Layer();
        ~Layer();

        char type;

        string name;
        float opacity;
        bool visible;

        Data* layerData;
        short* data;

        int tilesX, tilesY;

        vector<Property*> properties;

        void convertData();
};

#endif // LAYER_H
