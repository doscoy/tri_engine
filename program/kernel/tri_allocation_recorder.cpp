
// ---------------------------------------------
//  include
#include "tri_allocation_recorder.hpp"
#include "tri_types.hpp"
#include "../dbg/tri_dbg.hpp"


//==============================================================================

namespace t3 {

// *********************************************
//  アロケーションポイントの登録
void AllocationRecorder::checkin(
    void* address,
    std::size_t size,
    const char* const filename,
    int line
){
    for ( auto ap = info_.begin(); ap != info_.end(); ++ap ) {
        if ( !ap->isEnable() ){
            //  アロケーション情報を保存
            ap->setAddress( address );
            ap->setSize( size );
            ap->setFilename( filename );
            ap->setLine( line );
            
            //  ここはもう使ってますよ
            ap->setEnable( true );
            return;
        }
    }
    
    T3_PANIC( "Allocation recorder size over." );
}

    
// *********************************************
//  アロケーションポイントを削除
void AllocationRecorder::checkout(
    void* address
){
    for ( auto ap = info_.begin(); ap != info_.end(); ++ap ) {
        //  開放対象のアドレスを見つけて無効化
        if ( ap->getAddress() == address ){
            ap->setEnable( false );
        }
    }
    
    T3_PANIC( "Allocation point is not found." );
}


void AllocationRecorder::dump()
{
    for ( auto ap = info_.begin(); ap != info_.end(); ++ap ) {
        ap->dump();
    }
    
}
    
}   // namespace t3

