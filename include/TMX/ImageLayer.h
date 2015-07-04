#ifndef IMAGELAYER_H
#define IMAGELAYER_H

#include "Layer.h"

class Image;

class ImageLayer : public Layer
{
    public:
        ImageLayer();
        ~ImageLayer();

        int x;
        int y;

        Image* image;
};

#endif // IMAGELAYER_H
