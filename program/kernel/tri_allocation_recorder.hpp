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
        std::cout << address_ << ":" << size_ << "  " << filename_ << "(" << line_ << ")" << std::endl; 
    }
    
private:
    void* address_;
    std::size_t size_;
    const char* filename_;
    int line_;
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
        void* address,
        std::size_t size,
        const char* const filename,
        int line
    );
    
    // *********************************************
    //  アロケーションポイントを削除
    void checkout(
        void* address
    );    
    
    // *********************************************
    //  一覧をダンプ
    void dump();
    
    
private:
    enum{
        MAX_ALLOCATION_INFO = 10000
    };
    
    std::array<AllocationPointInfomation, MAX_ALLOCATION_INFO> info_;
    
};
    
}   // namespace t3





#endif // TRI_ALLOCATION_RECORDER_HPP_INCLUDED

