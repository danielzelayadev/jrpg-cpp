#ifndef OBJECTLAYER_H
#define OBJECTLAYER_H

#include "Layer.h"
#include "MapObject.h"

class ObjectLayer : public Layer
{
    public:
        ObjectLayer();
        ~ObjectLayer();

        void addObject(MapObject* obj);
        void removeObject(MapObject* obj);
        void removeObject(int i);
        void removeObject(string name);

        MapObject* getObject(int i);
        MapObject* getObject(string name);

        vector<MapObject*> getObjects() { return objects; }

        friend class TMXParser;
        friend class MapRenderer;

    private:
        vector<MapObject*> objects;

};

#endif // OBJECTLAYER_H
