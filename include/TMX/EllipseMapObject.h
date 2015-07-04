#ifndef ELLIPSEMAPOBJECT_H
#define ELLIPSEMAPOBJECT_H

#include "MapObject.h"

class EllipseMapObject : public MapObject
{
    public:
        EllipseMapObject();

        int x;
        int y;
        int width;
        int height;
};

#endif // ELLIPSEMAPOBJECT_H
