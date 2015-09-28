////////////////////////////////////////////////////////////////////////
//  Tri ENGINE
//    copyright 2012... Tri ENGINE project team.
//
//  Website: http://tri-engine.aquariuscode.com/
//  License: https://github.com/doscoy/tri_engine/wiki/License
////////////////////////////////////////////////////////////////////////
/**
    @file tri_bit.hpp
    あらゆる型を受け取る型. boots:anyの移植
    RTTI（実行時型情報）が有効になっている必要があります。
*/


#ifndef TRI_ANY_HPP_INCLUDED
#define TRI_ANY_HPP_INCLUDED


//  include
#include "core/core_config.hpp"
#include <typeinfo>
#include "core/kernel/memory/tri_new.hpp"

TRI_CORE_NS_BEGIN


///
/// あらゆる型を格納できる型
class Any {

private:
    ///
    /// ホルダーベース
    struct HolderBase{
        virtual ~HolderBase() {}
        virtual HolderBase* clone() const = 0;
        virtual const std::type_info& type() const = 0;
    };
	
    ///
    ///	ホルダー
    template <class T>
    struct holder
        : public HolderBase{
        ///
        ///	値保持
        T value_;
		
        ///
        ///	コンストラクタ
        holder( const T& value )
            :value_(value)
        {}
		
        ///
        ///	コピー処理
        virtual HolderBase* clone() const {
            return ( T3_SYS_NEW holder( value_ ) );
        }
		
        ///
        ///	型情報取得
        virtual const std::type_info& type() const{
            return (typeid( T ));
        }
    };
	


    //	Anyの実装は以下
public:

    ///
    ///	コンストラクタ
    template <class T>
    Any(const T& value)
        : content_(T3_SYS_NEW holder<T>(value))
    {}

    ///
    ///	コンストラクタ
    Any(const Any& other)
        : content_(other.content_ ? other.content_->clone() : nullptr)
    {}
		
    ///
    ///	デストラクタ
    ~Any(){
        if (content_) {
            T3_DELETE content_;
            content_ = nullptr;
        }
    }



//	オペレータ
public:
    ///
    /// 何か、別の型をAnyに代入
    template <class T>
    Any& operator =(const T& value) {
        if (content_) {
            T3_DELETE content_;
            content_ = NULL;
        }
        content_ = T3_SYS_NEW holder<T>(value);
        return ( *this );
    }
	
    ///
    ///	Any同士の代入
    Any& operator =(const Any& other) {
		if (content_) {
            T3_DELETE content_;
            content_ = NULL;
        }
        content_ = other.content_ ? other.content_->clone() : NULL;
        return ( *this );
    }



//	公開メソッド
public:
    ///
    ///	値を取り出す
    template <class T>
    const T& cast() const {
        return ( dynamic_cast< holder<T>& >(*content_).value_ );
    }

    ///
    ///	型情報取得
    const std::type_info& type() const {
        return content_ ? content_->type() : typeid( void );
    }



//	メンバ変数
private:
    ///
    /// 型ホルダ
    HolderBase* content_;

};



TRI_CORE_NS_END



///
/// サービス関数 Any_cast用意
template < class To >
inline To any_cast(
    t3::Any& from	///< 変換前
){
    return from.cast<To>();
}


#endif // TRI_ANY_HPP_INCLUDED


