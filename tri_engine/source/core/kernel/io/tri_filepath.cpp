////////////////////////////////////////////////////////////////////////
//  Tri ENGINE
//    copyright 2012... Tri ENGINE project team.
//
//  Website: http://tri-engine.aquariuscode.com/
//  License: https://github.com/doscoy/tri_engine/wiki/License
////////////////////////////////////////////////////////////////////////


#include "cross/cross.hpp"
#include "core/kernel/io/tri_filepath.hpp"

TRI_CORE_NS_BEGIN



String FilePath::base_filepath_;

FilePath::FilePath(
    const String& filepath
)   : filepath_(filepath)
    , filename_()
    , ext_()
{
    //  最後のピリオドを検索
    String::size_type last_period(filepath.rfind('.'));
    String::size_type last_slash(filepath.rfind('/'));

    if (last_period != String::npos) {
        //  最後のピリオドから先が拡張子
        ext_ = filepath.substr(last_period, filepath.length());
    }

    if (last_slash != String::npos) {
        //  最後のスラッシュから先がファイル名
        filename_ = filepath.substr(last_slash, filepath.length());
    }


}


FilePath::~FilePath() {
}


void FilePath::setBaseDirectory(
    String base
) {
    base_filepath_ = base;
}


String FilePath::fullpath() const {
    
    return base_filepath_ + filepath_;
}

TRI_CORE_NS_END
