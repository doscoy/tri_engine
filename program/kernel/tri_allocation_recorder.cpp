
// ---------------------------------------------
//  include
#include "tri_allocation_recorder.hpp"
#include "tri_types.hpp"
#include "../dbg/tri_dbg.hpp"
#include "../util/tri_util.hpp"

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
    for ( auto ap = allocate_info_.begin(); ap != allocate_info_.end(); ++ap ) {
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
    for ( auto ap = allocate_info_.begin(); ap != allocate_info_.end(); ++ap ) {
        //  開放対象のアドレスを見つけて無効化
        if ( ap->getAddress() == address ){
            ap->setEnable( false );
        }
    }
    
    T3_PANIC( "Allocation point is not found." );
}


void AllocationRecorder::dump(
    const u_int start_filter_frame,
    const u_int end_filter_frame
){
    for ( auto ap = allocate_info_.begin(); ap != allocate_info_.end(); ++ap ) {
        if ( !ap->isEnable() ){
            continue;
        }
        if ( inRange( ap->getFrame(), start_filter_frame, end_filter_frame ) ){
            ap->dump();
        }
    }
    
}
    
}   // namespace t3

