

#ifndef TRI_FILEPATH_HPP_INCLUDED
#define TRI_FILEPATH_HPP_INCLUDED


#include "base/tri_std.hpp"


namespace t3 {
inline namespace io {

class FilePath {
public:
    FilePath(
        String filepath
    );
    
    FilePath(const char* const filepath);
    
    ~FilePath();

public:
    String getFullPath() const;
    
    String getExt() const;
    
    String getFileNameNotExt() const;
    

public:
    static void setResourceDirectory(
        String const base
    );

private:
    String filepath_;
    static String base_filepath_;
};


}   // namespace io
}   // namespace t3



#endif // TRI_FILEPATH_HPP_INCLUDED
