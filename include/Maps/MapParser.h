#ifndef MAPPARSER_H
#define MAPPARSER_H

#include <string>
#include <fstream>

#include "Map.h"
#include "SDL2/SDL_image.h"

using namespace std;

class MapParser
{
    public:
        MapParser(SDL_Renderer* renderer);


        Map* parse(string mapDir);

    private:

        ifstream* reader;

        SDL_Renderer* renderer;

        void readDirBlock(Map* map);
        void readDimsBlock(Map* map);
        void readLayerBlock(Map* map);
        void readPropertiesBlock(Map* map);
        void readBlueprintBlock(Map* map);

        void loadAndAddTextures(Map* map, string dir);

        void readLayerSubBlock(Map* map, int layerNo);

        void getRepeats(string line, int* ind, int* rx, int* ry);
};

#endif // MAPPARSER_H
