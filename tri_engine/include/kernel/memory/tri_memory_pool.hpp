#ifndef TRI_MEMORY_POOL_HPP_INCLUDED
#define TRI_MEMORY_POOL_HPP_INCLUDED

#include "util/tri_uncopyable.hpp"
#include "base/tri_std.hpp"

namespace t3 {
    
class MemoryChunk final {

    uint32_t signature_;
    uint32_t size_;
    MemoryChunk* prev_;
    MemoryChunk* next_;

private:
    MemoryChunk();
    ~MemoryChunk();

public:
    
    bool isValidate() const;

    void chainNext(
        MemoryChunk* next
    ) {
        next_ = next;
        if (next) {
            next->prev_ = this;
        }
    }
    
    void chainPrev(
        MemoryChunk* prev
    ) {
        prev_ = prev;
        if (prev) {
            prev->next_ = this;
        }
    }
    
    MemoryChunk* next() {
        return next_;
    }
    
    const MemoryChunk* next() const {
        return next_;
    }
    
    MemoryChunk* prev() {
        return prev_;
    }
    
    const MemoryChunk* prev() const {
        return prev_;
    }
    
    void* endAddress() const {
        return reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(this) + size_);
    }
    
    size_t size() const {
        return size_;
    }
    
    void size(size_t s) {
        size_ = s;
    }
    
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
    void* allocate(size_t size, int align = 8);
    void deallocate(void* mem);

public:

    MemoryChunk* useChainRoot() {
        return use_chain_;
    }
    
    MemoryChunk* freeChainRoot() {
        return free_chain_;
    }
    
    size_t totalFreeSize() const;
    size_t totalUseSize() const;
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
    size_t peak_use_size_;
};



void renderMemoryPool(MemoryPool& pool);


}   // namespace t3


#endif // TRI_MEMORY_POOL_HPP_INCLUDED