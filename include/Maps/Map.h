#ifndef MAP_H
#define MAP_H

#include <SDL2/SDL.h>
#include <vector>
#include <string>

#include "Layer.h"

using namespace std;

class Map
{
    public:
        Map(){}

        void addLayer(Layer* layer);
        void addTileTexture(SDL_Texture* tileTxt);

        Layer* getLayer(int i);
        Layer* getLayer(string name);
        void hideLayer(int i);
        void hideLayer(string name);
        void showLayer(int i);
        void showLayer(string name);

        void setTileset(SDL_Texture* tileset) {this->tileset = tileset;}

        void setTilesX(int tx) {tilesX = tx;}
        void setTilesY(int ty) {tilesY = ty;}
        void setTileWidth(int tw) {tileWidth = tw;}
        void setTileHeight(int th) {tileHeight = th;}

        int getWidth() {return width;}
        int getHeight()  {return height;}
        int getTilesX()  {return tilesX;}
        int getTilesY()  {return tilesY;}
        int getTileWidth()  {return tileWidth;}
        int getTileHeight()  {return tileHeight;}
        int getLayerCount()  {return layers.size();}

        SDL_Texture* getTileset() {return tileset;}
        SDL_Texture* getTexture(int i) {return tileTextures.at(i);}

        int getTextureCount() {return tileTextures.size();}

    private:

        vector<SDL_Texture*> tileTextures;
        vector<Layer*> layers;

        SDL_Texture* tileset;

        int width, height,
            tilesX, tilesY,
            tileWidth, tileHeight;

};

#endif // MAP_H
