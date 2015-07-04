#include "TMX/Tile.h"

Tile::Tile()
{
    this->id = 0;
    this->probability = 0;
    this->terrain = "";
}

Tile::~Tile()
{
  for(int i = 0; i < animations.size(); i++)
     delete animations[i];
  for(int i = 0; i < properties.size(); i++)
     delete properties[i];
}
