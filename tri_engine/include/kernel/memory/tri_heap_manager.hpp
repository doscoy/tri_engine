
#ifndef TRI_HEAP_FACTORY_HPP_INCLUDED
#define TRI_HEAP_FACTORY_HPP_INCLUDED

//  include
#include "tri_heap.hpp"


namespace t3 {

///
/// ヒープの種類
enum HeapIndex {
    HEAP_DEFAULT,   ///< デフォルトヒープ
    HEAP_SYS,       ///< システムヒープ
    HEAP_APP,       ///< アプリケーションヒープ
    HEAP_APP_EX1,   ///< 予備
    HEAP_APP_EX2,   ///< 予備
    HEAP_APP_EX3,   ///< 予備
    HEAP_SIZE       ///< ヒープ数
};

using HeapContainer = Array<Heap, HEAP_SIZE>;

///
/// ヒープマネージャ
class HeapManager {

public:
    ///
    /// ヒープ生成
    static Heap* createHeap(const char* const name);

    ///
    /// ヒープ破棄
    static void destroyHeap(Heap* heap);

    ///
    /// デフォルトヒープを取得
    static Heap* getDefaultHeap();

    ///
    /// ヒープを取得
    static Heap* getHeap(int index);

    ///
    /// アロケーション情報をダンプ
    static void dumpAllocateInfo(
        uint32_t filter_min,
        uint32_t filter_max
    );

    ///
    /// ヒープコンテナ取得
    static HeapContainer& heaps();
    
private:
    ///
    /// ヒープマネージャ初期化
    static void initialize();

    ///
    /// ヒープ名でヒープ検索
    static Heap* findHeap(const char* const name);

    ///
    /// 新しいヒープを作成
    static Heap* createNewHeap(const char* const name);

private:
    ///
    /// デフォルトヒープ
    static Heap* default_heap_;
};


};

#endif // TRI_HEAP_FACTORY_HPP_INCLUDED

