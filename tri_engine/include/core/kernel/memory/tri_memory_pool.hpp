////////////////////////////////////////////////////////////////////////
//  Tri ENGINE
//    copyright 2012... Tri ENGINE project team.
//
//  Website: http://tri-engine.aquariuscode.com/
//  License: https://github.com/doscoy/tri_engine/wiki/License
////////////////////////////////////////////////////////////////////////
/**
    @file tri_memory_pool.hpp
    メモリプール.
*/

#ifndef TRI_MEMORY_POOL_HPP_INCLUDED
#define TRI_MEMORY_POOL_HPP_INCLUDED

//  include
#include "core/core_config.hpp"
#include "core/utility/tri_uncopyable.hpp"
#include "core/base/tri_std.hpp"


TRI_CORE_NS_BEGIN


///
/// メモリチャンク
class MemoryChunk final {
    ///
    /// シグネチャ
    uint32_t signature_;

    ///
    /// メモリサイズ
    size_t size_;

    ///
    /// 直前のアドレス
    MemoryChunk* prev_;

    ///
    /// 直後のアドレス
    MemoryChunk* next_;

private:
    ///
    /// コンストラクタ
    MemoryChunk();
    
    ///
    /// デストラクタ
    ~MemoryChunk();

public:
    
    ///
    /// 有効判定
    bool isValidate() const;

    ///
    /// 次のチャンクをつなげる
    void chainNext(
        MemoryChunk* next
    ) {
        next_ = next;
        if (next) {
            next->prev_ = this;
        }
    }
    
    ///
    /// 前のチャンクをつなげる
    void chainPrev(
        MemoryChunk* prev
    ) {
        prev_ = prev;
        if (prev) {
            prev->next_ = this;
        }
    }
    
    ///
    /// 次のチャンク取得
    MemoryChunk* next() {
        return next_;
    }
    
    ///
    /// 次のチャンク取得
    const MemoryChunk* next() const {
        return next_;
    }
    
    ///
    /// 前のチャンク取得
    MemoryChunk* prev() {
        return prev_;
    }
    
    ///
    /// 前のチャンク取得
    const MemoryChunk* prev() const {
        return prev_;
    }
    
    ///
    /// チャンクの終端アドレス取得
    void* endAddress() const {
        return reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(this) + size_);
    }
    
    ///
    /// チャンクサイズ取得
    size_t size() const {
        return size_;
    }
    
    ///
    /// チャンクサイズ設定
    void size(size_t s) {
        size_ = s;
    }
    
    ///
    /// 新たなチャンクを生成
    static MemoryChunk* create(
        void* addr,
        size_t size,
        MemoryChunk* prev,
        MemoryChunk* next
    );
};



class MemoryPool final {
public:
    explicit MemoryPool(size_t size);
    ~MemoryPool();
    
public:
    void* allocate(size_t size, int align = 16);
    void deallocate(void* mem);

public:

    MemoryChunk* useChainRoot() {
        return use_chain_;
    }
    
    MemoryChunk* freeChainRoot() {
        return free_chain_;
    }
    
    size_t totalFreeSize() const {
        return pool_size_ - totalUseSize();
    }
    
    size_t totalUseSize() const {
        return total_use_size_;
    }
    
    size_t peakUseSize() const {
        return peak_use_size_;
    }

private:
    MemoryChunk* findFreeChunk(size_t request_size);
    void useChunk(
        MemoryChunk* chunk,
        size_t request_size
    );
    
    void freeChunk(
        MemoryChunk* chunk
    );
    
    void mergeFreeChain(
        MemoryChunk* chunk
    );
    
    void setUseChainRoot(
        MemoryChunk* chunk
    );
    
    void setFreeChainRoot(
        MemoryChunk* chunk
    );
    
    size_t calcChunkSize(
        const MemoryChunk* const root
    ) const;
    
    
    bool initialize(size_t pool_size);

private:
    void* pool_;
    MemoryChunk* use_chain_;
    MemoryChunk* free_chain_;
    size_t pool_size_;
    size_t total_use_size_;
    size_t peak_use_size_;
};



void renderMemoryPool(MemoryPool& pool);


TRI_CORE_NS_END


#endif // TRI_MEMORY_POOL_HPP_INCLUDED