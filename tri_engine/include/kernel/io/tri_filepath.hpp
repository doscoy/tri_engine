/**
    @file tri_filepath.hpp
    ファイルパス.
*/

#ifndef TRI_FILEPATH_HPP_INCLUDED
#define TRI_FILEPATH_HPP_INCLUDED

//  include
#include "base/tri_std.hpp"


namespace t3 {

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
    String getFullPath() const;
    
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


}   // namespace t3



#endif // TRI_FILEPATH_HPP_INCLUDED
