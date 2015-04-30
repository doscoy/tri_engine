

#ifndef TRI_FILEPATH_HPP_INCLUDED
#define TRI_FILEPATH_HPP_INCLUDED


#include "base/tri_std.hpp"


namespace t3 {


class FilePath {
public:
    FilePath(
       const String& filepath
    );
    
    ~FilePath();

public:
    String getFullPath() const;
    
    String ext() const;
    
    const String& path() const;
    
    String getFileNameNotExt() const;
    
public:
    static void setBaseDirectory(
        String const base
    );

private:
    String filepath_;
    static String base_filepath_;
};


}   // namespace t3



#endif // TRI_FILEPATH_HPP_INCLUDED
