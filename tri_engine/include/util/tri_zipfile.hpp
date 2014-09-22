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

    bool initialize(const String& zip_file_name);
    void terminate();

    int entries() const {
        return entries_;
    }
    
    String getFileName(int index) const;

    size_t getFileSize(int index) const;

    size_t getFileSize(const String& name) const;

    bool readFile(
        int index,
        void* buffer
    );

    bool readFile(
        String& name,
        void* buffer
    );


	int find(const String &path) const;

	ZipContentsMap m_ZipContentsMap;

private:
    struct ZipDirHeader;
    struct ZipDirFileHeader;
    struct ZipLocalHeader;

    FileStream file_;

    char* data_buffer_;       // Raw data buffer.
    int entries_;         // エントリー数.

    const ZipDirFileHeader** pap_dir_;
};



}   // namespace util
}   // namespace t3




#endif
