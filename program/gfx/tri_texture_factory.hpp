


#ifndef TRI_TEXTURE_FACTORY_HPP_INCLUDED
#define TRI_TEXTURE_FACTORY_HPP_INCLUDED


namespace t3 {
    

class Texture;
class TextureFactory
{
public:
    static Texture* createFromFile(
        const char* const filename
    );
    
private:
    static Texture* createFromPng(
        const char* const png
    );
};




}   // namespace t3

#endif // TRI_TEXTURE_FACTORY_HPP_INCLUDED

