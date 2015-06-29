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
    if(!strstr(mapDir.c_str(), ".mml")) return nullptr;

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

    BlueprintData** blueprint = new BlueprintData*[map->getTilesY()];

    for(int i = 0; i < map->getTilesY(); i++)
    {
        blueprint[i] = new BlueprintData[map->getTilesX()];
        for(int k = 0; k < map->getTilesX(); k++)
        {
           blueprint[i][k].textureIndex = -1;
           blueprint[i][k].flag = -1;
           blueprint[i][k].cropX = 0;
           blueprint[i][k].cropY = 0;
           blueprint[i][k].cropW = 0;
           blueprint[i][k].cropH = 0;
           blueprint[i][k].crop = false;
        }
    }

    while(true)
    {
      getline(*reader, line);

      if(strstr(line.c_str(), "</L")) break;

      for(int i = 0; i < line.size(); i++)
      {
         char readChar = line.at(i);

         if(readChar == '[')
         {
           i++;
           int sx = 0, sy = 0;
           getStartPoint(line, &i, &sx, &sy);

           BlueprintData bd;
           bd.textureIndex = -1;

           if(line.at(i) == '{')
           {
              i++;
              bd.crop = true;
              crop(line, blueprint, &i, bd, sx, sy);
           }
           else
           {
             bd.crop = false;
             getTxtValue(line, &i, &(bd.textureIndex));
             stamp(line, blueprint, &i, bd, sx, sy);
           }

         }

      }

    }

    layer->setBlueprint(blueprint);
    cout << "----- Layer " << layerNo << " Blueprint -----" << endl;
    for(int i = 0; i < map->getTilesY(); i++)
    {
        for(int k = 0; k < map->getTilesX(); k++)
        {
           if(!layer->getBlueprint()[i][k].crop)
           cout << layer->getBlueprint()[i][k].textureIndex;
           else
           cout << "C";
        }
        cout << endl;
    }

    cout << endl;
}

void MapParser::crop(string line, BlueprintData** blueprint, int* ind, BlueprintData bd, int sx, int sy)
{
    getCropRect(line, ind, &bd);
    stamp(line, blueprint, ind, bd, sx, sy);
}

void MapParser::getCropRect(string line, int* ind, BlueprintData* bd)
{
   stringstream strmX, strmY, strmW, strmH;
   string stx(""), sty(""), stw(""), sth("");

   int current = 0;

   while(true)
   {
      char c = line.at(*ind);

      if(c == '}')
      {
          if(stx.size() > 0)
          {
            strmX << stx;
            strmX >> bd->cropX;
          }

          if(sty.size() > 0)
          {
            strmY << sty;
            strmY >> bd->cropY;
          }

          if(stw.size() > 0)
          {
            strmW << stw;
            strmW >> bd->cropW;
          }

          if(sth.size() > 0)
          {
            strmH << sth;
            strmH >> bd->cropH;
          }

          (*ind)++;
          break;
      }

      if(c == ',') { current++; (*ind)++; continue; }

      switch(current)
      {
         case 0:
         stx.push_back(c);
         break;
         case 1:
         sty.push_back(c);
         break;
         case 2:
         stw.push_back(c);
         break;
         case 3:
         sth.push_back(c);
         break;
      }

      (*ind)++;
   }

}
//14,4
void MapParser::stamp(string line, BlueprintData** blueprint, int* ind, BlueprintData bd, int sx, int sy)
{
    int rx = 0, ry = 0;

    if((*ind) < line.size() && line.at(*ind) == '(') { (*ind)++; getRepeats(line, ind, &rx, &ry);}

    for(int i = sy; i < sy+ry+1; i++)
        for(int k = sx; k < sx+rx+1; k++)
           blueprint[i][k] = bd;
}

void MapParser::getStartPoint(string line, int* ind, int* sx, int* sy)
{
    stringstream strmX, strmY;
    string stx(""), sty("");

    bool goX = true;

    while(true)
    {
       char c = line.at(*ind);

       if(c == ']')
       {
          strmX << stx;
          strmX >> *sx;

          if(!goX)
          {
            strmY << sty;
            strmY >> *sy;
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
          stx.push_back(c);
       else
          sty.push_back(c);


       (*ind)++;
    }
}

void MapParser::getTxtValue(string line, int* ind, short* val)
{
      string value("");
      stringstream strm;

      int shortLimit = 5+(*ind);

      for(; (*ind) < line.size() && (*ind) < shortLimit && line.at((*ind)) != '(' && line.at((*ind)) != '['
      && line.at((*ind)) != ' ';
      (*ind)++)
         value.push_back(line.at((*ind)));

      if(value.size() > 0) { strm << value; strm >> (*val); }
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
