#include "TMX/RectangleMapObject.h"

RectangleMapObject::RectangleMapObject():MapObject()
{
    this->x = 0;
    this->y = 0;
    this->width = 0;
    this->height = 0;

    shapeType = RECTANGLE;
}
