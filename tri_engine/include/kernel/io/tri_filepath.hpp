

#ifndef TRI_FILEPATH_HPP_INCLUDED
#define TRI_FILEPATH_HPP_INCLUDED

#include <string>



namespace t3 {
inline namespace io {

class FilePath {
public:
    FilePath(
        std::string filepath
    );
    
    ~FilePath();

public:
    std::string getFullPath() const;
    
    std::string getExt() const;
    
    std::string getFileNameNotExt() const;
    

public:
    static void setResourceDirectory(
        std::string const base
    );

private:
    std::string filepath_;
    static std::string base_filepath_;
};


}   // namespace io
}   // namespace t3



#endif // TRI_FILEPATH_HPP_INCLUDED
