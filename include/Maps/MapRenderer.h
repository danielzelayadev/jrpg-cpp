#ifndef MAPRENDERER_H
#define MAPRENDERER_H

#include "Map.h"
#include "SDL2/SDL.h"

class MapRenderer
{
    public:
        MapRenderer(Map* m);

        void render(SDL_Renderer* renderer);

        void renderLayer(SDL_Renderer* renderer, int index);


    private:
        Map* map;

        void renderFromTileSet(SDL_Renderer* renderer, short val, SDL_Rect tileRect);
        void renderFromTxtVector(SDL_Renderer* renderer, short val, SDL_Rect tileRect);

};

#endif // MAPRENDERER_H
