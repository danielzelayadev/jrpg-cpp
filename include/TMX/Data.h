#ifndef DATA_H
#define DATA_H

#include <string>

class Tile;

class Data
{
    public:
        Data();
        ~Data();

        std::string encoding;
        std::string compression;
        std::string data;

        Tile* tile;
};

#endif // DATA_H
