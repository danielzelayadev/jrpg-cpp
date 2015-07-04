#ifndef MAPRENDERER_H
#define MAPRENDERER_H

#include "TMX/Map.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

class MapRenderer
{
    public:
        MapRenderer(Map* m, SDL_Renderer* renderer, SDL_Rect* camera);
        ~MapRenderer();

        void render();

        void renderLayer(int index);


    private:
        Map* map;
        SDL_Renderer* renderer;
        SDL_Rect* camera;
        SDL_Rect tileRect;
        vector<SDL_Texture*> tilesets;
        vector<int> widths;
        vector<int> heights;

        int totalScreenTiles;
        int screenTilesX;
        int screenTilesY;

        void renderFromTileSet(short gid, SDL_Rect tileRect);

        int calculateStartPoint();
        void skipIndx(int& indx);

};

#endif // MAPRENDERER_H
