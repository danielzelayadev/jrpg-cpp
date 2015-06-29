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
      BlueprintData** blueprint = layer->getBlueprint();

      for(int i = 0; i < map->getTilesY(); i++, tileRect.y += tileRect.h)
      {
         tileRect.x = 0;
         for(int k = 0; k < map->getTilesX(); k++, tileRect.x+=tileRect.w)
         {
            if(blueprint[i][k].crop || blueprint[i][k].textureIndex != -1)
            {
               if(map->getTextureCount() > 0)
                 renderFromTxtVector(renderer, blueprint[i][k].textureIndex, tileRect);
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
//[10,5]{250,300,100,100}(5,5)-px
//[10,5]15{250,300,100,100}(5,5)-px
//[10,5]15{250,300,100,100}(5,5)-tl
//[10,5]15{250,300,100,100}(5,5)-tl
//Cambiar de BlueprintData a tile y hacerla una clase y que tengan properties y otras funciones
void MapRenderer::renderFromTileSet(SDL_Renderer* renderer, BlueprintData bd, SDL_Rect tileRect)
{
   SDL_Rect crop;

   if(bd.crop) {crop = {bd.cropX, bd.cropY, bd.cropW, bd.cropH}; tileRect.w = crop.w; tileRect.h = crop.h;}

   else
   {
      short val = bd.textureIndex;
      int rowMax = map->getTilesetWidth()/map->getTileWidth();
      int rowIndx = val / rowMax;
      int colIndx = abs((rowIndx*rowMax)-val);

      crop = {colIndx*map->getTileWidth(), rowIndx*map->getTileHeight(), tileRect.w, tileRect.h};
   }

   SDL_RenderCopy(renderer, map->getTileset(), &crop, &tileRect);
}
