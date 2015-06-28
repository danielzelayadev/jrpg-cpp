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

   int tilesXCtr = 0;
   int tilesYCtr = 0;

   if(layer->isShown())
   {
      string blueprint = layer->getBlueprint();

      for(int i = 0; i < blueprint.size(); i++)
      {
         if(blueprint.at(i) != '/')
         {
         stringstream strm;
         int indx = 0;
         strm << blueprint.at(index);
         strm >> indx;

         SDL_RenderCopy(renderer, map->getTexture(indx), 0, &tileRect);
         }

         tilesXCtr++;
         tileRect.x += tileRect.w;

         if(tilesXCtr >= map->getTilesX()) {tilesXCtr = 0; tileRect.x = 0; tilesYCtr++; tileRect.y += tileRect.h;}
      }
    }
}
