#ifndef RECTANGLEMAPOBJECT_H
#define RECTANGLEMAPOBJECT_H

#include "MapObject.h"

class RectangleMapObject : public MapObject
{
    public:
        RectangleMapObject();

        int x;
        int y;
        int width;
        int height;
};

#endif // RECTANGLEMAPOBJECT_H
