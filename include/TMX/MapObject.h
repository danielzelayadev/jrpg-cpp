#ifndef MAPOBJECT_H
#define MAPOBJECT_H

#include <vector>
#include <string>
#include "Property.h"
#include "Image.h"

using std::vector;
using std::string;

enum ShapeType
{
   RECTANGLE, ELLIPSE, POLYGON, POLYLINE
};

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

        int shapeType;

        Image* image;

        friend class TMXParser;

        string getProperty(int i);
        string getProperty(string name);

        private:
        void copyObj(MapObject* mo);

        vector<Property*> properties;

};

#endif // MAPOBJECT_H
