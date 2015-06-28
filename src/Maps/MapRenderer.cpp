#include "MapRenderer.h"

#include <sstream>
#include <iostream>

using namespace std;

MapRenderer::MapRenderer(Map* m)
{
    map = m;
}

void MapRenderer::render(SDL_Renderer* renderer)
{
   if(map->getTextureCount() > 0)
      for(int i = 0; i < map->getLayerCount(); i++)
         renderLayer(renderer, i);

   else if(map->getTileset())
   {
   }
}

void MapRenderer::renderLayer(SDL_Renderer* renderer, int index)
{
   Layer* layer = map->getLayer(index);

   SDL_Rect tileRect = {0, 0, map->getTileWidth(), map->getTileHeight()};

   if(layer->isShown())
   {
      char** blueprint = layer->getBlueprint();

      for(int i = 0; i < map->getTilesY(); i++, tileRect.y += tileRect.h)
      {
         tileRect.x = 0;
         for(int k = 0; k < map->getTilesX(); k++, tileRect.x+=tileRect.w)
         {
            if(blueprint[i][k] != '/')
            {
              stringstream strm;
              int indx = 0;
              strm << blueprint[i][k];
              strm >> indx;

              SDL_RenderCopy(renderer, map->getTexture(indx), 0, &tileRect);
            }
         }
      }
    }
}
