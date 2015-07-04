#include "TMX/Data.h"
#include "TMX/Tile.h"

Data::Data()
{
    this->compression = "";
    this->encoding = "";
    this->data = "";
    this->tile = new Tile();
}

Data::~Data()
{
   delete tile;
}
