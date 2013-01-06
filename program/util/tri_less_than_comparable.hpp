/* -------------------------------------------------------------------------------
	NdFramework
	< > <= >= î‰ärâ¬î\ÉIÉuÉWÉFÉNÉg

                            Copyright (C)2009-2010 Nd CUBE  All rights reserved.
---------------------------------------------------------------------------------*/

#ifndef TRI_LESS_THAN_COMPARABLE_HPP_INCLUDED
#define TRI_LESS_THAN_COMPARABLE_HPP_INCLUDED

namespace t3 {

//  比較演算子mix-in
template <class T>
class LessThanComparable{


	// > 
	friend bool operator >( 
		const T& lhs,
		const T& rhs
		){
		return ( rhs.operator<( lhs ) );	
	}

	//	<=
	friend bool operator <=(
		const T& lhs,
		const T& rhs
		){
		return ( !rhs.operator<(lhs) );	
	}
	
	//	>=
	friend bool operator <=(
		const T& lhs,
		const T& rhs
		){
		return ( !lhs.operator<(rhs) );	
	}
	
};
} // namespace t3

#endif // TRI_LESS_THAN_COMPARABLE_HPP_INCLUDED
