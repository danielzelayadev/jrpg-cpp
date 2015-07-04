#include "TMX/MapObject.h"

#include <string.h>

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

void MapObject::copyObj(MapObject* mo)
{
   this->id = mo->id;
   this->gid = mo->gid;
   this->name = mo->name;
   this->rotation = mo->rotation;
   this->visible = mo->visible;
   this->type = mo->type;

   for(int i = 0; i < mo->properties.size(); i++)
   {
      Property* prop = new Property();
      prop->name = mo->properties[i]->name;
      prop->value= mo->properties[i]->value;

      this->properties.push_back(prop);
   }
}

string MapObject::getProperty(int i)
{
   if(i < 0 || i >= properties.size()) return "";

   return properties[i]->value;
}

string MapObject::getProperty(string name)
{
    for(int i = 0; i < properties.size(); i++)
       if(!strcmp(properties[i]->name.c_str(), name.c_str()))
          return properties[i]->value;

    return "";
}

MapObject::~MapObject()
{
   delete image;

    for(int i = 0; i < properties.size(); i++)
       delete properties[i];
}
