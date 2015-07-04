#include "TMX/ObjectLayer.h"

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
