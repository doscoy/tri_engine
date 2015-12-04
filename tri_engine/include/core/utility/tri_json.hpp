////////////////////////////////////////////////////////////////////////
//  Tri ENGINE
//    copyright 2012... Tri ENGINE project team.
//
//  Website: http://tri-engine.aquariuscode.com/
//  License: https://github.com/doscoy/tri_engine/wiki/License
////////////////////////////////////////////////////////////////////////
/**
    @file tri_json.hpp
    JSON形式のファイルのパース.
*/


#ifndef tri_engine_tri_json_hpp
#define tri_engine_tri_json_hpp

#include "core/core_config.hpp"
#include "picojson.h"


TRI_CORE_NS_BEGIN



///
///	JsonObject.
/// パーサとして外部ライブラリ picojsonを使用
class JsonObject {
public:
    ///
    /// コンストラクタ
	JsonObject(picojson::object& obj)
		: obj_(obj)
	{}
	
public:
    ///
    /// キーを指定して数値を取得
	int integer(std::string key) {
		return static_cast<int>(obj_[key].get<double>());
	}
	
    ///
    /// キーを指定して文字列を取得
	std::string string(std::string key) {
		return obj_[key].get<std::string>();
	}

    ///
    /// キーを指定して子オブジェクトを取得
	JsonObject object(std::string key) {
		return JsonObject(obj_[key].get<picojson::object>());
	}

private:
	picojson::object& obj_;	
};

///
/// Jsonパーサ
class JsonParser {
public:
    ///
    /// コンストラクタ
	Json(
        const char* const json  ///< jsonデータ
    )   : root_(nullptr)
	{
		auto log = picojson::parse(value_, json);
		if (!log.empty()) {
            //  パースに失敗
            //  エラー出力
			std::cout << "json pars error ---" << log << std::endl;
		}
		else {
            //  パースに成功
			root_ = new JsonObject(value_.get<picojson::object>());
		}
	}
    
    ///
    /// デストラクタ
	~Json() {
		delete root_;
	}
    
public:
    ///
    /// ルートオブジェクト取得
	JsonObject& root() {
		return *root_;
	}
	
    ///
    /// キーを指定してオブジェクト取得
	JsonObject object(std::string str) {
		return root().object(str);
	}


private:
	picojson::value value_;
	JsonObject* root_;
};



TRI_CORE_NS_END


#endif
