#include "Maps/MapParser.h"

#include <dirent.h>

#include <iostream>

#include <sstream>

MapParser::MapParser(SDL_Renderer* renderer)
{
    reader = new ifstream();
    this->renderer = renderer;
}

Map* MapParser::parse(string mapDir)
{
    if(!strstr(mapDir.c_str(), ".mp")) return nullptr;

    reader->open(mapDir);

    if(reader->is_open())
    {
        Map* map = new Map();

        readDirBlock(map);

        readDimsBlock(map);

        readLayerBlock(map);

        readPropertiesBlock(map);

        readBlueprintBlock(map);

        return map;
    }

    return nullptr;
}

void MapParser::readDirBlock(Map* map)
{
    string line;

    int jumpCount = 4;

    do
    {
      getline(*reader, line);

      if(line == "<DIRS>") continue;

      if(strstr(line.c_str(), "tilesetDir"))
      {
           int wsiz = 10;
           int posI = wsiz+jumpCount;
           string tileSetDir = line.substr(posI, line.size()-posI-1);
           map->setTileset(IMG_LoadTexture(renderer, tileSetDir.c_str()));
      }

      else if(strstr(line.c_str(), "tilefolderDir"))
      {
           int wsiz = 13;
           int posI = wsiz+jumpCount;
           string tileFolderDir = line.substr(posI, line.size()-posI-1);
           loadAndAddTextures(map, tileFolderDir);
      }

    } while(line != "</DIRS>");
}

void MapParser::loadAndAddTextures(Map* map, string dir)
{
   DIR *dpdf;
   struct dirent *epdf;

   dpdf = opendir(dir.c_str());
   if (dpdf)
   {
      while(epdf = readdir(dpdf))
      {
         string txtDir = dir + "/" + epdf->d_name;

        if( strcmp(epdf->d_name, ".") != 0 && strcmp(epdf->d_name, "..") != 0 )
            map->addTileTexture(IMG_LoadTexture(renderer, txtDir.c_str()));
      }

      closedir(dpdf);
   }
}

void MapParser::readDimsBlock(Map* map)
{
   string line;

   int jumpCount = 4;

    do
    {
      getline(*reader, line);

      stringstream strm;

      if(line == "<DIMS>") continue;

      if(strstr(line.c_str(), "TILES_X"))
      {
           int wsiz = 7;
           int posI = wsiz+jumpCount;
           strm << line.substr(posI, line.size()-posI-1);
           int tilesX = 0;
           strm >> tilesX;
           map->setTilesX(tilesX);
      }

      else if(strstr(line.c_str(), "TILES_Y"))
      {
           int wsiz = 7;
           int posI = wsiz+jumpCount;
           strm << line.substr(posI, line.size()-posI-1);
           int tilesY = 0;
           strm >> tilesY;
           map->setTilesY(tilesY);
      }

      else if(strstr(line.c_str(), "TILE_WIDTH"))
      {
           int wsiz = 10;
           int posI = wsiz+jumpCount;
           strm << line.substr(posI, line.size()-posI-1);
           int tileW = 0;
           strm >> tileW;
           map->setTileWidth(tileW);
      }

      else if(strstr(line.c_str(), "TILE_HEIGHT"))
      {
           int wsiz = 11;
           int posI = wsiz+jumpCount;
           strm << line.substr(posI, line.size()-posI-1);
           int tileH = 0;
           strm >> tileH;
           map->setTileHeight(tileH);
      }

    } while(line != "</DIMS>");
}

void MapParser::readLayerBlock(Map* map)
{
    string line;

   int jumpCount = 4;

    while(true)
    {
      getline(*reader, line);

      if(line == "<LAYERS>") continue;
      if(line == "</LAYERS>") break;

      if(strstr(line.c_str(), "LAYER"))
      {
           int wsiz = 5;
           int posI = wsiz+jumpCount;
           string layerName = line.substr(posI, line.size()-posI-1);

           Layer* layer = new Layer(layerName);

           map->addLayer(layer);
      }

    }
}

void MapParser::readPropertiesBlock(Map* map)
{
}

void MapParser::readBlueprintBlock(Map* map)
{
    string line;

    do
    {
      getline(*reader, line);

      stringstream strm;

      if(line == "<BLUEPRINT>") continue;

      if(strstr(line.c_str(), "<L"))
      {
         int wsiz = 2;
         strm << line.at(wsiz);
         int layerNo = 0;
         strm >> layerNo;
         readLayerSubBlock(map, layerNo);
      }

    } while(line != "</BLUEPRINT>");
}

void MapParser::readLayerSubBlock(Map* map, int layerNo)
{
    string line;
    Layer* layer = map->getLayer(layerNo-1);

    string blueprint("");

    while(true)
    {
      getline(*reader, line);

      if(strstr(line.c_str(), "</L")) break;

      for(int i = 0; i < line.size(); i++)
      {
         char readChar = line.at(i);

         if(i < line.size()-1 && line.at(i+1) == '(')
         {
           int repeatX = 0, repeatY = 1;

           i+=2;
           getRepeats(line, &i, &repeatX, &repeatY);

//           cout << repeatX << endl;
//           cout << repeatY << endl << endl;

           for(int k = 0; k < repeatY; k++)
           {
              for(int j = 0; j < map->getTilesX(); j++)
              {
                 if(j < repeatX)
                   blueprint.push_back(readChar);
                 else
                   blueprint.push_back('/');
              }
           }

           continue;
         }

         blueprint.push_back(readChar);
      }

    }

    layer->setBlueprint(blueprint);
//    cout << "----- Layer " << layerNo << " Blueprint -----" << endl;
//    cout << layer->getBlueprint() << endl << endl;
}

void MapParser::getRepeats(string line, int* ind, int* rx, int* ry)
{
    string multX(""), multY("");
    stringstream strmX, strmY;
    bool goX = true;

    while(true)
    {
       char c = line.at(*ind);

       if(c == ')')
       {
          strmX << multX;
          strmX >> *rx;

          if(!goX)
          {
            strmY << multY;
            strmY >> *ry;
          }

          (*ind)++;
          break;
       }

       if(c == ',')
       {
          goX = false;
          (*ind)++;
          continue;
       }

       if(goX)
          multX.push_back(c);
       else
          multY.push_back(c);

       (*ind)++;
    }
}
