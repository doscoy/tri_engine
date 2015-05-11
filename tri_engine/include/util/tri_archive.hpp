/**
    @file tri_archive.hpp
    アーカイブ管理.
*/

#ifndef TRI_ARCHIVE_HPP_INCLUDED
#define TRI_ARCHIVE_HPP_INCLUDED

//  include
#include "tri_zipfile.hpp"
#include "base/tri_std.hpp"
#include "kernel/io/tri_file.hpp"


namespace t3 {

///
/// アーカイブ管理
class Archive {

public:
    ///
    /// コンストラクタ
    Archive() {}

    ///
    /// デストラクタ
    ~Archive() {}


public:
    /// アーカイブファイル読み込み
    void load(
        const String& arcname   ///< アーカイブ名
    );

    ///
    /// アーカイブの展開.
    /// 全展開
    void decompressAll();

    ///
    /// ファイル取得
    const File* file(
        const String& filename  ///< ファイル名
    );

private:
    ZipFile zip_;   ///< zipファイル
    Vector<File*> files_;   ///< 管理しているファイル
};


}   // namespace t3


#endif // TRI_ARCHIVE_HPP_INCLUDED
