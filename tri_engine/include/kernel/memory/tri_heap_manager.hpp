
#ifndef TRI_HEAP_FACTORY_HPP_INCLUDED
#define TRI_HEAP_FACTORY_HPP_INCLUDED

//  include
#include "tri_heap.hpp"


namespace t3 {

///
/// �q�[�v�̎��
enum HeapIndex {
    HEAP_DEFAULT,   ///< �f�t�H���g�q�[�v
    HEAP_SYS,       ///< �V�X�e���q�[�v
    HEAP_APP,       ///< �A�v���P�[�V�����q�[�v
    HEAP_APP_EX1,   ///< �\��
    HEAP_APP_EX2,   ///< �\��
    HEAP_APP_EX3,   ///< �\��
    HEAP_SIZE       ///< �q�[�v��
};

using HeapContainer = Array<Heap, HEAP_SIZE>;

///
/// �q�[�v�}�l�[�W��
class HeapManager {

public:
    ///
    /// �q�[�v����
    static Heap* createHeap(const char* const name);

    ///
    /// �q�[�v�j��
    static void destroyHeap(Heap* heap);

    ///
    /// �f�t�H���g�q�[�v���擾
    static Heap* getDefaultHeap();

    ///
    /// �q�[�v���擾
    static Heap* getHeap(int index);

    ///
    /// �A���P�[�V���������_���v
    static void dumpAllocateInfo(
        uint32_t filter_min,
        uint32_t filter_max
    );

    ///
    /// �q�[�v�R���e�i�擾
    static HeapContainer& heaps();
    
private:
    ///
    /// �q�[�v�}�l�[�W��������
    static void initialize();

    ///
    /// �q�[�v���Ńq�[�v����
    static Heap* findHeap(const char* const name);

    ///
    /// �V�����q�[�v���쐬
    static Heap* createNewHeap(const char* const name);

private:
    ///
    /// �f�t�H���g�q�[�v
    static Heap* default_heap_;
};


};

#endif // TRI_HEAP_FACTORY_HPP_INCLUDED

