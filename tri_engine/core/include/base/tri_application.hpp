/**
    @file tri_application.hpp
    アプリケーション基底クラス.
    全てのアプリケーションはこのクラスを継承して作成する
*/

#ifndef TRI_APPLICATION_HPP_INCLUDED
#define TRI_APPLICATION_HPP_INCLUDED

//  インクルード
#include "core_config.hpp"
#include "utility/tri_uncopyable.hpp"
#include "base/tri_std.hpp"
#include "tri_types.hpp"
#include "utility/tri_stopwatch.hpp"



TRI_CORE_NS_BEGIN

//  前方宣言
class ApplicationDebugMenu;






//  前方宣言
class SceneGenerator;

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
    void updateApplication();

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

    ///
    /// アプリケーションのルートシーンを設定
    void rootScene(
        SceneGenerator* root    ///< root
    ) {
        root_scene_generator_ = root;
    }
    
private:
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
public:
    ///
    /// ルートシーンへ遷移
    void gotoRootScene();
    
    
private:
#if DEBUG
    ScopedPtr<ApplicationDebugMenu> system_menu_;
#endif
    SceneGenerator* root_scene_generator_;  ///< ルートシーンのジェネレータ
    uint32_t last_scene_change_frame_;  ///< 最後にシーンチェンジしたフレーム
    uint32_t memory_leak_check_filter_; ///< メモリリークチェックフィルタ
    Stopwatch fps_timer_;   ///< fps計測用タイマー
    Array<float, 260> fps_stack_;   ///< fps保存用コンテナ
    float fps_; ///< fps
};




///
/// エンジンの初期化
bool initializeTriEngine(
    const int width,        ///< スクリーン幅
    const int height,       ///< スクリーン高さ
    const char* const title ///< 任意の文字列
);


///
/// エンジンの後片付け
void terminateTriEngine();


///
/// 起動するアプリを設定.
void setApplication(
    Application& app    ///< アプリケーション
);


///
/// 初期化.
void initializeApplication();


///
/// 後片付け.
void terminateApplication();

///
/// 更新.
void updateApplication();

///
/// 描画.
void renderApplication();

///
/// アプリ有効判定
bool isActiveApplication();

TRI_CORE_NS_END

#endif // TRI_APPLICATION_HPP_INCLUDED
