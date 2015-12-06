////////////////////////////////////////////////////////////////////////
//  Tri ENGINE
//    copyright 2012... Tri ENGINE project team.
//
//  Website: http://tri-engine.aquariuscode.com/
//  License: https://github.com/doscoy/tri_engine/wiki/License
////////////////////////////////////////////////////////////////////////
/**
    @file tri_filepath.hpp
    ファイルパス.
*/

#ifndef TRI_FILEPATH_HPP_INCLUDED
#define TRI_FILEPATH_HPP_INCLUDED

//  include
#include "core/core_config.hpp"
#include "cross/cross_std.hpp"

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
    const String& ext() const {
        return ext_;
    }
    
    ///
    /// パス取得
    const String& path() const {
        return filepath_;
    }
    
    ///
    /// 拡張子付きのファイル名を取得
    const String& filename() const {
        return filename_;
    }
    

public:
    ///
    /// 共通のベースディレクトリを設定
    static void setBaseDirectory(
        String const base
    );

private:
    String filepath_;               ///< ファイルパス
    String filename_;               ///< ファイル名
    String ext_;                    ///< 拡張子

    static String base_filepath_;   ///< アプリケーションのベースディレクトリ。プラットフォーム毎に変わる
};


TRI_CORE_NS_END



#endif // TRI_FILEPATH_HPP_INCLUDED
