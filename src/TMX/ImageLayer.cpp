#include "TMX/ImageLayer.h"
#include "TMX/Image.h"

ImageLayer::ImageLayer():Layer()
{
    this->type = 'I';
    this->x = 0;
    this->y = 0;
    this->image = new Image();
}

ImageLayer::~ImageLayer()
{
   delete image;
}
