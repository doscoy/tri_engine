////////////////////////////////////////////////////////////////////////
//  Tri ENGINE
//    copyright 2012... Tri ENGINE project team.
//
//  Website: http://tri-engine.aquariuscode.com/
//  License: https://github.com/doscoy/tri_engine/wiki/License
////////////////////////////////////////////////////////////////////////
/**
    @file tri_framework.hpp
    システムの基盤となるフレームワーククラス.
*/

#ifndef TRI_FRAMEWORK_HPP_INCLUDED
#define TRI_FRAMEWORK_HPP_INCLUDED

//  インクルード
#include "core/core_config.hpp"
#include "core/utility/tri_uncopyable.hpp"
#include "tri_types.hpp"
#include "core/utility/tri_stopwatch.hpp"
#include "core/utility/tri_singleton.hpp"
#include "cross/cross_std.hpp"
#include "core/base/tri_application.hpp"



TRI_CORE_NS_BEGIN

class FrameworkDebugMenu;

///
/// フレームワーククラス.
class Framework
    : public Singleton<Framework>
{
    //  friend
    friend class Singleton<Framework>;

private:
    ///
    /// コンストラクタ
    Framework();

    ///
    /// デストラクタ
    ~Framework();


public:
    ///
    /// 初期化
    bool initializeFramework(int width, int height, const char* const title);

    ///
    /// 更新
    void updateFramework();

    ///
    /// 描画
    void renderFramework();

    ///
    /// 後片付け
    void terminateFramework();


    ///
    /// アプリケーションが実行中か判定
    /// @retval true 実行中
    bool isActive() const;

    ///
    /// フレームワーク上で動かすアプリを設定
    void setApplication(
        const ApplicationGenerator* gen
    ) {
        next_app_generator_ = gen;
    }
    
private:
    ///
    /// アプリケーションの更新を呼ぶ
    void doUpdateApplication(const DeltaTime dt);
    
    ///
    /// アプリケーションの描画を呼ぶ
    void doRenderApplication();


    ///
    /// 描画前処理
    void beginRender();

    ///
    /// 描画後処理
    void endRender();


    ///
    /// デバッグメニューのオープンリクエストが発生しているか判定
    /// @retval true リクエストが発生した
    bool isDebugMenuOpenRequest();

    ///
    /// サスペンド中か判定
    /// @retval true サスペンド中
    bool isSuspend() const;

    ///
    /// ワークバーの初期化
    void initializeWorkBar();

    ///
    /// デバッグ用描画
    void debugPrinting();
    
private:

    ApplicationPtr app_;
    const ApplicationGenerator* next_app_generator_;

#ifdef TRI_DEBUG
    UniquePtr<FrameworkDebugMenu> system_menu_;
#endif
    Stopwatch fps_timer_;   ///< fps計測用タイマー
    Array<float, 260> fps_stack_;   ///< fps保存用コンテナ
    float fps_; ///< fps
};





TRI_CORE_NS_END

#endif // TRI_APPLICATION_HPP_INCLUDED
