#include "TMX/Layer.h"
#include "TMX/Data.h"

#include <sstream>
#include <stdio.h>
#include <iostream>

using namespace std;

Layer::Layer()
{
  this->type = 'L';
  this->name = "";
  this->opacity = 1.0;
  this->visible = true;
  this->data = nullptr;
  this->layerData = new Data();
}

Layer::Layer(int tilesX, int tilesY)
{
  this->tilesX = tilesX;
  this->tilesY = tilesY;
  this->type = 'L';
  this->name = "";
  this->opacity = 1.0;
  this->visible = true;
  this->data = nullptr;
  this->layerData = new Data();
}

Layer::~Layer()
{
    delete layerData;

    delete[] data;

    for(int i = 0; i < properties.size(); i++)
       delete properties[i];
}

void Layer::convertData()
{
   string tmp = layerData->data;

   data = new short[tilesX*tilesY];

   int dCtr = 0;

   while(true)
   {
      string valStr("");
      stringstream strm;

      if(tmp.find(",") == tmp.npos)
      {
        valStr = tmp.substr(0, tmp.size()-1);
        strm << valStr;
        strm >> data[dCtr];
        break;
      }

      int firstCommaIndex = tmp.find_first_of(",");

      valStr = tmp.substr(0, firstCommaIndex);
      strm << valStr;
      strm >> data[dCtr];

      dCtr++;
      tmp = tmp.substr(firstCommaIndex+1, tmp.size()-firstCommaIndex+1);
   }
}
