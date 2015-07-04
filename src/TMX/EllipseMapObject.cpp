#include "TMX/EllipseMapObject.h"

EllipseMapObject::EllipseMapObject():MapObject()
{
    this->x = 0;
    this->y = 0;
    this->width = 0;
    this->height = 0;

    shapeType = ELLIPSE;
}
