#include "TMX/Image.h"
#include "TMX/Data.h"

Image::Image()
{
    this->format = "";
    this->height = 0;
    this->imageData = new Data();
    this->source = "";
    this->trans = "";
    this->width = 0;
}

Image::~Image()
{
   delete imageData;
}
