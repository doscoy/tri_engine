////////////////////////////////////////////////////////////////////////
//  Tri ENGINE
//    copyright 2012... Tri ENGINE project team.
//
//  Website: http://tri-engine.aquariuscode.com/
//  License: https://github.com/doscoy/tri_engine/wiki/License
////////////////////////////////////////////////////////////////////////
/**
    @file tri_application.hpp
    アプリケーション基底クラス.
    全てのアプリケーションはこのクラスを継承して作成する
*/

#ifndef TRI_APPLICATION_HPP_INCLUDED
#define TRI_APPLICATION_HPP_INCLUDED

//  インクルード
#include "core/core_config.hpp"
#include "core/utility/tri_uncopyable.hpp"
#include "tri_types.hpp"
#include "core/utility/tri_stopwatch.hpp"
#include "cross/cross_std.hpp"
#include "core/kernel/memory/tri_new.hpp"

TRI_CORE_NS_BEGIN


///
/// アプリケーションジェネレータ
class Application;
using ApplicationPtr = SharedPtr<Application>;
class ApplicationGenerator {
public:
    virtual ApplicationPtr create() const = 0;
};

template <class T>
class TypedApplicationGenerator
    : public ApplicationGenerator {
public:
    ApplicationPtr create() const override {
        ApplicationPtr app(T3_SYS_NEW T);
        return app;
    }
};



//  前方宣言
class TaskGeneratorBase;

///
/// アプリケーションクラス.
class Application 
    : Uncopyable 
{
public:
    ///
    /// コンストラクタ
    Application();

    ///
    /// デストラクタ
    virtual ~Application();


private:
    ///
    /// ゲーム側の初期化
    virtual void initializeGame() = 0;

    ///
    /// ゲーム側の後片付け
    virtual void terminateGame() = 0;

public:
    ///
    /// 初期化
    void initializeApplication();

    ///
    /// 更新
    void updateApplication(const DeltaTime dt);

    ///
    /// 描画
    void renderApplication();

    ///
    /// 後片付け
    void terminateApplication();


    ///
    /// アプリケーションが実行中か判定
    /// @retval true 実行中
    bool isActive() const;


    bool isReady() const {
        return  initialized_;
    }

    ///
    /// アプリケーションのルートシーンを設定
    void rootScene(
        TaskGeneratorBase* root    ///< root
    ) {
        root_scene_generator_ = root;
    }
    
    
    ///
    /// アプリケーションのジェネレータ取得
    template <class T>
    static const ApplicationGenerator* getGenerator() {
        static TypedApplicationGenerator<T> generator;
        return &generator;
    }
    
    
public:
    ///
    /// ルートシーンへ遷移
    void gotoRootScene();
    
    
private:
    TaskGeneratorBase* root_scene_generator_;  ///< ルートシーンのジェネレータ
    uint32_t last_scene_change_frame_;  ///< 最後にシーンチェンジしたフレーム
    uint32_t memory_leak_check_filter_; ///< メモリリークチェックフィルタ
    bool initialized_;
};



TRI_CORE_NS_END

#endif // TRI_APPLICATION_HPP_INCLUDED
