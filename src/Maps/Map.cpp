#include "Map.h"

void Map::addLayer(Layer* layer)
{
  layers.push_back(layer);
}

void Map::addTileTexture(SDL_Texture* texture)
{
  tileTextures.push_back(texture);
}

Layer* Map::getLayer(int i)
{
  return layers.at(i);
}

Layer* Map::getLayer(string name)
{
  for(int i = 0; i < layers.size(); i++)
  {
     if(layers.at(i)->getName() == name)
        return layers.at(i);
  }

  return nullptr;
}

void Map::hideLayer(int i)
{
    Layer* lay = getLayer(i);

    if(lay)
       lay->setShown(false);
}

void Map::hideLayer(string name)
{
    Layer* lay = getLayer(name);

    if(lay)
       lay->setShown(false);
}

void Map::showLayer(int i)
{
    Layer* lay = getLayer(i);

    if(lay)
       lay->setShown(true);
}

void Map::showLayer(string name)
{
    Layer* lay = getLayer(name);

    if(lay)
       lay->setShown(true);
}
