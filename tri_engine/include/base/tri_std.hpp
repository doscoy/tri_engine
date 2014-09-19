
#ifndef tri_engine_tri_std_hpp
#define tri_engine_tri_std_hpp

#include <cstddef>
#include <cstdint>
#include <string>
#include <memory>
#include <memory.h>
#include <vector>
#include <list>
#include <array>
#include <map>
#include <set>
#include <cstdio>
#include <cstdarg>
#include <fstream>
#include <functional>
#include <thread>



namespace t3 {




template <typename T>
using SharedPtr = std::shared_ptr<T>;
  
template <typename T>
using ScopedPtr = std::unique_ptr<T>;


template <typename T>
using Vector = std::vector<T>;


template <typename T>
using List = std::list<T>;

template <typename Key, typename T, typename Comp>
using Map = std::map<Key, T, Comp>;


template <typename T, size_t Size>
using Array = std::array<T, Size>;


template <typename Key>
using Set = std::set<Key>;

using String = std::string;
  
  
using Thread = std::thread;

using FileStream = std::ifstream;
  
}   // namespace t3


#endif
