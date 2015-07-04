#ifndef IMAGE_H
#define IMAGE_H

#include <string>

using std::string;

class Data;

class Image
{
    public:
        Image();
        ~Image();

        string format;
        string source;
        string trans;
        int width;
        int height;

        Data* imageData;
};

#endif // IMAGE_H
