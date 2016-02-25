////////////////////////////////////////////////////////////////////////
//  Tri ENGINE
//    copyright 2012... Tri ENGINE project team.
//
//  Website: http://tri-engine.aquariuscode.com/
//  License: https://github.com/doscoy/tri_engine/wiki/License
////////////////////////////////////////////////////////////////////////
#include "core/kernel/memory/tri_memory_pool.hpp"
#include "core/debug/tri_dbg.hpp"
#include "core/utility/tri_signature.hpp"
#include "core/graphics/tri_color.hpp"


//  メモリプールの使用最大値を検証
#if DEBUG
#define TRI_PEAK_POOL_CHECK     1
#else
#define TRI_PEAK_POOL_CHECK     1
#endif

//  メモリチャンクを書き込む用に確保する追加エリアサイズ
//  アライメントが綺麗になるように余裕をもって確保する
#define TRI_MEMPOOL_CHUNK_AREA_SIZE     32
static_assert(TRI_MEMPOOL_CHUNK_AREA_SIZE >= sizeof(t3::MemoryChunk), "error");

#define TRI_MEMPOOL_CHUNK_DIVISION_LIMIT_SIZE (TRI_MEMPOOL_CHUNK_AREA_SIZE + 12)


TRI_CORE_NS_BEGIN


namespace  {
    
    
inline size_t roundup(
    size_t size,
    int allign
){
    return (size + ( allign - 1 )) &~ ( allign - 1 );
}

//  メモリチャンク用のシグネチャ
constexpr uint32_t CHUNK_SIGNATURE = t3::makeSignature('M', 'C', 'N', 'K');

    
}   // unname namespace




bool MemoryChunk::isValidate() const {
    return signature_ == CHUNK_SIGNATURE;
}


MemoryChunk* MemoryChunk::create(
    void* addr,
    size_t size,
    MemoryChunk* prev,
    MemoryChunk* next
) {
    MemoryChunk* chunk = reinterpret_cast<MemoryChunk*>(addr);
    chunk->size(size);
    chunk->chainPrev(prev);
    chunk->chainNext(next);
    chunk->signature_ = CHUNK_SIGNATURE;
    
    return chunk;
}


MemoryPool::MemoryPool(size_t size)
    : pool_(nullptr)
    , use_chain_(nullptr)
    , free_chain_(nullptr)
    , pool_size_(0)
    , total_use_size_(0)
    , peak_use_size_(0)
{
    initialize(size);
}

MemoryPool::~MemoryPool() {
    std::free(pool_);
}


bool MemoryPool::initialize(size_t pool_size) {
    T3_ASSERT(pool_ == nullptr);

    //  メモリプール全体のメモリを最初に確保
    pool_ = std::malloc(pool_size);
    if (pool_ == nullptr) {
        //  ここで確保できないと元も子もない
        return false;
    }

    //  フリーリスト作成
    free_chain_ = MemoryChunk::create(
        pool_,
        pool_size,
        nullptr,
        nullptr
    );

    //  プール全体のサイズを保存
    pool_size_ = pool_size;
    
    //  プール使用準備完了
    return true;
}


void* MemoryPool::allocate(
    size_t size,
    int align
) {
    //  チャンクを含んだサイズをリクエスト
    size_t req_size = size + TRI_MEMPOOL_CHUNK_AREA_SIZE;

    //  アライメントを考慮
    req_size = roundup(req_size, align);
    
    //  フリーチャンクを探す
    MemoryChunk* target_chank = findFreeChunk(req_size);

    void* addr = nullptr;
    //  候補が見つかった
    if (target_chank) {

        //  チャンクを使用中に切り替える
        useChunk(target_chank, req_size);
        addr = reinterpret_cast<void*>(
            reinterpret_cast<uintptr_t>(target_chank) + TRI_MEMPOOL_CHUNK_AREA_SIZE
        );
    }
    
#if TRI_PEAK_POOL_CHECK
    //  一番メモリ使った瞬間を記録
    size_t total_use = totalUseSize();
    if (total_use > peak_use_size_) {
        peak_use_size_ = total_use;
    }
#endif

    return addr;
}

void MemoryPool::deallocate(void* mem) {
    MemoryChunk* chunk = reinterpret_cast<MemoryChunk*>(
        reinterpret_cast<uintptr_t>(mem) - TRI_MEMPOOL_CHUNK_AREA_SIZE
    );
    T3_ASSERT(chunk->isValidate());
    freeChunk(chunk);
}



MemoryChunk* MemoryPool::findFreeChunk(
    size_t request_size
) {
    MemoryChunk* chunk = free_chain_;

    //  リクエスト以上の空き領域を持ったチャンクを探す
    MemoryChunk* candidate = nullptr;
    size_t min_sa = std::numeric_limits<size_t>::max();
    while (chunk) {
        //  サイズ判定
        int surplus = static_cast<int>(chunk->size()) - static_cast<int>(request_size);
        if (surplus > 0) {
            if (surplus < TRI_MEMPOOL_CHUNK_DIVISION_LIMIT_SIZE) {
                //  ほぼぴったりサイズなので即決定
                //  チャンクを分割するほどサイズが無いので
                //  結局このチャンクのみが使われるから
                candidate = chunk;
                break;
            }
            else if (surplus < min_sa) {
                //  リクエスト以上のサイズを持ったチャンク発見
                min_sa = surplus;
                candidate = chunk;
            }
        }
        
        //  次のチャンク
        chunk = chunk->next();
    }
 
    if (candidate == nullptr) {
    
        printf("not found.");
    }
    
    return candidate;
}

void MemoryPool::useChunk(
    MemoryChunk* chunk,
    size_t request_size
) {
    T3_ASSERT_MSG(chunk->size() >= request_size, "%u >= %u", chunk->size(), request_size);
    
    //  リクエストされたサイズとチャンクのサイズの余りから
    //  新しいチャンクを作成
    size_t surplus = chunk->size() - request_size;

    //  余りで新しいチャンクを作れるか判定
    if (surplus >= TRI_MEMPOOL_CHUNK_DIVISION_LIMIT_SIZE) {
        //  新しいチャンクを作れるので作る
        MemoryChunk* surplus_chunk = MemoryChunk::create(
            reinterpret_cast<MemoryChunk*>(reinterpret_cast<intptr_t>(chunk) + request_size),
            surplus,
            chunk->prev(),
            chunk->next()
        );
        
        //  抜けるチャンクがルートだったら新しいチャンクをルートにする
        if (chunk == free_chain_) {
            //  抜けるチャンクがルートだった
            setFreeChainRoot(surplus_chunk);
        }
    
        
        //  チャンクのサイズが変わった
        //  リクエストされたサイズがチャンクのサイズとなる
        chunk->size(request_size);

    } else {
        //  新しいチャンクを作る余裕が無い
        //  単純にチェインから自分を抜く
        MemoryChunk* prev_chunk = chunk->prev();
        if (prev_chunk) {
            prev_chunk->chainNext(chunk->next());
        } else {
            //  prev_chunkがnullptrということはこのチャンクは
            //  チェインのルートだった
            setFreeChainRoot(chunk->next());
        }
    }
    
    //  使用中のチェインの先頭につなぐ
    chunk->chainNext(use_chain_);
    setUseChainRoot(chunk);
    
    //  使用中サイズを更新
    total_use_size_ += chunk->size();
}


void MemoryPool::freeChunk(
    MemoryChunk* chunk
) {
    //  使用中チェインから外す
    MemoryChunk* prev_chunk = chunk->prev();

    if (prev_chunk) {
        prev_chunk->chainNext(chunk->next());
    } else {
        //  prev_chunkがnullptrということはこのチャンクがルートだった
        setUseChainRoot(chunk->next());
    }
    
    //  完全にチェインから外れた
    chunk->chainPrev(nullptr);
    chunk->chainNext(nullptr);

    //  使用中サイズを更新
    total_use_size_ -= chunk->size();

    //  フリーチェインに繋ぎ直す
    mergeFreeChain(chunk);
}

void MemoryPool::mergeFreeChain(
    MemoryChunk* chunk
) {
    MemoryChunk* prev_chain = nullptr; // 前に連続して繋がるチェイン
    MemoryChunk* next_chain = nullptr; // 後ろに連続して繋がるチェイン
    
    //  チェインを走査して連続するチャンクを探す
    MemoryChunk* search = free_chain_;
    while (search) {
        if (prev_chain == nullptr) {
            if (search->endAddress() == chunk) {
                //  前に連続して繋がるチャンク見つけた
                prev_chain = search;
            }
        }
        if (next_chain == nullptr) {
            if (search == chunk->endAddress()) {
                //  次に連続して繋がるチャンクを見つけた
                next_chain = search;
            }
        }
        
        if (prev_chain && next_chain) {
            break;
        }
        
        search = search->next();
    }

    //  次に繋がるチャンクがある
    if (next_chain) {
    
        chunk->chainNext(next_chain->next());
        chunk->chainPrev(next_chain->prev());
        chunk->size(next_chain->size() + chunk->size());

        if (next_chain == free_chain_) {
            //  次に繋がるチェインがルートだった場合
            //  ルートを変える
            setFreeChainRoot(chunk);
        }
        
        
        //  その上で一旦フリーチェインから外す
        //  再度繋ぎ直す為
        MemoryChunk* prev = chunk->prev();
        if (prev) {
            prev->chainNext(chunk->next());
        } else {
            setFreeChainRoot(chunk->next());
        }
        
    }
    
    
    
    
    
    //  前に繋がるチャンクがある
    if (prev_chain) {

        //  基本的にチェインから外れた状態でくるので
        //  双方向にnullだが、直前の「次に繋がるチャンク」が
        //  ある場合はここでチェインがつながっている可能性がある
        MemoryChunk* prev = chunk->prev();
        MemoryChunk* next = chunk->next();
        if (prev) {
            prev->chainNext(next);

        } else if (next) {
            next->chainPrev(prev);
        }
        
        //  自分がルートだった場合次をルートにする
        if (chunk == free_chain_) {
            setFreeChainRoot(next);
        }
        
        //  これで自分は一旦チェインから完全に外れた
        //  前に繋がるチェインに混ざる
        prev_chain->size(prev_chain->size() + chunk->size());
    } else {
        //  前に繋がるチャンクが無い場合は
        //  ルートにつなげる
        if (chunk != free_chain_) {
            chunk->chainNext(free_chain_);
            setFreeChainRoot(chunk);
        } else {
            //  チャンクはフリーチェインルートだった
            T3_ASSERT(chunk->prev() == nullptr);
        }
        
    }
}

void MemoryPool::setUseChainRoot(
    MemoryChunk* chunk
) {
    use_chain_ = chunk;
    if (chunk) {
        chunk->chainPrev(nullptr);
    }
}
void MemoryPool::setFreeChainRoot(
    MemoryChunk* chunk
) {
    free_chain_ = chunk;
    if (chunk) {
        chunk->chainPrev(nullptr);
    }
}

size_t MemoryPool::calcChunkSize(
    const MemoryChunk* const root
) const {
    size_t total_size = 0;
    const MemoryChunk* chunk = root;
    while (chunk) {
        total_size += chunk->size();
        chunk = chunk->next();
    }
    return total_size;
}



void renderMemoryPool(MemoryPool& pool) {
    int limit_x = 310;
    int now = -320;
    float line_y = 120;
    float rect_size = 1;
    float render_ratio = 0.001f;
    
    //  チェイン描画用の色設定
    t3::Color free_color = t3::color_sample::skyblue();
    t3::Color use_color = t3::color_sample::orange();
    
    //  フリーチェインを描画
    t3::MemoryChunk* free = pool.freeChainRoot();

    while (free) {
        size_t size = static_cast<std::size_t>(free->size() * render_ratio);
        
        while (size + now > limit_x) {
            int diff = limit_x-now;
            
            t3::drawRectangleMinSize(
                t3::Vec2(static_cast<float>(now), line_y),
                t3::Vec2(static_cast<float>(diff), rect_size),
                free_color
            );
            now = -320;
            size -= diff;
            line_y -= rect_size;
        }
        t3::drawRectangleMinSize(
            t3::Vec2(static_cast<float>(now), line_y),
            t3::Vec2(static_cast<float>(size), rect_size),
            free_color
        );
        now += size;

        free = free->next();
    }
    
    line_y -= 2;

    //  ユーズチェインを描画
    t3::MemoryChunk* use = pool.useChainRoot();
    now = -320;
    while (use) {
        size_t size = static_cast<std::size_t>(use->size() * render_ratio);
        while (size + now > limit_x) {
            int diff = limit_x-now;
            
            t3::drawRectangleMinSize(
                t3::Vec2(static_cast<float>(now), line_y),
                t3::Vec2(static_cast<float>(diff), rect_size),
                use_color
            );
            now = -320;
            size -= diff;
            line_y -= rect_size;
        }
        t3::drawRectangleMinSize(
            t3::Vec2(static_cast<float>(now), line_y),
            t3::Vec2(static_cast<float>(size), rect_size),
            use_color
        );
        now += size;


        use = use->next();
    }
}


TRI_CORE_NS_END



