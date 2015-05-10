#ifndef TRI_ZIPFILE_HPP_INCLUDED
#define TRI_ZIPFILE_HPP_INCLUDED

//  include
#include "base/tri_std.hpp"

namespace t3 {

///
/// コンテンツのマップ
using ZipContentsMap = std::map<String, int>;

///
/// Zipアーカイブ
class ZipFile {

public:
    ///
    /// コンストラクタ
    ZipFile()
        : zip_contents_map_()
        , file_()
        , data_buffer_(nullptr)
        , entries_(0)
        , pap_dir_(nullptr)
    {}
    
    ///
    /// デストラクタ
    ~ZipFile() {
        terminate();
        file_.close();
    }

    ///
    /// 初期化
    bool initialize(
        const String& zip_file_name ///< zipファイル名
    );
    
    ///
    /// 後片付け
    void terminate();

    ///
    /// コンテンツ数
    int entries() const {
        return entries_;
    }
    
    ///
    /// ファイル名を取得
    String getFileName(int index) const;

    ///
    /// ファイルサイズを取得
    size_t getFileSize(
        int index   ///< ファイルインデックス
    ) const;

    ///
    /// ファイルサイズを取得
    size_t getFileSize(
        const String& name  ///< ファイル名
    ) const;

    ///
    /// ファイル読み込み
    bool readFile(
        int index,
        const void* buffer
    );

    ///
    /// ファイル読み込み
    bool readFile(
        String& name,
        const void* buffer
    );


	///
    /// ファイル検索
    int find(
        const String &path  ///< パス
    ) const;


private:
    struct ZipDirHeader;
    struct ZipDirFileHeader;
    struct ZipLocalHeader;

	///
    /// コンテンツマップ
    ZipContentsMap zip_contents_map_;
    
    ///
    /// ファイルストリーム
    FileStream file_;

    ///
    /// データバッファ
    char* data_buffer_;
    
    ///
    /// エントリー数
    int entries_;

    ///
    ///
    const ZipDirFileHeader** pap_dir_;
};


}   // namespace t3




#endif
