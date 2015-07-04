#include "TMX/ObjectLayer.h"

#include <string.h>

ObjectLayer::ObjectLayer():Layer()
{
    this->type = 'O';
}

ObjectLayer::~ObjectLayer()
{
    for(int i = 0; i < objects.size(); i++)
       delete objects[i];

    for(int i = 0; i < properties.size(); i++)
       delete properties[i];
}

void ObjectLayer::addObject(MapObject* obj)
{
   if(obj) objects.push_back(obj);
}

void ObjectLayer::removeObject(MapObject* obj)
{
   for(int i = 0; i < objects.size(); i++)
   {
      MapObject* mo = objects[i];

      if(mo == obj)
      {
         objects.erase(objects.begin()+i);
         delete mo;
      }
   }
}

void ObjectLayer::removeObject(string name)
{
   for(int i = 0; i < objects.size(); i++)
   {
      MapObject* mo = objects[i];

      if(!strcmp(mo->name.c_str(), name.c_str()))
      {
         objects.erase(objects.begin()+i);
         delete mo;
      }
   }
}

void ObjectLayer::removeObject(int i)
{
   MapObject* mo = getObject(i);

   if(!mo) return;

   objects.erase(objects.begin()+i);
   delete mo;
}

MapObject* ObjectLayer::getObject(int i)
{
   if(i < 0 || i >= objects.size()) return nullptr;

   return objects[i];
}

MapObject* ObjectLayer::getObject(string name)
{
   for(int i = 0; i < objects.size(); i++)
   {
      MapObject* mo = objects[i];

      if(!strcmp(mo->name.c_str(), name.c_str()))
         return mo;
   }

   return nullptr;
}
