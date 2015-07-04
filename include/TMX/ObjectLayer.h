#ifndef OBJECTLAYER_H
#define OBJECTLAYER_H

#include "Layer.h"
#include "MapObject.h"

class ObjectLayer : public Layer
{
    public:
        ObjectLayer();
        ~ObjectLayer();

        vector<MapObject*> objects;
};

#endif // OBJECTLAYER_H
