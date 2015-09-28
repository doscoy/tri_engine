////////////////////////////////////////////////////////////////////////
//  Tri ENGINE
//    copyright 2012... Tri ENGINE project team.
//
//  Website: http://tri-engine.aquariuscode.com/
//  License: https://github.com/doscoy/tri_engine/wiki/License
////////////////////////////////////////////////////////////////////////
/**
    @file tri_heap.hpp
    ヒープ.
*/

#ifndef TRI_HEAP_HPP_INCLUDED
#define TRI_HEAP_HPP_INCLUDED

//  include
#include "cross/cross_sdk.hpp"
#include "core/core_config.hpp"
#include "core/base/tri_std.hpp"
#include "core/kernel/process/tri_mutex.hpp"
#include "core/utility/tri_uncopyable.hpp"
#include "core/utility/tri_bytesize.hpp"
#include "tri_memory_pool.hpp"

TRI_CORE_NS_BEGIN


//
#define NAME_LENGTH  6
extern MemoryPool* heapMemoryPool();

//  前方宣言
class AllocHeader;


///
/// ヒープ
class Heap
    : private Uncopyable
{
public:
    ///
    /// コンストラクタ
    Heap();

    ///
    /// デストラクタ
    ~Heap() = default;

public:
    ///
    /// ヒープ名取得
    const char* name() const {
        return heap_name_;
    }
    
    ///
    /// ヒープ番号取得
    int no() const {
        return heap_no_;
    }

    ///
    /// ヒープを有効化
    void activate(
        const char* const name,  ///< 名前
        int no                   ///< 有効にするヒープ番号
    );

    ///
    /// ヒープを無効化
    void deactivate();

    ///
    /// 有効判定
    bool isActive() const {
        return active_;
    }

    ///
    /// メモリ確保
    void* allocate(const size_t size);

    ///
    ///　メモリ確保
    void* allocate(
        const size_t size,
        const char* const file_name,
        const int line
    );

    ///
    /// メモリ解放
    static void  deallocate(void* mem);

    ///
    /// ヒープ情報をダンプ
    void dump(
        uint32_t filter_min,
        uint32_t filter_max
    ) const;

    ///    
    ///  １度のメモリ割り当てピーク
    ByteSize peak() {
        return peak_;
    }

    ///    
    ///  トータルのメモリ割り当て量
    ByteSize allocated() {
        return allocated_;
    }
    
    ///
    /// ノード数取得
    uint32_t nodeCount() {
        return node_count_;
    }

    ///
    /// ミューテックス取得
    static Mutex& mutex() {
        return mutex_;
    }
    
private:
    ///
    /// メモリ解放
    void deallocate(AllocHeader* header);

private:
    bool active_;                   ///< 有効判定フラグ
    char heap_name_[NAME_LENGTH];   ///< ヒープ名
    int heap_no_;                   ///< ヒープ番号
    ByteSize allocated_;            ///< アロケート済みサイズ
    ByteSize peak_;                 ///< 一度で確保された最大サイズ
    uint32_t node_count_;           ///< ノード数
    AllocHeader* head_alloc_;       ///< ノードのルート

    Heap* first_child_;             ///< ヒープリストの先頭
    Heap* next_siblind_;            ///< 次のヒープ
    Heap* prev_sibling_;            ///< 前のヒープ

    static Mutex mutex_;            ///< ミューテックス
};



TRI_CORE_NS_END


#endif // TRI_HEAP_HPP_INCLUDED
