#ifndef TRI_NAMABLE_HPP_INCLUDED
#define TRI_NAMABLE_HPP_INCLUDED



namespace t3 {

class Namable
{
public:
    const char* getName() const {
        return filename_;
    }
    
    void setName( const char* const name ){
        std::strcmp( filename_, name );
    }
    
private:
    enum {
        MAX_NAME_SIZE = 96,
    };
    
    char filename_[MAX_NAME_SIZE];

};
    
}   // namespace t3



#endif // TRI_NAMABLE_HPP_INCLUDED

