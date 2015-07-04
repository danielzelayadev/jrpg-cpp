#include "TMX/MapObject.h"

MapObject::MapObject()
{
    this->id = 0;
    this->gid = 0;
    this->name = "";
    this->rotation = 0;
    this->visible = true;
    this->type = "";

    this->image = nullptr;
}

void MapObject::copyObj(MapObject mo)
{
   this->id = mo.id;
   this->gid = mo.gid;
   this->name = mo.name;
   this->rotation = mo.rotation;
   this->visible = mo.visible;
   this->type = mo.type;
   this->properties = mo.properties;
}

MapObject::~MapObject()
{
   delete image;

    for(int i = 0; i < properties.size(); i++)
       delete properties[i];
}
