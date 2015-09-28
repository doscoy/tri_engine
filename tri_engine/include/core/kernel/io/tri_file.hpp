////////////////////////////////////////////////////////////////////////
//  Tri ENGINE
//    copyright 2012... Tri ENGINE project team.
//
//  Website: http://tri-engine.aquariuscode.com/
//  License: https://github.com/doscoy/tri_engine/wiki/License
////////////////////////////////////////////////////////////////////////
/**
    @file tri_file.hpp
    ファイル.
*/

#ifndef TRI_FILE_HPP_INCLUDED
#define TRI_FILE_HPP_INCLUDED


//  include
#include "core/core_config.hpp"
#include "core/utility/tri_uncopyable.hpp"
#include "core/base/tri_types.hpp"
#include "core/base/tri_std.hpp"
#include "tri_filepath.hpp"

TRI_CORE_NS_BEGIN


///
/// ファイルクラス
class File 
    : private Uncopyable
{
public:
    enum class IOMode {
        IN,
        OUT
    };
    
    enum class IOType {
        TEXT,
        BINARY
    };

public:
    ///
    /// コンストラクタ
    File();

    ///
    /// コンストラクタ
    File(
        const String& name,
        size_t size
    );

    ///
    /// コンストラクタ
    File(
        const String& name,
        size_t size,
        uint8_t* data
    );
    
    ///
    /// デストラクタ
    ~File();

public:
    ///
    ///  ファイル読み込み
    bool loadFile(
        const FilePath& filepath,
        IOMode mode = IOMode::IN,
        IOType type = IOType::BINARY
    );

    ///
    ///  ファイル読み込み
    bool loadFile(
        const char* const filepath,
        IOMode mode = IOMode::IN,
        IOType type = IOType::BINARY
    );

    ///
    ///  データ取得
    const uint8_t* data() const {
        return data_;
    }
    
    ///
    ///  データサイズ取得
    std::size_t size() const {
        return size_;
    }
    
    ///
    ///  正当性チェック
    bool isVaild() const {
        return  data_ != nullptr;
    }

    ///
    ///  名前
    const String& name() const {
        return name_;
    }

    
private:
    String name_;           ///< 名前
    std::uint8_t* data_;    ///< データ
    std::size_t size_;      ///< データサイズ
    bool auto_free_;        ///< バッファの自動解放フラグ
};
    
using FilePtr = SharedPtr<File>;
    
TRI_CORE_NS_END



#endif // TRI_FILE_HPP_INCLUDED