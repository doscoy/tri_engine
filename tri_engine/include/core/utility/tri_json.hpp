
#ifndef tri_engine_tri_json_hpp
#define tri_engine_tri_json_hpp

#include "core/core_config.hpp"
#include "picojson.h"


TRI_CORE_NS_BEGIN



///
///	JsonObject
class JsonObject {
public:
	JsonObject(picojson::object& obj)
		: obj_(obj)
	{}
	
public:
	int integer(std::string key) {
		return static_cast<int>(obj_[key].get<double>());
	}
	
	std::string string(std::string key) {
		return obj_[key].get<std::string>();
	}

	JsonObject object(std::string key) {
		return JsonObject(obj_[key].get<picojson::object>());
	}

private:
	picojson::object& obj_;	
};

///
/// Jsonパース
class JsonParser {
public:
	Json(const char* const json) 
		: root_(nullptr)
	{
		auto log = picojson::parse(value_, json);
		if (!log.empty()) {
			std::cout << "json pars error ---" << log << std::endl;
		}
		else {
			root_ = new JsonObject(value_.get<picojson::object>());
		}
	}
	~Json() {
		delete root_;
	}
public:
	JsonObject& root() {
		return *root_;
	}
	
	JsonObject object(std::string str) {
		return root().object(str);
	}
private:
	picojson::value value_;
	JsonObject* root_;
};



TRI_CORE_NS_END


#endif
