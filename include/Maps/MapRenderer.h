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

};

#endif // MAPRENDERER_H
