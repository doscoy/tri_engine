////////////////////////////////////////////////////////////////////////
//  Tri ENGINE
//    copyright 2012... Tri ENGINE project team.
//
//  Website: http://tri-engine.aquariuscode.com/
//  License: https://github.com/doscoy/tri_engine/wiki/License
////////////////////////////////////////////////////////////////////////

/**
    @file core_config.hpp
    CoreENGINEで使う設定.
*/

#ifndef CORE_CONFIG_HPP_INCLUDED
#define CORE_CONFIG_HPP_INCLUDED

///
/// TriENGINEのコアモジュールで使用するネームスペース定義マクロ
/// t3 { core {
#define TRI_CORE_NS_BEGIN   namespace t3 { inline namespace core {
#define TRI_CORE_NS_END     }}


///
/// TriENGINEのイベントグループをまとめるネームスペース
#define TRI_EVENT_NS_BEGIN  namespace event {
#define TRI_EVENT_NS_END    }


#endif // CORE_CONFIG_HPP_INCLUDED

