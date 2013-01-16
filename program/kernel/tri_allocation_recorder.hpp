#ifndef TRI_ALLOCATION_RECORDER_HPP_INCLUDED
#define TRI_ALLOCATION_RECORDER_HPP_INCLUDED

// ---------------------------------------------
//  include
#include <iostream>
#include <array>

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
    void setFrame( const u_int frame ){
        frame_ = frame;
    }
    
    // *********************************************
    //  登録フレームを取得
    u_int getFrame() const {
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
        std::printf( "[%d]%3dbyte %s(%d)\n", frame_, size_, filename_, line_ );
    }
    
private:
    void* address_;
    std::size_t size_;
    const char* filename_;
    int line_;
    u_int frame_;
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
        const u_int frame
    );
    
    // *********************************************
    //  アロケーションポイントを削除
    void checkout(
        void* address
    );    
    
    // *********************************************
    //  一覧をダンプ
    void dump(
        const u_int start_filter_frame = 0,
        const u_int end_filter_frame = std::numeric_limits<u_int>::max()
    ) const;
    
    
private:
    enum{
        MAX_ALLOCATION_INFO = 10000
    };
    
    std::array<AllocationPointInfomation, MAX_ALLOCATION_INFO> allocate_info_;
    
};
    
}   // namespace t3





#endif // TRI_ALLOCATION_RECORDER_HPP_INCLUDED

