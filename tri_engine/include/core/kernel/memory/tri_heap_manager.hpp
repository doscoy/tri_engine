////////////////////////////////////////////////////////////////////////
//  Tri ENGINE
//    copyright 2012... Tri ENGINE project team.
//
//  Website: http://tri-engine.aquariuscode.com/
//  License: https://github.com/doscoy/tri_engine/wiki/License
////////////////////////////////////////////////////////////////////////
/**
    @file tri_heap_manager.hpp
    ヒープ管理.
*/
#ifndef TRI_HEAP_FACTORY_HPP_INCLUDED
#define TRI_HEAP_FACTORY_HPP_INCLUDED

//  include
#include "core/core_config.hpp"
#include "tri_heap.hpp"


TRI_CORE_NS_BEGIN


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


TRI_CORE_NS_END

#endif // TRI_HEAP_FACTORY_HPP_INCLUDED

