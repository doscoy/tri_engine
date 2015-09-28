////////////////////////////////////////////////////////////////////////
//  Tri ENGINE
//    copyright 2012... Tri ENGINE project team.
//
//  Website: http://tri-engine.aquariuscode.com/
//  License: https://github.com/doscoy/tri_engine/wiki/License
////////////////////////////////////////////////////////////////////////


#include "mem_pool_test.hpp"

namespace  {
  
struct AutoReleaser {


    int release_frame_;
    void* addr_;
    bool active_;


    AutoReleaser()
        : release_frame_(0)
        , addr_(nullptr)
        , active_(false)
    {
    }

    
    void setup(int frame, void* addr) {
        release_frame_ = frame;
        addr_ = addr;
        active_ = true;
    }
    
    void update(t3::MemoryPool& pool) {
        if (active_) {
            if (release_frame_ <= 0) {
                pool.deallocate(addr_);
                addr_ = nullptr;
                active_ = false;
            } else {
                release_frame_ -= 1;
            }
        }
    }
    
    bool isActive() const {
        return active_;
    }
};


struct Mongo {
    int m1_;
    int m2_;
    char d[30];
};
  
};

constexpr int pool_size = 1024*1024*20;



class MemPoolScene::SceneContext {

public:
    SceneContext()
        : pool_(pool_size)
    {}
    
    ~SceneContext()
    {}
  
public:
    void initialize() {

/*
        int ALLOC_COUNT = 70000;
        mon1_.reserve(ALLOC_COUNT);
        mon2_.reserve(ALLOC_COUNT);
        t3::Stopwatch s1;
        s1.start();
        for (int i = 0; i < ALLOC_COUNT; ++i) {
            void* addr = std::malloc(sizeof(Mongo));
            mon1_.push_back(addr);
        }
        s1.end();

        T3_TRACE("std::malloc %f\n",s1.interval());
        t3::Stopwatch s2;
        s2.start();
        for (int i = 0; i < ALLOC_COUNT; ++i) {
            void* addr = pool_.allocate(sizeof(Mongo));
            mon2_.push_back(addr);
        }
        s2.end();
        T3_TRACE("pool        %f\n",s2.interval());
    
    
        s1.start();
        for (int i = 0; i < ALLOC_COUNT; ++i) {
            std::free(mon1_[i]);
        }
        s1.end();


        T3_TRACE("std::malloc %f\n",s1.interval());
        s2.start();
        for (int i = 0; i < ALLOC_COUNT; ++i) {
            pool_.deallocate(mon2_[i]);
        }
        s2.end();
        T3_TRACE("pool        %f\n",s2.interval());
*/
    }
    
    void terminate() {
        
    }
    
    void update(t3::tick_t delta_time) {


        size_t req = t3::Director::instance().random().getInt(100) + 4;
        int release_frame = t3::Director::instance().random().getInt(8) + 2;
        void* addr = pool_.allocate(req);
        T3_ASSERT(addr);

        AutoReleaser rel;
        rel.setup(release_frame, addr);
        for (int i = 0; i < lst_.size(); ++i) {
            if (!lst_[i].isActive()) {
                lst_[i] = rel;
                break;
            }
        }
        
        for (int i = 0; i < lst_.size(); ++i) {
            lst_[i].update(pool_);
        }

        T3_ASSERT(pool_.totalFreeSize() + pool_.totalUseSize() == pool_size);

    }


    void suspend(t3::tick_t delta_time) {

    }
    
private:
    t3::MemoryPool pool_;
    std::array<AutoReleaser, 20> lst_;
    std::vector<void*> mon1_;
    std::vector<void*> mon2_;
    
};






MemPoolScene::MemPoolScene()
    : SceneBase( "MemPool" ) {
    context_.reset(T3_NEW SceneContext());
}

MemPoolScene::~MemPoolScene() {
    
}


void MemPoolScene::initializeScene() {
    context_->initialize();
}


void MemPoolScene::terminateScene() {
    context_->terminate();
}


void MemPoolScene::updateScene(t3::tick_t delta_time) {
    context_->update(delta_time);
    
    t3::Director& gs = t3::Director::instance();
    const t3::Pad& pad = gs.input().pad();
    if (pad.isTrigger(t3::Pad::BUTTON_B)) {
        finish();
    }
}

void MemPoolScene::suspendScene(t3::tick_t delta_time) {

    context_->suspend(delta_time);
}

void MemPoolScene::debugRenderScene() {
}














