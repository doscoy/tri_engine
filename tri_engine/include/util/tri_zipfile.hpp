#ifndef TRI_ZIPFILE_HPP_INCLUDED
#define TRI_ZIPFILE_HPP_INCLUDED

#include "base/tri_std.hpp"

namespace t3 {



using ZipContentsMap = std::map<String, int>;

class ZipFile {

public:
    ZipFile()
        : m_ZipContentsMap()
        , file_()
        , data_buffer_(nullptr)
        , entries_(0)
        , pap_dir_(nullptr)
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
        const void* buffer
    );

    bool readFile(
        String& name,
        const void* buffer
    );


	int find(const String &path) const;


private:
    struct ZipDirHeader;
    struct ZipDirFileHeader;
    struct ZipLocalHeader;

	ZipContentsMap m_ZipContentsMap;
    FileStream file_;

    char* data_buffer_;   // データバッファ.
    int entries_;         // エントリー数.

    const ZipDirFileHeader** pap_dir_;
};


}   // namespace t3




#endif
