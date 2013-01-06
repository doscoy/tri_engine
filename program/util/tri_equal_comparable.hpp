

#ifndef TRI_EQUAL_COMPARABLE_HPP_INCLUDED
#define TRI_EQUAL_COMPARABLE_HPP_INCLUDED

namespace t3 {


// 比較演算子ミックスイン
template <class T>
class EqalComparable {
    
	friend bool operator != (
		const T& lhs,
		const T& rhs
		){
		return !lhs.operator==(rhs);	
	}
};


} // namespace t3

#endif // TRI_EQUAL_COMPARABLE_HPP_INCLUDED
