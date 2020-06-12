#ifndef RESOURCE_NOT_LOADED_H
#define RESOURCE_NOT_LOADED_H
#include <iostream>
#include <string> 
#include "BaseException.h"

namespace PlanetDefenders
{
    class TextureNotLoaded : public BaseException
    {
    public:
        TextureNotLoaded(const std::string& textureName) :
            BaseException("Texture " + textureName + " not loaded")
        {}
        friend std::ostream& operator<<(std::ostream& output, const TextureNotLoaded& e)
        {
            output << e.message() << std::endl;
            return output;
        }
    };

    class MusicNotLoaded : public BaseException
    {
    public:
        MusicNotLoaded(const std::string& musicName) :
            BaseException("Music " + musicName + " not loaded")
        {}
        friend std::ostream& operator<<(std::ostream& output, const MusicNotLoaded& e)
        {
            output << e.message() << std::endl;
            return output;
        }
    };

}
#endif

