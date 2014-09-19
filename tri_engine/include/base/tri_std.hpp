
#ifndef tri_engine_tri_std_hpp
#define tri_engine_tri_std_hpp

#include <cstddef>
#include <cstdint>
#include <string>
#include <memory.h>
#include <vector>
#include <list>
#include <array>
#include <map>


namespace t3 {




template <typename T>
using SharedPtr = std::shared_ptr<T>;
  


template <typename T>
using Vector = std::vector<T>;


template <typename Key, typename T, typename Comp>
using Map = std::map<Key, T, Comp>;


  
}   // namespace t3


#endif
