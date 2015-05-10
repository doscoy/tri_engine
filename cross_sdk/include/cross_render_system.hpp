
#ifndef CROSS_RENDER_SYSTEM_HPP_INCLUDED
#define CROSS_RENDER_SYSTEM_HPP_INCLUDED


//  include
#include <cstdint>
#include <cstdlib>

///
/// ソースファイルに直接書かれたシェーダコードを文字列化
#define TRI_INSTANT_SHADER(A)  #A



namespace cross {

//  前方参照
class Texture;

///
/// レンダリングシステム
class RenderSystem {
public:
    ///
    /// 型の数値
    enum {
        BYTE  = 0x1401,
        INT   = 0x1404,
        FLOAT = 0x1406,
    };
    
    
    ///
    /// フレーブバッファID
    using FrameBufferID = unsigned int;

    ///
    /// フレームバッファを作成
    static void createFrameBuffer(FrameBufferID* id);
    
    ///
    /// フレームバッファを削除
    static void deleteFrameBuffer(FrameBufferID* id);
    
    ///
    /// フレームバッファをバインド
    static void bindFrameBuffer(FrameBufferID id);
    
    ///
    /// カレントのフレームバッファIDを取得
    static FrameBufferID getCurrentFrameBufferID();
    
    
    ///
    /// レンダーバッファID
    using RenderBufferID = unsigned int;
    
    ///
    /// レンダーバッファを作成
    static void createRenderBuffer(RenderBufferID* id);
    
    ///
    ///レンダーバッファを削除
    static void deleteRenderBuffer(RenderBufferID* id);
    
    ///
    /// レンダーバッファをバインド
    static void bindRenderBuffer(RenderBufferID id);
    
    ///
    /// カレントのれんだーバッファを取得
    static RenderBufferID getCurrentRenderBufferID();


    ///
    /// ドローコール数を取得
    static int getDrawCallCount();
    
    ///
    /// ドローコール数をリセット
    static void resetDrawCallCount();

    ///
    /// バッファID
    using BufferID = unsigned int;
    
    ///
    /// シェーダプログラムID
    using ShaderProgramID = unsigned int;
    
    ///
    /// シェーダ変数の場所
    using ShaderVariableLocation = unsigned int;
    
    ///
    /// テクスチャID
    using TextureID = unsigned int;

    ///
    /// ブレンドモード
    enum class BlendMode
        : uint8_t {
        NONE,       ///< ブレンド無し
        NORMAL,     ///< 通常ブレンド
        ADD         ///< 加算半透明
    };

    ///
    /// ブレンドモード設定
    static void setBlendMode(
        BlendMode mode
    );


    ///
    /// テクスチャユニット定義
    enum TextureUnit {
        UNIT0 = 0,
        UNIT1 = 1,
        UNIT2 = 2,
        UNIT3 = 3,
        UNIT4 = 4
    };
    
    ///
    /// テクスチャユニットを有効化
    static void setActiveTextureUnit(
        int unit
    );


    ///
    /// テクスチャをバインド
    static void bindTexture(
        TextureID texture
    );

    ///
    /// シェーダの種類
    enum class ShaderType {
        VERTEX_SHADER,      ///< 頂点シェーダ
        FRAGMENT_SHADER,    ///< フラグメントシェーダ
        GEOMETRY_SHADER     ///< ジオメトリシェーダ
    };

    ///
    /// シェーダをビルド
    static int buildShader(
        const char* const source,
        ShaderType shader_type
    );
    
    ///
    /// シェーダをアタッチ
    static void attachShader(
        ShaderProgramID program_handle,
        int shader_handle
    );

    ///
    /// シェーダプログラムをリンクする
    static void linkShader(
        ShaderProgramID
    );
    
    ///
    /// ユニフォーム変数の場所を取得
    static ShaderVariableLocation getUniformLocation(
        ShaderProgramID program,
        const char* const name
    );

    ///
    /// アトリビュート変数の場所を取得
    static ShaderVariableLocation getAttributeLocation(
        ShaderProgramID program,
        const char* const name
    );

    ///
    /// アトリビュート変数の場所をバインド
    static void bindAttributeLocation(
        ShaderProgramID handle,
        ShaderVariableLocation location,
        const char* const name
    );

    ///
    /// フラグメント変数をバインド
    static void bindFragmentDataLocation(
        ShaderProgramID handle,
        ShaderVariableLocation location,
        const char* const name
    );

    ///
    ///
    static void setUniformValue(
        ShaderVariableLocation location,
        float val
    );
    
    ///
    /// ユニフォーム変数に値をセット
    static void setUniformValue(
        ShaderVariableLocation location,
        size_t size,
        float* val
    );
    
    ///
    /// ユニフォーム変数に値をセット
    static void setUniformValue(
        ShaderVariableLocation location,
        int val
    );


    ///
    /// シェーダをセット
    static void setShader(
        ShaderProgramID shader
    );

    ///
    /// ユニフォーム変数に値をセット
    static void setUniformValue(
        ShaderVariableLocation,
        float x,
        float y,
        float z
    );
    
    ///
    /// ユニフォーム変数に値をセット
    static void setUniformValue(
        ShaderVariableLocation location,
        float x,
        float y,
        float z,
        float w
    );

    ///
    /// ユニフォーム変数に値をセット
    static void setUniformMatrix(
        ShaderVariableLocation location,
        const float* mtx
    );

    ///
    /// レンダリングシステムの初期化
    static void initializeRenderSystem();

    ///
    /// カラーフォーマット定義
    enum class ColorFormat {
        RGB,    ///< RGB
        RGBA,   ///< RGBA
        GRAY,   ///< グレースケール
        GRAYA   ///< アルファ付きグレースケール
    };
    
    ///
    /// テクスチャのセットアップ
    static void setupTextureData(
        int width,
        int height,
        RenderSystem::ColorFormat color_format,
        const void* data
    );

    ///
    /// カリングモード
    enum class CullingMode {
        MODE_FRONT,     ///< 前面カリング
        MODE_BACK,      ///< 背面カリング
    };
    
    ///
    /// カリングモードの設定.
    /// 隠面除去の設定を行います
    static void setCullingMode(
        CullingMode mode        ///< モード
    );
    
    
    ///
    /// ダブルバッファリング時のフレームバッファ切り替え
    static void swapBuffers();
    
    ///
    /// バッファのクリア
    static void clearBuffer(
        bool color_clear,
        bool depth_clear,
        bool stencil_clear
    );
    
    
    ///
    /// デプスバッファへの書き込みを設定
    static void setDepthWrite(
        bool enable     ///< true = 書き込み有効
    );
    
    ///
    /// デプスバッファをクリアする値を設定
    static void setClearDepthValue(
        const float value
    );
    
    
    ///
    /// フレームバッファをクリアする色
    static void clearColor(
        float r,
        float g,
        float b,
        float a
    );
    
    
    ///
    /// デプステストのモード
    enum class DepthTestMode {
        MODE_NEVER,     ///< 常に弾く
        MODE_LESS,      ///< 通常
        MODE_ALWAYS     ///< 常に通す
    };
    
    ///
    /// デプステストのモード設定
    static void setDepthTestMode(
        DepthTestMode mode
    );
    
    ///
    /// ブレンド関数の種類
    enum class BlendFunctionType {
        TYPE_ZERO,
        TYPE_ONE,
        TYPE_SRC_COLOR,
        TYPE_ONE_MINUS_SRC_COLOR,
        TYPE_DST_COLOR,
        TYPE_ONE_MINUS_DST_COLOR,
        TYPE_SRC_ALPHA,
        TYPE_ONE_MINUS_SRC_ALPHA,
        TYPE_DST_ALPHA,
        TYPE_ONE_MINUS_DST_ALPHA,
        TYPE_CONSTANT_COLOR,
        TYPE_ONE_MINUS_CONSTANT_COLOR,
        TYPE_CONSTANT_ALPHA,
        TYPE_ONE_MINUS_CONSTANT_ALPHA,
    };
    
    ///
    /// ブレンド関数を設定
    static void setBlendFunctionType(
        BlendFunctionType sfactor,
        BlendFunctionType dfactor
    );
    
    
    ///
    /// ビューポート設定
    static void setViewport(
        const int x,
        const int y,
        const int w,
        const int h
    );
    
    ///
    /// ビューポート設定
    static void setViewportC(
        const int x,
        const int y,
        const int w,
        const int h
    );
    
    ///
    /// ビューポート値を取得
    static void getViewport(
        int* x,
        int* y,
        int* w,
        int* h
    );


    ///
    /// デプステストを設定
    static void setDepthTest(
        bool enable
    );
    
    ///
    /// ブレンドを行うか設定
    static void setBlend(
        bool enable
    );
    
    ///
    /// カリングを行うか設定
    static void setCulling(
        bool enable
    );
    

    ///
    /// テクスチャフィルタの種類
    enum class TextureFilterType {
        TYPE_NEAREST,   ///< 最近値
        TYPE_LINEAR     ///< 線形補間
    };
    
    ///
    /// テクスチャフィルタ設定
    static void setTextureMagFilter(
        TextureFilterType type
    );
    
    ///
    /// テクスチャフィルタ設定
    static void setTextureMinFilter(
        TextureFilterType type
    );
    
    ///
    /// テクスチャラップモード定義
    enum class TextureWrapType {
        CLAMP_TO_EDGE,  ///< エッジでクランプ
        REPEAT          ///< リピート
    };
    
    ///
    /// テクスチャラップモードを設定
    static void setTextureWrap(
        TextureWrapType type
    );
    
    ///
    /// 横方向のテクスチャラップモード
    static void setTextureWrapS(
        TextureWrapType s
    );
    
    ///
    /// 縦方向のテクスチャラップモード
    static void setTextureWrapT(
        TextureWrapType t
    );

    ///
    /// 描画モード
    enum class DrawMode{
        MODE_TRIANGLES,     ///< トライアングル
        MODE_TRIANGLE_STRIP ///< トライアングルストリップ
    };
    
    ///
    /// 描画
    static void drawElements(
        DrawMode mode,
        int count,
        size_t indices_type_size
    );
    
    ///
    /// 描画
    static void drawElementsC(
        DrawMode mode,
        int count,
        size_t indices_type_size
    );
    
    ///
    /// 描画
    static void drawArray(
        DrawMode mode,
        int first,
        int count
    );
    
    ///
    /// 描画
    static void drawArrayC(
        DrawMode mode,
        int first,
        int count
    );

    ///
    /// バッファタイプ
    enum class BufferType {
        TYPE_VERTEX,    ///< 頂点バッファとして使用
        TYPE_INDEX,     ///< インデックスバッファとして使用
    };
    
    ///
    /// バッファの使い方
    enum class BufferUsage {
        STATIC_DRAW,    ///< 静的描画モード
        DYNAMIC_DRAW    ///< 動的描画モード
    };
    
    ///
    /// バインド
    static void bindBuffer(
        BufferType target_type,
        int buffer_id
    );
    
    ///
    /// バインドされているバッファをリセット
    static void resetBufferBind() {
        bindBuffer(BufferType::TYPE_VERTEX, 0);
        bindBuffer(BufferType::TYPE_INDEX, 0);
        bindVertexArrayBuffer(0);
    }
    
    ///
    /// バッファを作成
    static void createBuffer(uint32_t* buffer);
    
    ///
    /// バッファを削除
    static void deleteBuffer(uint32_t* buffer);
    
    ///
    /// バッファを削除
    static void deleteBufferC(uint32_t* buffer);
    
    
    ///
    /// バッファデータのセットアップ
    static void setupBufferData(
        BufferType type,
        int size,
        const void* data,
        BufferUsage usage
    );

    ///
    /// バッファサブデータをセットアップ
    static void setupBufferSubData(
        BufferType type,
        int offset,
        int size,
        const void* data
    );
  
    
    ///
    /// 頂点シェーダのアトリビュートを有効化
    static void setEnableVertexAttribute(
        int slot
    );
    
    ///
    /// 頂点シェーダのアトリビュートを無効化
    static void setDisableVertexAttribute(
        int slot
    );
    
    ///
    /// 頂点バッファポインタを設定
    static void setVertexAttributePointer(
        int slot,
        int element_num,
        int type,
        bool normalized,
        int stride,
        void* ptr
    );
    
    ///
    /// シェーダアトリビュートに値を設定
    static void setAttributeValue(
        int slot,   ///< スロット
        float a,    ///< 値1
        float b,    ///< 値２
        float c,    ///< 値3
        float d     ///< 値4
    );
    
    
    ///
    /// 描画バッファのアタッチタイプ
    enum class RenderBufferAttachType {
        DEPTH,      ///< デプスバッファ
        COLOR0,     ///< カラーバッファ
    };
    
    ///
    /// レンダーバッファをアタッチ
    static void attachRenderBuffer(
        RenderBufferAttachType type,
        RenderBufferID id
    );
    
    ///
    /// フレームバッファをテクスチャにアタッチ
    static void attachFrameBufferTexture(
        RenderBufferAttachType type,
        TextureID id
    );
    
    ///
    /// 描画バッファの使い方定義
    enum class RenderBufferUsage {
        DEPTH,  ///< デプスバッファ
        COLOR,  ///< カラーバッファ
    };
    
    ///
    /// 描画バッファのセットアップ
    static void setupRenderBufferStorage(
        RenderBufferUsage usage,
        int width,
        int height
    );
    
    
    ///
    /// VAOを作成
    static BufferID createVertexArrayBuffer();
    
    ///
    /// VAOをバインド
    static void bindVertexArrayBuffer(BufferID id);
    
    ///
    /// VAOを削除
    static void deleteVertexArrayBuffer(BufferID id);
    
    
    
    ///
    /// 描画フェンス
    static void fenceDraw();
    
    ///
    /// 描画フェンス待ち
    static void fenceDrawWaiting();
    
    ///
    /// バッファをマッピング
    static void mapBuffer(
        RenderSystem::BufferType type,
        intptr_t offset,
        size_t size,
        void* data
    );
    
    ///
    /// バッファのマッピングを解除
    static void unmapBuffer(RenderSystem::BufferType type);
    
    ///
    /// シェーダプログラム生成
    static int createProgram();
    
    ///
    /// テクスチャ生成
    static TextureID createTexture();

    ///
    /// テクスチャの削除
    static void deleteTexture(TextureID* id);
    
    ///
    /// レンダリングシステムエラー判定
    static bool isError();
};


}   // namespace cross

#endif // TRI_RENDER_SYSTEM_HPP
