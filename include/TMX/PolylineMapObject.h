#ifndef POLYLINEMAPOBJECT_H
#define POLYLINEMAPOBJECT_H

#include "MapObject.h"

class PolylineMapObject : public MapObject
{
    public:
        PolylineMapObject();

        vector<int> x;
        vector<int> y;
};

#endif // POLYLINEMAPOBJECT_H
