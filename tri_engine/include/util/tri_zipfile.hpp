#ifndef TRI_ZIPFILE_HPP_INCLUDED
#define TRI_ZIPFILE_HPP_INCLUDED

#include <fstream>
#include <map>
#include <string>


namespace t3 {
inline namespace util {



using ZipContentsMap = std::map<std::string, int>;

class ZipFile {

public:
    ZipFile()
        : entries_(0)
        , file_(nullptr)
        , data_buffer_(nullptr)
    {
    }
    
    ~ZipFile() {
        terminate();
        file_.close();
    }

    bool initialize(const std::string& resFileName);
    void terminate();

    int entries() const {
        return entries_;
    }
    
    std::string getFileName(int index) const;

    int getFileSize(int index) const;

    bool readFile(
        int index,
        void* buffer
    );

    bool readFile(
        std::string& filename,
        void* buffer
    );


	int find(const std::string &path) const;

	ZipContentsMap m_ZipContentsMap;

private:
    struct TZipDirHeader;
    struct TZipDirFileHeader;
    struct TZipLocalHeader;

    std::ifstream file_;

    char* data_buffer_;       // Raw data buffer.
    int entries_;         // エントリー数.

    const TZipDirFileHeader** m_papDir;
};



}   // namespace util
}   // namespace t3




#endif
