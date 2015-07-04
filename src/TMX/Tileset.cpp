#include "TMX/Tileset.h"
#include "TMX/Image.h"
#include "TMX/TileOffset.h"

#include <cmath>
#include <stdio.h>

Tileset::Tileset()
{
   firstgid = 1;
   source = "";
   name = "";
   tilewidth = 0;
   tileheight = 0;
   spacing = 0;
   margin = 0;

   this->image = new Image();
   this->offset = new TileOffset();
}

Tileset::~Tileset()
{
   delete image;
   delete offset;

   for(int i = 0; i < tiles.size(); i++)
       delete tiles[i];
   for(int i = 0; i < terrainTypes.size(); i++)
       delete terrainTypes[i];
   for(int i = 0; i < properties.size(); i++)
       delete properties[i];
}
