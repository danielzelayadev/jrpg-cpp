#include "TMX/TMXParser.h"
#include "TMX/Data.h"

#include <sstream>

using std::stringstream;

TMXParser::TMXParser()
{
   fileDir = "";
   tmxFile = nullptr;
}

TMXParser::TMXParser(string fileDir)
{
   this->fileDir = fileDir;
   tmxFile = new XMLDocument();
}

TMXParser::~TMXParser()
{
   if(tmxFile) delete tmxFile;
}

Map* TMXParser::parse(string fileDir)
{
   this->fileDir = fileDir;

   if(tmxFile) delete tmxFile;

   tmxFile = new XMLDocument();

   return parse();
}

Map* TMXParser::parse()
{
   if(fileDir.size() < 5 || fileDir.substr(fileDir.size()-4, 4) != ".tmx") { printf("Not a TMX file.\n"); return nullptr;}

   if(tmxFile->LoadFile(fileDir.c_str()) != 0) { printf("File does not exist.\n"); return nullptr; }

   string path = "";
   int found = fileDir.find_last_of("/");
   if(found != fileDir.size()) path = fileDir.substr(0, found);

   Map* tiledMap = new Map(path);

   XMLNode* root = tmxFile->FirstChildElement();

   if(!root) { printf("No map node\n"); return nullptr; }

   printf("Beginning parse...\n\n");

   if(!loadMapAttributes(tiledMap, root->ToElement())) return nullptr;

   XMLNode* tmp = root->FirstChildElement();

   while(tmp)
   {
     printf("Parsing "); printf(tmp->Value()); printf("...\n");

     if(!strcmp(tmp->Value(), "tileset"))
     {
       if(!loadTileSetNode(tiledMap, tmp)) return nullptr;
     }
     else if(!strcmp(tmp->Value(), "layer"))
     {
       if(!loadLayerNode(tiledMap, tmp)) return nullptr;
     }
     else if(!strcmp(tmp->Value(), "objectgroup"))
     {
       if(!loadObjectGroupNode(tiledMap, tmp)) return nullptr;
     }
     else if(!strcmp(tmp->Value(), "imagelayer"))
     {
       if(!loadImageLayerNode(tiledMap, tmp)) return nullptr;
     }
     else if(!strcmp(tmp->Value(), "properties"))
     {
        if(!loadProperties(&tiledMap->properties, tmp)) return nullptr;
     }
     tmp = tmp->NextSibling();
   }

   printf("\nParse ended successfully! :)\n");
   return tiledMap;
}

bool TMXParser::loadMapAttributes(Map* tiledMap, XMLElement* element)
{
   if(!element) { printf("Node doesn't have attributes.\n"); return false; }

   if(element->QueryFloatAttribute("version", &tiledMap->version) != 0) printf("No version attribute.\n");

   const char* ori = "";

   ori = element->Attribute("orientation");

   if(!ori) { printf("No orientation attribute.\n"); return false; }

   tiledMap->orientation = ori;

   if(element->QueryIntAttribute("width", &tiledMap->tilesX) != 0) { printf("No width attribute.\n"); return false; }

   if(element->QueryIntAttribute("height", &tiledMap->tilesY) != 0) { printf("No height attribute.\n"); return false; }

   if(element->QueryIntAttribute("tilewidth", &tiledMap->tileWidth) != 0)
   { printf("No tilewidth attribute.\n"); return false; }

   if(element->QueryIntAttribute("tileheight", &tiledMap->tileHeight) != 0)
   { printf("No tileheight attribute.\n"); return false; }

   tiledMap->width = tiledMap->tilesX * tiledMap->tileWidth;
   tiledMap->height = tiledMap->tilesY * tiledMap->tileHeight;

   const char* ro = "";

   ro = element->Attribute("renderorder");

   if(!ro) printf("No render order.\n");

   else tiledMap->renderOrder = ro;

   tiledMap->print();

   return true;
}

bool TMXParser::loadTileSetNode(Map* tiledMap, XMLNode* tilesetNode)
{
   tiledMap->tilesets.push_back(new Tileset());

   if(!loadTileSetAttributes(tiledMap, tilesetNode->ToElement())) return false;

   XMLNode* tmp = tilesetNode->FirstChildElement();

   while(tmp)
   {
      printf("Parsing "); printf(tmp->Value()); printf(" for tileset %d...\n", tiledMap->tilesets.size());

      if(!strcmp(tmp->Value(), "tileoffset"))
      {
         if(!loadTileOffsetAttributes(tiledMap, tilesetNode->ToElement())) return false;
      }
      else if(!strcmp(tmp->Value(), "image"))
      {
        Image* image = tiledMap->tilesets.back()->image;
        if(!loadImageNode(image, tmp)) return false;
      }
      else if(!strcmp(tmp->Value(), "tile"))
      {
        Tile* tile;

        if(!tiledMap->tilesets.back()->tiles.size())
        { tile = new Tile(); tiledMap->tilesets.back()->tiles.push_back(tile); }

        else tile = tiledMap->tilesets.back()->tiles.back();

        if(!loadTileNode(tile, tmp)) return false;
      }
      else if(!strcmp(tmp->Value(), "terraintypes"))
      {
        if(!loadTerrainTypes(&tiledMap->tilesets.back()->terrainTypes, tmp)) return false;
      }
      else if(!strcmp(tmp->Value(), "properties"))
      {
        if(!loadProperties(&tiledMap->tilesets.back()->properties, tmp)) return false;
      }

      tmp = tmp->NextSibling();
   }

   return true;
}

 bool TMXParser::loadTileSetAttributes(Map* tiledMap, XMLElement* element)
 {
   if(!element) { printf("Node doesn't have attributes.\n"); return false; }

   Tileset* tileset = tiledMap->tilesets.at(tiledMap->tilesets.size()-1);

   if(element->QueryIntAttribute("firstgid", &tileset->firstgid) != 0)
   { printf("No firstgid attribute.\n"); return false; }

   const char* src = "";

   src = element->Attribute("source");

   if(!src) printf("No source for the tileset.\n");

   else tileset->source = src;

   const char* nm = "";

   nm = element->Attribute("name");

   if(!nm) printf("No name specified for the tileset.\n");

   else tileset->name = nm;

   if(element->QueryIntAttribute("tilewidth", &tileset->tilewidth) != 0)
   { printf("No tilewidth attribute.\n"); return false; }

   if(element->QueryIntAttribute("tileheight", &tileset->tileheight) != 0)
   { printf("No tileheight attribute.\n"); return false; }

   if(element->QueryIntAttribute("spacing", &tileset->spacing) != 0)
     printf("No spacing specified; defaulting to 0.\n");

   if(element->QueryIntAttribute("margin", &tileset->margin) != 0)
     printf("No margin specified; defaulting to 0.\n");

   return true;
 }

 bool TMXParser::loadTileOffsetAttributes(Map* tiledMap, XMLElement* element)
 {
    Tileset* tileset = tiledMap->tilesets.at(tiledMap->tilesets.size()-1);

    if(element->QueryIntAttribute("x", &tileset->offset->x) != 0)
     printf("No x offset specified; defaulting to 0.\n");

    if(element->QueryIntAttribute("y", &tileset->offset->y) != 0)
     printf("No y offset specified; defaulting to 0.\n");

    return true;
 }

 bool TMXParser::loadImageNode(Image* image, XMLNode* imageNode)
 {
    if(!loadImageAttributes(image, imageNode->ToElement())) return false;

    XMLNode* tmp = imageNode->FirstChildElement();

    while(tmp)
    {
       printf("Parsing "); printf(tmp->Value()); printf(" for image...\n");

       if(!strcmp(tmp->Value(), "data"))
       {
          if(!loadDataNode(image->imageData, tmp)) return false;
       }

       tmp = tmp->NextSibling();
    }

    return true;
 }

 bool TMXParser::loadImageAttributes(Image* image, XMLElement* element)
 {
    if(!element) { printf("Node doesn't have attributes.\n"); return false; }

    const char* str = "";

    str = element->Attribute("format");

    if(!str) printf("No format specified.\n");

    else image->format = str;

    str = element->Attribute("source");

    if(!str) { printf("No source specified... Aborting.\n"); return false; }

    image->source = str;

    str = element->Attribute("trans");

    if(!str) printf("No trans specified.\n");

    else image->trans = str;

    if(element->QueryIntAttribute("width", &image->width) != 0)
    { printf("No width specified for image... Aborting.\n"); return false;}

    if(element->QueryIntAttribute("height", &image->height) != 0)
    { printf("No height specified for image... Aborting.\n"); return false;}

    return true;
 }

 bool TMXParser::loadDataNode(Data* data, XMLNode* dataNode)
 {
    if(!loadDataAttributes(data, dataNode->ToElement())) return false;

    XMLNode* tmp = dataNode->FirstChildElement();

    while(tmp)
    {
      printf("Parsing "); printf(tmp->Value()); printf(" for data node...\n");

      if(!strcmp(tmp->Value(), "tile"))
      {
         if(!loadTileNode(data->tile, tmp)) return false;
      }

      tmp = tmp->NextSibling();
    }

    return true;
 }

//Por ahora solo CSV
 bool TMXParser::loadDataAttributes(Data* data, XMLElement* element)
 {

   if(!element) { printf("Node doesn't have attributes.\n"); return false; }

   const char* str = "";

   str = element->Attribute("encoding");

   if(!str) { printf("Data encoding not specified... Aborting.\n"); return false; }

   data->encoding = str;

   str = element->Attribute("compression");

   if(!str) printf("Data compression not specified.\n");

   else data->compression = str;

   if(!strcmp(data->encoding.c_str(), "csv"))
     data->data = element->GetText();

   else
   {
     printf("\n%s is either not a valid encoding or is currently\nnot supported by the parser!...Aborting.\n",
     data->encoding.c_str());
     return false;
   }

   return true;
 }

 bool TMXParser::loadTileNode(Tile* tile, XMLNode* tileNode)
 {
   if(!loadTileAttributes(tile, tileNode->ToElement())) return false;

   XMLNode* tmp = tileNode->FirstChildElement();

   while(tmp)
   {
     printf("Parsing "); printf(tmp->Value()); printf(" for tile node...\n");

     if(!strcmp(tmp->Value(), "objectgroup"))
     {

     }

     else if(!strcmp(tmp->Value(), "properties"))
     {
        if(!loadProperties(&tile->properties, tmp)) return false;
     }

     tmp = tmp->NextSibling();
   }

   return true;
 }

  bool TMXParser::loadTileAttributes(Tile* tile, XMLElement* element)
  {
    if(!element) { printf("Node doesn't have attributes.\n"); return false; }

    if(element->QueryIntAttribute("id", &tile->id) != 0)
    { printf("No tile id specified... Aborting.\n"); return false; }

    const char* str = "";

    str = element->Attribute("terrain");

    if(!str) printf("No terrain specified.\n");

    else tile->terrain = str;

    if(element->QueryFloatAttribute("probability", &tile->probability) != 0)
       printf("No tile probability specified.\n");

    return true;
  }

bool TMXParser::loadProperties(vector<Property*>* properties, XMLNode* propertiesNode)
{
    XMLNode* tmp = propertiesNode->FirstChildElement();

    while(tmp)
    {
       printf("Parsing "); printf(tmp->Value()); printf("...\n");

       if(!strcmp(tmp->Value(), "property"))
       {
          if(!loadPropertyAttributes(properties, tmp->ToElement())) return false;
       }

       tmp = tmp->NextSibling();
    }

    return true;
}

bool TMXParser::loadPropertyAttributes(vector<Property*>* properties, XMLElement* element)
{
    if(!element) { printf("Node doesn't have attributes.\n"); return false; }

    Property* prop = new Property();

    const char* str = "";

    str = element->Attribute("name");

    if(!str) printf("Property name not specified.\n");

    else prop->name = str;

    str = element->Attribute("value");

    if(!str) printf("Property value not specified.\n");

    else prop->value = str;

    properties->push_back(prop);

    return true;
}

bool TMXParser::loadTerrainTypes(vector<Terrain*>* terrains, XMLNode* terraintypeNode)
{
    XMLNode* tmp = terraintypeNode->FirstChildElement();

    while(tmp)
    {
      printf("Parsing "); printf(tmp->Value()); printf("...\n");

      if(!strcmp(tmp->Value(), "terrain"))
      {
        if(!loadTerrainAttributes(terrains, tmp->ToElement())) return false;
      }

      tmp = tmp->NextSibling();
    }

    return true;
}

bool TMXParser::loadTerrainAttributes(vector<Terrain*>* terrains, XMLElement* element)
{
    if(!element) { printf("Node doesn't have attributes.\n"); return false; }

    Terrain* terrain = new Terrain();

    const char* str = element->Attribute("name");

    if(!str) { printf("Terrain name not specified... Aborting.\n"); return false; }

    terrain->name = str;

    if(element->QueryIntAttribute("tile", &terrain->tile) != 0)
    { printf("No tile specified... Aborting.\n"); return false; }

    terrains->push_back(terrain);

    return true;
}

bool TMXParser::loadLayerNode(Map* tiledMap, XMLNode* layerNode)
{
    Layer* layer = new Layer(tiledMap->width, tiledMap->height);

    if(!loadLayerAttributes(layer, layerNode->ToElement())) { delete layer; return false; }

    XMLNode* tmp = layerNode->FirstChildElement();

    while(tmp)
    {
       printf("Parsing "); printf(tmp->Value()); printf(" for layer...\n");

       if(!strcmp(tmp->Value(), "data"))
       {
          if(!loadDataNode(layer->layerData, tmp)) return false;

          layer->convertData();
       }

       else if(!strcmp(tmp->Value(), "properties"))
       {
         if(!loadProperties(&layer->properties, tmp)) return false;
       }

       tmp = tmp->NextSibling();
    }

    tiledMap->layers.push_back(layer);

    return true;
}

bool TMXParser::loadLayerAttributes(Layer* layer, XMLElement* element)
{
    if(!element) { printf("Node doesn't have attributes.\n"); return false; }

    const char* str = element->Attribute("name");

    if(!str) { printf("Layer name not specified... Aborting.\n"); return false; }

    layer->name = str;

    if(element->QueryFloatAttribute("opacity", &layer->opacity) != 0)
       printf("Opacity not specified...Defaulting to 1.\n");

    if(element->QueryBoolAttribute("visible", &layer->visible) != 0)
       printf("Visibility not specified...Defaulting to visible.\n");

    return true;
}

bool TMXParser::loadImageLayerNode(Map* tiledMap, XMLNode* imageLayerNode)
{
    ImageLayer* iLayer = new ImageLayer();

    if(!loadImageLayerAttributes(iLayer, imageLayerNode->ToElement())) { delete iLayer; return false; }

    XMLNode* tmp = imageLayerNode->FirstChildElement();

    while(tmp)
    {
      printf("Parsing "); printf(tmp->Value()); printf(" for image layer...\n");

      if(!strcmp(tmp->Value(), "properties"))
      {
         if(!loadProperties(&iLayer->properties, tmp)) return false;
      }
      else if(!strcmp(tmp->Value(), "image"))
      {
         if(!loadImageNode(iLayer->image, tmp)) return false;
      }

      tmp = tmp->NextSibling();
    }

    tiledMap->layers.push_back(iLayer);

    return true;
}

bool TMXParser::loadImageLayerAttributes(ImageLayer* iLayer, XMLElement* element)
{
    if(!loadLayerAttributes((Layer*)iLayer, element)) return false;

    if(element->QueryIntAttribute("x", &iLayer->x) != 0)
       printf("X position not specified for image layer...Defaulting to 0.\n");

    if(element->QueryIntAttribute("y", &iLayer->y) != 0)
       printf("Y position not specified for image layer...Defaulting to 0.\n");

    return true;
}

bool TMXParser::loadObjectGroupNode(Map* tiledMap, XMLNode* objectGroupNode)
{
    ObjectLayer* oLayer = new ObjectLayer();

    if(!loadObjectLayerAttributes(oLayer, objectGroupNode->ToElement())) return false;

    XMLNode* tmp = objectGroupNode->FirstChildElement();

    while(tmp)
    {
      printf("Parsing "); printf(tmp->Value()); printf(" for object layer...\n");

      if(!strcmp(tmp->Value(), "object"))
      {
         if(!loadObject(&oLayer->objects, tmp)) return false;
      }

      else if(!strcmp(tmp->Value(), "properties"))
      {
        if(!loadProperties(&oLayer->properties, tmp)) return false;
      }

      tmp = tmp->NextSibling();
    }

    tiledMap->layers.push_back(oLayer);

    return true;
}

bool TMXParser::loadObjectLayerAttributes(ObjectLayer* oLayer, XMLElement* element)
{
    return loadLayerAttributes((Layer*)oLayer, element);
}

bool TMXParser::loadObject(vector<MapObject*>* objects, XMLNode* objectNode)
{
    MapObject object;

    if(!loadObjectAttributes(&object, objectNode->ToElement())) return false;

    XMLNode* tmp = objectNode->FirstChildElement(),
             *cache = nullptr;
    bool isRect = false, isEllipse = false, isPolygon = false, isPolyline = false;

    while(tmp)
    {
      printf("Parsing "); printf(tmp->Value()); printf(" for object...\n");

      if(!strcmp(tmp->Value(), "properties"))
      {
         if(!loadProperties(&object.properties, tmp)) return false;
      }

      else if(!strcmp(tmp->Value(), "image"))
      {
         object.image = new Image();
         if(!loadImageNode(object.image, tmp)) return false;
      }

      else if(!strcmp(tmp->Value(), "ellipse"))
      {
         isEllipse = true;
      }

      else if(!strcmp(tmp->Value(), "polygon"))
      {
         isPolygon = true;
         cache = tmp;
      }

      else if(!strcmp(tmp->Value(), "polyline"))
      {
         isPolyline = true;
         cache = tmp;
      }

      tmp = tmp->NextSibling();
    }

    isRect = !isEllipse && !isPolygon && !isPolyline;

    MapObject* newObject;

    if(isRect)
    { newObject = new RectangleMapObject(); loadRectAttributes((RectangleMapObject*)newObject, objectNode->ToElement()); }
    else if(isEllipse)
    { newObject = new EllipseMapObject(); loadEllipseAttributes((EllipseMapObject*)newObject, objectNode->ToElement()); }
    else if(isPolygon)
    { newObject = new PolygonMapObject(); loadPolygonAttributes((PolygonMapObject*)newObject, cache->ToElement()); }
    else if(isPolyline)
    { newObject = new PolylineMapObject(); loadPolylineAttributes((PolylineMapObject*)newObject, cache->ToElement()); }

    newObject->copyObj(&object);

    objects->push_back(newObject);

    return true;
}

bool TMXParser::loadObjectAttributes(MapObject* object, XMLElement* element)
{
    if(!element) { printf("Node doesn't have attributes.\n"); return false; }

    if(element->QueryIntAttribute("id", &object->id) != 0)
       printf("Object id not specified.\n");
    if(element->QueryIntAttribute("gid", &object->gid) != 0)
       printf("No reference to tile.\n");
    if(element->QueryIntAttribute("rotation", &object->rotation) != 0)
       printf("Object rotation not specified...Defaulting to 0.\n");
    if(element->QueryBoolAttribute("visible", &object->visible) != 0)
       printf("Object visibility not specified...Defaulting to visible.\n");

    const char* str = "";

    str = element->Attribute("name");

    if(!str) printf("Object name not specified.\n");

    else object->name = str;

    str = element->Attribute("type");

    if(!str) printf("Object type not specified.\n");

    else object->type = str;

    return true;
}

bool TMXParser::loadRectAttributes(RectangleMapObject* rmo, XMLElement* element)
{
    if(!element) { printf("Node doesn't have attributes.\n"); return false; }

    if(element->QueryIntAttribute("x", &rmo->x) != 0)
       printf("X position not specified for rectangle object...Defaulting to 0.\n");

    if(element->QueryIntAttribute("y", &rmo->y) != 0)
       printf("Y position not specified for rectangle object...Defaulting to 0.\n");

    if(element->QueryIntAttribute("width", &rmo->width) != 0)
       printf("Y position not specified for rectangle object...Defaulting to 0.\n");

    if(element->QueryIntAttribute("height", &rmo->height) != 0)
       printf("Y position not specified for rectangle object...Defaulting to 0.\n");

    return true;
}

bool TMXParser::loadEllipseAttributes(EllipseMapObject* ellipse, XMLElement* element)
{
    if(!element) { printf("Node doesn't have attributes.\n"); return false; }

    if(element->QueryIntAttribute("x", &ellipse->x) != 0)
       printf("X position not specified for ellipse object...Defaulting to 0.\n");

    if(element->QueryIntAttribute("y", &ellipse->y) != 0)
       printf("Y position not specified for ellipse object...Defaulting to 0.\n");

    if(element->QueryIntAttribute("width", &ellipse->width) != 0)
       printf("Y position not specified for ellipse object...Defaulting to 0.\n");

    if(element->QueryIntAttribute("height", &ellipse->height) != 0)
       printf("Y position not specified for ellipse object...Defaulting to 0.\n");

    return true;
}

bool TMXParser::loadPolygonAttributes(PolygonMapObject* poly, XMLElement* element)
{
    if(!element) { printf("Node doesn't have attributes.\n"); return false; }

    const char* str = "";

    str = element->Attribute("points");

    if(!str) printf("Points not specified for polygon.\n");

    else
    {
       string points = str;
       stringstream strm;

       for(int i = 0; i < points.size(); i++)
       {
          char c = points.at(i);

          if(c == ',')
          {
             int xPos = 0;
             strm >> xPos;
             strm.str(string());
             poly->x.push_back(xPos);
          }
          else if(c == ' ')
          {
             int yPos = 0;
             strm >> yPos;
             strm.str(string());
             poly->y.push_back(yPos);
          }
          else
             strm << c;
       }

    }

    return true;
}

bool TMXParser::loadPolylineAttributes(PolylineMapObject* poly, XMLElement* element)
{
    if(!element) { printf("Node doesn't have attributes.\n"); return false; }

    const char* str = "";

    str = element->Attribute("points");

    if(!str) printf("Points not specified for polyline.\n");

    else
    {
       string points = str;
       stringstream strm;

       for(int i = 0; i < points.size(); i++)
       {
          char c = points.at(i);

          if(c == ',')
          {
             int xPos = 0;
             strm >> xPos;
             strm.clear();
             poly->x.push_back(xPos);
          }
          else if(c == ' ')
          {
             int yPos = 0;
             strm >> yPos;
             strm.clear();
             poly->y.push_back(yPos);
          }
          else
             strm << c;

       }

    }

    return true;
}
