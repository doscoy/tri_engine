#ifndef TRI_OPTIONAL_HPP_INCLUDED
#define TRI_OPTIONAL_HPP_INCLUDED


#include "../dbg/tri_assert.hpp"

namespace t3 {


template <class T>
class optional
{

public:
	optional() 
		: valid_( false )
    {
		// none
	}

	optional( const T& t )
		: content_( t )
		, valid_( true )
    {
		// none
	}

	optional( const optional& other )
		: valid_( false )
    {
		if ( other.isValid() ){
			content_ = other.content_;
			valid_ = true;
		}
	}
	
	~optional()
	{
		// none
	}


public:
/* Tを返すパターン
	const T& operator =(const T& t ) {

		content_ = t;
		valid_ = true;

		return content_;
	}

	const T& operator =( const optional& rhs ) {
		
		if ( this != &rhs ){
			if ( rhs.isValid() ){
				content_ = rhs.content_;
				valid_ = true;
			}
			else {
				valid_ = false;
			}
		}
		return content_;
	}
*/

	const optional& operator =(const T& t ) {
		content_ = t;
		valid_ = true;

		return *this;
	}

	const optional& operator =( const optional& rhs ) {
		if ( this != &rhs ){
			if ( rhs.valid_ ){
				content_ = rhs.content_;
				valid_ = true;
			}
			else {
				valid_ = false;
			}
		}
		return *this;
	}




    optional operator -() {
        T3_ASSERT_MSG( valid_, "It's no initialized value." );
        return optional( -content_ );
    }

    optional operator +() {
        T3_ASSERT_MSG( valid_, "It's no initialized value." );
        return *this;
    }
    
    T operator +( const T& rhs ) const {
        T3_ASSERT_MSG( valid_, "It's no initialized value." );
		return content_ + rhs;
    }
    
    T operator +( const optional& rhs ) const {
        T3_ASSERT_MSG( rhs.valid_, "It's no initialized value." );
        T3_ASSERT_MSG( valid_, "It's no initialized value." );
		return content_ + rhs.content_;
    }
    
    T operator -( const T& rhs ) const {
        T3_ASSERT_MSG( valid_, "It's no initialized value." );
		return content_ - rhs;
    }
    
    T operator -( const optional& rhs ) const {
        T3_ASSERT_MSG( rhs.valid_, "It's no initialized value." );
        T3_ASSERT_MSG( valid_, "It's no initialized value." );
		return content_ - rhs.content_;
    }
    
    T operator *( const T& rhs ) const {
        T3_ASSERT_MSG( valid_, "It's no initialized value." );
		return content_ * rhs;
    }
    
    T operator *( const optional& rhs ) const {
        T3_ASSERT_MSG( rhs.valid_, "It's no initialized value." );
        T3_ASSERT_MSG( valid_, "It's no initialized value." );
		return content_ * rhs.content_;
    }
    
    T operator /( const T& rhs ) const {
        T3_ASSERT_MSG( valid_, "It's no initialized value." );
		return content_ / rhs;
    }
    
    T operator /( const optional& rhs ) const {
        T3_ASSERT_MSG( rhs.valid_, "It's no initialized value." );
        T3_ASSERT_MSG( valid_, "It's no initialized value." );
		return content_ / rhs.content_;
    }
    
    
    
/*
	optional& operator ++() {
		T3_ASSERT_MSG( valid_, "It's no initialized value." );
		++content_;
		return ( *this );
	}

	optional& operator ++(int) {
		T3_ASSERT_MSG( valid_, "It's no initialized value." );
		content_++;
		return ( *this );
	}
*/
    T operator ++() {
		T3_ASSERT_MSG( valid_, "It's no initialized value." );
		return ( ++content_ );
	}

	T operator ++(int) {
		T3_ASSERT_MSG( valid_, "It's no initialized value." );
		return ( content_++ );
	}

	T operator --() {
		T3_ASSERT_MSG( valid_, "It's no initialized value." );
		return ( --content_ );
	}

	T operator --(int) {
		T3_ASSERT_MSG( valid_, "It's no initialized value." );
		return ( content_-- );
	}

	const optional& operator +=(const optional& rhs){
		T3_ASSERT_MSG( valid_, "It's no initialized value." );
		content_ += rhs.content_;

		return ( *this );
	}

	const optional& operator +=(const T& rhs){
		T3_ASSERT_MSG( valid_, "It's no initialized value." );
		content_ += rhs;

		return ( *this );
	}
	
	const optional& operator -=(const optional& rhs){
		T3_ASSERT_MSG( valid_, "It's no initialized value." );
		content_ -= rhs.content_;

		return ( *this );
	}

	
	const optional& operator -=(const T& rhs){
		T3_ASSERT_MSG( valid_, "It's no initialized value." );
		content_ -= rhs;

		return ( *this );
	}

	const optional& operator *=(const optional& rhs){
		T3_ASSERT_MSG( valid_, "It's no initialized value." );
		content_ *= rhs.content_;

		return ( *this );
	}

	const optional& operator *=(const T& rhs){
		T3_ASSERT_MSG( valid_, "It's no initialized value." );
		content_ *= rhs;

		return ( *this );
	}

	const optional& operator /=(const optional& rhs){
		T3_ASSERT_MSG( valid_, "It's no initialized value." );
		content_ /= *rhs.getContent();

		return ( *this );
	}

	const optional& operator /=(const T& rhs){
		T3_ASSERT_MSG( valid_, "It's no initialized value." );
		content_ /= rhs;

		return ( *this );
	}
	
	const optional& operator %=(const optional& rhs){
		T3_ASSERT_MSG( valid_, "It's no initialized value." );
		content_ %= rhs.content_;

		return ( *this );
	}

	const optional& operator %=(const T& rhs){
		T3_ASSERT_MSG( valid_, "It's no initialized value." );
		content_ %= rhs;

		return ( *this );
	}

    const optional* operator &() const{
    	T3_ASSERT_MSG( valid_, "It's no initialized value." );
        return this;
    }
    

    optional* operator &() {
    	T3_ASSERT_MSG( valid_, "It's no initialized value." );
        return this;
    }

	const T& operator *() const {
		T3_ASSERT_MSG( valid_, "It's no initialized value." );
		return ( content_ );
	}
	
	T& operator *() {
		T3_ASSERT_MSG( valid_, "It's no initialized value." );
		return ( content_ );
	}
	
	const T* const operator ->() const {
		T3_ASSERT_MSG( valid_, "It's no initialized value." );
		return ( &content_ );
	}
	
	T* const operator ->() {
		T3_ASSERT_MSG( valid_, "It's no initialized value." );
		return ( &content_ );
	}
	
	operator T(){
		T3_ASSERT_MSG( valid_, "It's no initialized value." );
		return ( content_ );
	}


    bool operator == ( const optional& other ) const {
		T3_ASSERT_MSG( valid_, "It's no initialized value." );
		if ( other.valid_ && valid_ ){
			return ( other.content_== content_ );
		}
		return ( false );
	}
    
    bool operator != ( const optional& other ) const {
		T3_ASSERT_MSG( valid_, "It's no initialized value." );
        return !other.operator==(*this);
    }
    
    bool operator == ( const T& other ) const {
		T3_ASSERT_MSG( valid_, "It's no initialized value." );
		if ( valid_ ){
			return ( other == content_ );
		}
		return ( false );
	}
    
    bool operator != ( const T& other ) const {
		T3_ASSERT_MSG( valid_, "It's no initialized value." );    
        return !( operator==(other) );
    }
    
	bool operator < ( const optional& other ) const {
		if ( other.valid_ && valid_ ){
			return ( other.content_ < content_ );
		}
		return ( false );
	}

	bool operator < ( const T& other ) const {
		if ( valid_ ){
			return ( other < content_ );
		}
		return ( false );
	}

	bool operator > ( const optional& other ) const {
		if ( other.valid_ && valid_ ){
			return ( other.content_ > content_ );
		}
		return ( false );
	}

	bool operator > ( const T& other ) const {
		if ( valid_ ){
			return ( other > content_ );
		}
		return ( false );
	}



public:
	bool isValid() const {
		return ( valid_ );
	}
	

	void clear() {
		valid_ = false;
	}


private:
	T content_;
	bool valid_;
};



} // namespace t3

#endif // TRI_OPTIONAL_HPP_INCLUDED
