/*
 *  uncopyable.hpp
 *  TriEngine
 *
 *  Created by 可児 哲郎 on 11/09/23.
 *  Copyright 2011  . All rights reserved.
 *
 */


#ifndef TRI_UNCOPYABLE_HPP_INCLUDED
#define TRI_UNCOPYABLE_HPP_INCLUDED

//  コピー禁止ミックスイン
class Uncopyable
{
public:
    Uncopyable() = default;
    ~Uncopyable() = default;
    Uncopyable( const Uncopyable& ) = delete;
    Uncopyable& operator= ( const Uncopyable& ) = delete;
};

#endif // TRI_UNCOPYABLE_HPP_INCLUDED