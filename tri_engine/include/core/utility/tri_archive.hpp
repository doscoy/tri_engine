/**
    @file tri_archive.hpp
    アーカイブ管理.
*/

#ifndef TRI_ARCHIVE_HPP_INCLUDED
#define TRI_ARCHIVE_HPP_INCLUDED

//  include
#include "core/core_config.hpp"
#include "tri_zipfile.hpp"
#include "core/base/tri_std.hpp"
#include "core/kernel/io/tri_file.hpp"


TRI_CORE_NS_BEGIN


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

TRI_CORE_NS_END


#endif // TRI_ARCHIVE_HPP_INCLUDED
