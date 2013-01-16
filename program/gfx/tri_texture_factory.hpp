


#ifndef TRI_TEXTURE_FACTORY_HPP_INCLUDED
#define TRI_TEXTURE_FACTORY_HPP_INCLUDED

#include <memory>


namespace t3 {
    

class Texture;
class TextureFactory
{
public:
    static std::shared_ptr<Texture> createFromFile(
        const char* const filename
    );
    
private:
    static std::shared_ptr<Texture> createFromPng(
        const char* const png
    );
};




}   // namespace t3

#endif // TRI_TEXTURE_FACTORY_HPP_INCLUDED

