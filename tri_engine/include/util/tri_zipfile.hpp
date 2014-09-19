#ifndef TRI_ZIPFILE_HPP_INCLUDED
#define TRI_ZIPFILE_HPP_INCLUDED

#include "base/tri_std.hpp"

namespace t3 {
inline namespace util {



using ZipContentsMap = std::map<String, int>;

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

    bool initialize(const String& resFileName);
    void terminate();

    int entries() const {
        return entries_;
    }
    
    String getFileName(int index) const;

    int getFileSize(int index) const;

    bool readFile(
        int index,
        void* buffer
    );

    bool readFile(
        String& filename,
        void* buffer
    );


	int find(const String &path) const;

	ZipContentsMap m_ZipContentsMap;

private:
    struct TZipDirHeader;
    struct TZipDirFileHeader;
    struct TZipLocalHeader;

    FileStream file_;

    char* data_buffer_;       // Raw data buffer.
    int entries_;         // エントリー数.

    const TZipDirFileHeader** m_papDir;
};



}   // namespace util
}   // namespace t3




#endif
