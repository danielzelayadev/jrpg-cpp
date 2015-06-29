#ifndef LAYER_H
#define LAYER_H

#include "Tile.h"
#include <string>

using namespace std;

struct BlueprintData
{
   short textureIndex;
   short flag;
   bool crop;
   short cropX, cropW, cropY, cropH;
};

class Layer
{
    public:
        Layer(string name);

        string getName(){return name;}
        BlueprintData** getBlueprint(){return blueprint;}
        void setBlueprint(BlueprintData** blueprint) {this->blueprint = blueprint;}

        void setShown(bool s) {shown = s;}
        bool isShown() {return shown;}

    private:
        string name;

        BlueprintData** blueprint;

        bool shown;
};

#endif // LAYER_H
