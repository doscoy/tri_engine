
// ---------------------------------------------
//  include
#include "tri_allocation_recorder.hpp"
#include "tri_types.hpp"
#include "dbg/tri_dbg.hpp"
#include "util/tri_util.hpp"

//==============================================================================

namespace t3 {

// *********************************************
//  アロケーションポイントの登録
void AllocationRecorder::checkin(
    void* const address,
    const std::size_t size,
    const char* const filename,
    const int line,
    const uint32_t frame
){
    for ( auto ap = allocate_info_.begin(); ap != allocate_info_.end(); ++ap ) {
        if ( !ap->isEnable() ){
            //  アロケーション情報を保存
            ap->setAddress( address );
            ap->setSize( size );
            ap->setFilename( filename );
            ap->setLine( line );
            ap->setFrame( frame );
            
            
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
    void* const address
){
    for ( auto ap = allocate_info_.begin(); ap != allocate_info_.end(); ++ap ) {
        //  開放対象のアドレスを見つけて無効化
        if ( ap->getAddress() == address ){
            ap->setEnable( false );
            return;
        }
    }
    
    T3_PANIC( "Allocation point is not found. (%p)", address );
}


void AllocationRecorder::dump (
    const uint32_t start_filter_frame,
    const uint32_t end_filter_frame
) const {
    int no = 0;
    T3_TRACE("AllocationRecorder::dump() %d --> %d\n", start_filter_frame, end_filter_frame );
    for ( auto ap = allocate_info_.begin(); ap != allocate_info_.end(); ++ap ) {
        if ( !ap->isEnable() ){
            continue;
        }
        if ( inRange( ap->getFrame(), start_filter_frame, end_filter_frame ) ){
            no += 1;
            std::printf("%4d ", no);
            ap->dump();
        }
    }
    
}
    
}   // namespace t3

