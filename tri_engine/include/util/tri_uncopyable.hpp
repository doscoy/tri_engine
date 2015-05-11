/**
    @file tri_uncopyable.hpp
    コピー禁止ミックスインクラス.
*/
#ifndef TRI_UNCOPYABLE_HPP_INCLUDED
#define TRI_UNCOPYABLE_HPP_INCLUDED

namespace t3 {

///
///  コピー禁止ミックスイン
class Uncopyable {
protected:
    Uncopyable() = default;
    ~Uncopyable() = default;
    Uncopyable( const Uncopyable& ) = delete;
    Uncopyable& operator= ( const Uncopyable& ) = delete;
};


}   // namespace t3


#endif // TRI_UNCOPYABLE_HPP_INCLUDED
