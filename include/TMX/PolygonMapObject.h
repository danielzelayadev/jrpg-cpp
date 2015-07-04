#ifndef POLYGONMAPOBJECT_H
#define POLYGONMAPOBJECT_H

#include "MapObject.h"

class PolygonMapObject : public MapObject
{
    public:
        PolygonMapObject();

        vector<int> x;
        vector<int> y;
};

#endif // POLYGONMAPOBJECT_H
