/**
    @file tri_filepath.hpp
    ファイルパス.
*/

#ifndef TRI_FILEPATH_HPP_INCLUDED
#define TRI_FILEPATH_HPP_INCLUDED

//  include
#include "core/core_config.hpp"
#include "core/base/tri_std.hpp"


TRI_CORE_NS_BEGIN


///
/// ファイルパスクラス
class FilePath {
public:
    ///
    /// コンストラクタ
    FilePath(
       const String& filepath
    );
    
    ///
    /// デストラクタ
    ~FilePath();

public:
    ///
    /// フルパス取得
    String fullpath() const;
    
    ///
    /// 拡張子取得
    String ext() const;
    
    ///
    /// パス取得
    const String& path() const;
    
    ///
    /// 拡張子無しのファイル名を取得
    String getFileNameNotExt() const;
    
public:
    ///
    /// 共通のベースディレクトリを設定
    static void setBaseDirectory(
        String const base
    );

private:
    String filepath_;               ///< ファイルパス
    static String base_filepath_;   ///< ベースディレクトリ
};


TRI_CORE_NS_END



#endif // TRI_FILEPATH_HPP_INCLUDED
