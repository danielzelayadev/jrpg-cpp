#include "MapRenderer.h"

#include <cmath>

#include <sstream>
#include <iostream>

using namespace std;

MapRenderer::MapRenderer(Map* m)
{
    map = m;
}

void MapRenderer::render(SDL_Renderer* renderer)
{
      for(int i = 0; i < map->getLayerCount(); i++)
         renderLayer(renderer, i);
}

void MapRenderer::renderLayer(SDL_Renderer* renderer, int index)
{
   Layer* layer = map->getLayer(index);

   SDL_Rect tileRect = {0, 0, map->getTileWidth(), map->getTileHeight()};

   if(layer->isShown())
   {
      short** blueprint = layer->getBlueprint();

      for(int i = 0; i < map->getTilesY(); i++, tileRect.y += tileRect.h)
      {
         tileRect.x = 0;
         for(int k = 0; k < map->getTilesX(); k++, tileRect.x+=tileRect.w)
         {
            if(blueprint[i][k] != -1)
            {
               if(map->getTextureCount() > 0)
                 renderFromTxtVector(renderer, blueprint[i][k], tileRect);
               else if(map->getTileset())
                 renderFromTileSet(renderer, blueprint[i][k], tileRect);
            }
         }
      }
    }
}

void MapRenderer::renderFromTxtVector(SDL_Renderer* renderer, short val, SDL_Rect tileRect)
{
   SDL_RenderCopy(renderer, map->getTexture(val), 0, &tileRect);
}

void MapRenderer::renderFromTileSet(SDL_Renderer* renderer, short val, SDL_Rect tileRect)
{
   int rowMax = map->getTilesetWidth()/map->getTileWidth();
   int rowIndx = val / rowMax;
   int colIndx = abs((rowIndx*rowMax)-val);

   SDL_Rect crop = {colIndx*map->getTileWidth(), rowIndx*map->getTileHeight(), tileRect.w, tileRect.h};

   SDL_RenderCopy(renderer, map->getTileset(), &crop, &tileRect);
}
