
#include "tri_zipfile.hpp"
#include <zlib.h>
#include <cctype>			// for std::tolower

#include "kernel/memory/tri_new.hpp"
#include "util/tri_zipfile.hpp"
#include "dbg/tri_assert.hpp"
#include "util/tri_util.hpp"

namespace t3 {
inline namespace util {

namespace {

constexpr int MAX_FILE_PATH = 256;

}   // unname namespace



// --------------------------------------------------------------------------
// Basic types.
// --------------------------------------------------------------------------


// --------------------------------------------------------------------------
// ZIP file structures. Note these have to be packed.
// --------------------------------------------------------------------------

#pragma pack(1)
// --------------------------------------------------------------------------
// struct ZipFile::TZipLocalHeader					- Chapter 8, page 215
// --------------------------------------------------------------------------
struct ZipFile::TZipLocalHeader
{
    enum
    {
        SIGNATURE = 0x04034b50,
    };
    uint32_t sig;
    
    uint16_t version;
    uint16_t flag;
    
    uint16_t compression;      // Z_NO_COMPRESSION or Z_DEFLATED
    uint16_t modTime;
    
    uint16_t modDate;
    uint32_t crc32;
    uint32_t cSize;
    uint32_t ucSize;
    uint16_t fnameLen;         // Filename string follows header.
    uint16_t xtraLen;          // Extra field follows filename.
    
    
    
    bool isUseDataDescriptor() const {
        return flag & 8;
    }

};

// --------------------------------------------------------------------------
// struct ZipFile::TZipDirHeader					- Chapter 8, page 215
// --------------------------------------------------------------------------
struct ZipFile::TZipDirHeader
{
    enum
    {
        SIGNATURE = 0x06054b50
    };
    uint32_t sig;
    uint16_t nDisk;
    uint16_t nStartDisk;
    uint16_t nDirEntries;
    uint16_t totalDirEntries;
    uint32_t dirSize;
    uint32_t dirOffset;
    uint16_t cmntLen;
};

// --------------------------------------------------------------------------
// struct ZipFile::TZipDirFileHeader					- Chapter 8, page 215
// --------------------------------------------------------------------------
struct ZipFile::TZipDirFileHeader
{
    enum
    {
        SIGNATURE   = 0x02014b50
    };
    uint32_t sig;
    uint16_t verMade;
    uint16_t verNeeded;
    uint16_t flag;
    uint16_t compression;      // COMP_xxxx
    uint16_t modTime;
    uint16_t modDate;
    uint32_t crc32;
    uint32_t cSize;            // Compressed size
    uint32_t ucSize;           // Uncompressed size
    uint16_t fnameLen;         // Filename string follows header.
    uint16_t xtraLen;          // Extra field follows filename.
    uint16_t cmntLen;          // Comment field follows extra field.
    uint16_t diskStart;
    uint16_t intAttr;
    uint32_t extAttr;
    uint32_t hdrOffset;

    char* GetName() const {
        return (char *)(this + 1);
    }
    
    char* GetExtra() const {
        return GetName() + fnameLen;
    }
    
    char* GetComment() const {
        return GetExtra() + xtraLen;
    }
};

#pragma pack()


bool ZipFile::initialize(
    const std::string& resFileName
) {
    terminate();

    file_.open(resFileName.c_str(), std::ios::binary);

    // Assuming no extra comment at the end, read the whole end record.
    TZipDirHeader dh;

    file_.seekg(-(int)sizeof(dh), std::ios::end);
    std::streamoff dhOffset = file_.tellg();
    std::memset(&dh, 0, sizeof(dh));
    file_.read((char*)&dh, sizeof(dh));
    // Check
    if (dh.sig != TZipDirHeader::SIGNATURE) {
        return false;
    }
    
    // Go to the beginning of the directory.
    file_.seekg(dhOffset - dh.dirSize, std::ios::beg);
    // Allocate the data buffer, and read the whole thing.
    data_buffer_ = T3_NEW char[dh.dirSize + dh.nDirEntries*sizeof(*m_papDir)];
  
    if (!data_buffer_) {
        return false;
    }
    
    std::memset(data_buffer_, 0, dh.dirSize + dh.nDirEntries*sizeof(*m_papDir));
    file_.read(data_buffer_, dh.dirSize);

    // Now process each entry.
    char* pfh = data_buffer_;
    m_papDir = (const TZipDirFileHeader **)(data_buffer_ + dh.dirSize);

    bool success = true;

    for (int i = 0; i < dh.nDirEntries && success; i++) {
        TZipDirFileHeader &fh = *(TZipDirFileHeader*)pfh;

        // Store the address of nth file for quicker access.
        m_papDir[i] = &fh;

        // Check the directory entry integrity.
        if (fh.sig != TZipDirFileHeader::SIGNATURE) {
            success = false;
        } else {
            pfh += sizeof(fh);
        }
     
        
        
        char fileName[MAX_FILE_PATH];
        memcpy(fileName, pfh, fh.fnameLen);
        fileName[fh.fnameLen]=0;
        strToLower(fileName, MAX_FILE_PATH);
        
        std::string spath = fileName;
        m_ZipContentsMap[spath] = i;

        // Skip name, extra and comment fields.
        pfh += fh.fnameLen + fh.xtraLen + fh.cmntLen;
    }

    if (!success) {
        T3_DELETE_A(data_buffer_);
    } else {
        entries_ = dh.nDirEntries;
    }

    return success;
}

int ZipFile::find(const std::string &path) const
{
	std::string lowerCase = path;
	std::transform(
        lowerCase.begin(),
        lowerCase.end(),
        lowerCase.begin(),
        (int(*)(int))std::tolower
    );
	ZipContentsMap::const_iterator i = m_ZipContentsMap.find(lowerCase);
	if (i == m_ZipContentsMap.end()) {
		return -1;
    }

	return i->second;
}


void ZipFile::terminate()
{
    m_ZipContentsMap.clear();
    T3_DELETE_A(data_buffer_);
    entries_ = 0;
}


std::string ZipFile::getFileName(int index) const {

    std::string fileName = "";
    if (index >=0 && index < entries_) {
        char pszDest[MAX_FILE_PATH];
        std::memcpy(
            pszDest,
            m_papDir[index]->GetName(),
            m_papDir[index]->fnameLen
        );
        pszDest[m_papDir[index]->fnameLen] = '\0';
        fileName = pszDest;
	}
    
	return fileName;
}


int ZipFile::getFileSize(int index) const {
    if (index < 0 || index >= entries_) {
        return -1;
    } else {
        return m_papDir[index]->ucSize;
    }
}


bool ZipFile::readFile(
    std::string& filename,
    void *buffer
) {
    return readFile(find(filename), buffer);
}


bool ZipFile::readFile(
    int index,
    void* buffer
) {
    if (buffer == nullptr || index < 0 || index >= entries_) {
        return false;
    }

    // Quick'n dirty read, the whole file at once.
    // Ungood if the ZIP has huge files inside

    // Go to the actual file and read the local header.
    file_.seekg(m_papDir[index]->hdrOffset, std::ios::beg);
    TZipLocalHeader h;

    std::memset(&h, 0, sizeof(h));
    file_.read((char*)&h, sizeof(h));
    
    if (h.sig != TZipLocalHeader::SIGNATURE) {
        return false;
    }
    
    // Skip extra fields
    file_.seekg(h.fnameLen + h.xtraLen, std::ios::cur);
    
    if (h.compression == Z_NO_COMPRESSION) {
        // Simply read in raw stored data.
        file_.read((char*)buffer, h.cSize);
        return true;
    } else if (h.compression != Z_DEFLATED) {
        return false;
    }
    
    
    //  データディスクリプタを使っているか判定
    size_t comp_size = 0;
    size_t uncomp_size = 0;
    if (h.isUseDataDescriptor()) {
        //  Data Descriptorを使っている
        std::streamoff cur = file_.tellg();
        //  Data Descriptorを探す
        for(int i = 0; i < 9999999; ++i){
            uint8_t c;//0x08074b50
            file_.read((char*)&c, 1);

            if (c == 0x50) {
                file_.read((char*)&c, 1);
                if (c == 0x4B) {
                    file_.read((char*)&c, 1);
                    if (c == 0x7) {
                        file_.read((char*)&c, 1);
                        if (c == 0x8) {
                            //  Data Descriptor見つけた
                            struct DataDescriptor {
                                uint32_t crc32_;
                                uint32_t compressed_size_;
                                uint32_t uncompressed_size_;
                            };
                            DataDescriptor desc;
                            file_.read((char*)&desc, sizeof(DataDescriptor));
                            comp_size = desc.compressed_size_;
                            uncomp_size = desc.uncompressed_size_;
                            break;
                        }
                    }
                }
            }
        }
        // データの開始位置までシーク
        file_.seekg(cur);
        
    } else {
        //  Data Descriptorは使ってない
        comp_size = h.cSize;
        uncomp_size = h.ucSize;
    }
    
    
    //  圧縮済データを読み込む用のメモリ確保
    char* pcData = T3_NEW char[comp_size];

    if (!pcData) {
        return false;
    }
    
    //  データ読み込み
    std::memset(pcData, 0, comp_size);
    file_.read(pcData, comp_size);

    bool ret = true;

    // Setup the inflate stream.
    z_stream stream;
  
    int err;

    stream.next_in = (Bytef*)pcData;
    stream.avail_in = (uInt)comp_size;
    stream.next_out = (Bytef*)buffer;
    stream.avail_out = uncomp_size;
    stream.zalloc = (alloc_func)0;
    stream.zfree = (free_func)0;

    // Perform inflation. wbits < 0 indicates no zlib header inside the data.
    err = inflateInit2(&stream, -MAX_WBITS);
    if (err == Z_OK) {
        err = inflate(&stream, Z_FINISH);
        inflateEnd(&stream);
        if (err == Z_STREAM_END) {
            err = Z_OK;
        }
        inflateEnd(&stream);
    }
    if (err != Z_OK) {
        ret = false;
    }

    T3_DELETE_A pcData;
    return ret;
}




}   // namespace util
}   // namespace t3


