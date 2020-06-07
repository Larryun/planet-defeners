#ifndef TEXTURE_NOT_LOADED_H
#define TEXTURE_NOT_LOADED_H
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
        const std::string message()
        {
            return msg;
        }
    };

}
#endif

