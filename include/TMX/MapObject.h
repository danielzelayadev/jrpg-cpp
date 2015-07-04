#ifndef MAPOBJECT_H
#define MAPOBJECT_H

#include <vector>
#include <string>
#include "Property.h"
#include "Image.h"

using std::vector;
using std::string;

class MapObject
{
    public:
        MapObject();
        ~MapObject();

        int id;
        string name;
        string type;
        int rotation;
        int gid;
        bool visible;

        Image* image;

        vector<Property*> properties;

        friend class TMXParser;

        private:
        void copyObj(MapObject mo);
};

#endif // MAPOBJECT_H
