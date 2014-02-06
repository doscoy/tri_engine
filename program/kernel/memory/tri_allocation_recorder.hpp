#ifndef TRI_ALLOCATION_RECORDER_HPP_INCLUDED
#define TRI_ALLOCATION_RECORDER_HPP_INCLUDED

// ---------------------------------------------
//  include
#include <iostream>
#include <array>
#include <cstdint>

//==============================================================================

namespace t3 {
    
// ---------------------------------------------
//  アロケートした場所の情報
class AllocationPointInfomation
{
public:
    // *********************************************
    //  コンストラクタ
    AllocationPointInfomation()   
        : address_( nullptr )
        , size_( 0 )
        , filename_( nullptr )
        , line_( -1 )
        , frame_( 0 )
        , enable_( false )
    {}
    
public:
    
    // *********************************************
    //  アドレス設定
    void setAddress( void* address ){
        address_ = address;
    }
    
    // *********************************************
    //  アドレス取得
    void* getAddress() const {
        return address_;
    }
    
    // *********************************************
    //  確保サイズ設定
    void setSize( std::size_t size ){
        size_ = size;
    }
    
    // *********************************************
    //  ファイル名設定
    void setFilename( const char* const filename ){
        filename_ = filename;
    }
    
    // *********************************************
    //  行番号設定
    void setLine( int line ){
        line_ = line;
    }
    
    // *********************************************
    //  登録フレームを保持
    void setFrame( const uint32_t frame ){
        frame_ = frame;
    }
    
    // *********************************************
    //  登録フレームを取得
    uint32_t getFrame() const {
        return frame_;
    }
    
    // *********************************************
    //  有効かどうか設定
    void setEnable( bool e ){
        enable_ = e;
    }
    
    // *********************************************
    //  有効判定
    bool isEnable() const {
        return enable_;
    }
    
    // *********************************************
    //  情報をダンプ
    void dump() const {
        std::printf( "[%d]%3dbyte %s(%d)\n", frame_, static_cast<int>(size_), filename_, line_ );
    }
    
private:
    void* address_;
    std::size_t size_;
    const char* filename_;
    int line_;
    uint32_t frame_;
    bool enable_;
};

// ---------------------------------------------
//  アロケーションレコーダ
class AllocationRecorder {
public:
    AllocationRecorder(){
        
    }

    
    ~AllocationRecorder(){
        
    }


public:
    // *********************************************
    //  アロケーションポイントを登録
    void checkin(
        void* const address,
        const std::size_t size,
        const char* const filename,
        const int line,
        const uint32_t frame
    );
    
    // *********************************************
    //  アロケーションポイントを削除
    void checkout(
        void* address
    );    
    
    // *********************************************
    //  一覧をダンプ
    void dump(
        const uint32_t start_filter_frame = 0,
        const uint32_t end_filter_frame = std::numeric_limits<uint32_t>::max()
    ) const;
    
    
private:
    enum{
        MAX_ALLOCATION_INFO = 200000
    };
    
    std::array<AllocationPointInfomation, MAX_ALLOCATION_INFO> allocate_info_;
    
};
    
}   // namespace t3





#endif // TRI_ALLOCATION_RECORDER_HPP_INCLUDED

