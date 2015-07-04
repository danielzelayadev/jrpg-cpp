#include "MapRenderer.h"

#include "TMX/ObjectLayer.h"
#include "TMX/RectangleMapObject.h"

#include <cmath>

#include <sstream>
#include <iostream>

using namespace std;

MapRenderer::MapRenderer(Map* m, SDL_Renderer* renderer, SDL_Rect* camera)
{
    map = m;
    this->renderer = renderer;
    this->camera = camera;

    camCachedX = camera->x;
    camCachedY = camera->y;

    for(int i = 0; i < map->tilesets.size(); i++)
    {
      string pathToTexture = "";
      string mapPath = m->path;
      string imageSource = map->tilesets.at(i)->image->source;
      pathToTexture.append(mapPath);
      pathToTexture.append("/");
      pathToTexture.append(imageSource);

      tilesets.push_back(IMG_LoadTexture(renderer, pathToTexture.c_str()));
      widths.push_back(map->tilesets.at(i)->image->width);
      heights.push_back(map->tilesets.at(i)->image->height);
    }


    if(map->tilesX*map->tileWidth >= camera->w)
    { screenTilesX = (camera->w / map->tileWidth); if(camera->w % map->tileWidth) screenTilesX++; }
    else
           screenTilesX = map->tilesX;

    if(map->tilesY*map->tileHeight >= camera->h)
    { screenTilesY = (camera->h / map->tileHeight); if(camera->h % map->tileHeight) screenTilesY++; }
    else
           screenTilesY = map->tilesY;

    totalScreenTiles = screenTilesX*screenTilesY;
    cout << totalScreenTiles << endl;
}

void MapRenderer::update()
{
   if(camCachedX > camera->x)
      pushObjects(RIGHT);

   else if(camCachedX < camera->x)
      pushObjects(LEFT);

   if(camCachedY > camera->y)
      pushObjects(DOWN);

   else if(camCachedY < camera->y)
      pushObjects(UP);

   camCachedX = camera->x;
   camCachedY = camera->y;
}

void MapRenderer::render()
{
      for(int i = 0; i < map->layers.size(); i++)
         renderLayer(i);
}

void MapRenderer::renderLayer(int index)
{
   Layer* layer = map->layers.at(index);

   if(layer->type == 'L' && layer->visible)
   {
      tileRect = {0, 0, map->tileWidth, map->tileHeight};

      short* blueprint = layer->data;

      int x = 0;

      for(int i = 0, indx = calculateStartPoint(); i < totalScreenTiles; i++)
      {
         if(blueprint[indx])
           renderFromTileSet(blueprint[indx], tileRect);
         x++;
         indx++;

         tileRect.x += tileRect.w;
         if(x % screenTilesX == 0) { skipIndx(indx); x = 0; tileRect.x = 0; tileRect.y += tileRect.h; }
      }

   }
}

void MapRenderer::renderFromTileSet(short gid, SDL_Rect tileRect)
{
   int val = gid-1;

   int tilesetIndx = 0;
   int rowMax = 0;
   int colMax = 0;

   for(int i = 0; i < tilesets.size(); i++)
   {
      int tilesetW = widths.at(i), tilesetH = heights.at(i);
      rowMax = tilesetW/map->tileWidth;
      colMax = tilesetH/map->tileHeight;

      if(val < colMax*rowMax) { tilesetIndx = i; break; }
   }

   int rowIndx = val/ rowMax;
   int colIndx = abs( (rowIndx*rowMax)-val );

   SDL_Rect crop = {colIndx*map->tileWidth, rowIndx*map->tileHeight, tileRect.w, tileRect.h};
   SDL_RenderCopy( renderer, tilesets.at(tilesetIndx), &crop, &tileRect);
}

int MapRenderer::calculateStartPoint()
{
   int rowIndx = (camera->y / map->tileHeight);
   int colIndx = camera->x / map->tileWidth;
   int startIndx = (rowIndx * map->tilesX) + colIndx;

   return startIndx;
}

void MapRenderer::skipIndx(int& indx)
{
    int diffX = map->tilesX - screenTilesX;

    if(diffX)
    indx += diffX;
}

void MapRenderer::pushObjects(int dir)
{
   for(int i = 0; i < map->layers.size(); i++)
   {
       if(map->layers[i]->type == 'O')
       {
           ObjectLayer* oLayer = (ObjectLayer*)map->layers[i];

           for(int k = 0; k < oLayer->objects.size(); k++)
           {
               if(oLayer->objects[k]->shapeType == RECTANGLE)
               {
                  RectangleMapObject* rmo = (RectangleMapObject*)oLayer->objects[k];

                  if(dir == UP) rmo->y -= map->tileHeight;
                  else if(dir == DOWN) rmo->y += map->tileHeight;
                  else if(dir == RIGHT) rmo->x += map->tileWidth;
                  else if(dir == LEFT) rmo->x -= map->tileWidth;
               }
           }
       }
   }
}

MapRenderer::~MapRenderer()
{
   for(int i = 0; i < tilesets.size(); i++)
      SDL_DestroyTexture(tilesets.at(i));
}
