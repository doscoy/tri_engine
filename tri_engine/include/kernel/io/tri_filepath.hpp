

#ifndef TRI_FILEPATH_HPP_INCLUDED
#define TRI_FILEPATH_HPP_INCLUDED

namespace t3 {
inline namespace io {

class FilePath
{
public:
    FilePath(
        const char* const filepath
    );
    
    ~FilePath();

public:
    const char* getFullPath() const {
        return filepath_;
    }
    
    const char* getBasePath() const {
        return base_filepath_;
    }

public:
    static void setBaseFilePath(
        const char* const base
    );

private:
    char filepath_[128];
    static char base_filepath_[64];
};


}   // namespace io
}   // namespace t3



#endif // TRI_FILEPATH_HPP_INCLUDED
