#ifndef TRI_RTTI_HPP_INCLUDED
#define TRI_RTTI_HPP_INCLUDED


namespace t3 {



class RTTI
{
public:
    RTTI( const char* class_name )
        : class_name_( class_name )
        , base_rtti_( nullptr )
    {
    }
    
    
    RTTI( const char* class_name, const RTTI& base )
        : class_name_( class_name )
        , base_rtti_( &base )
    {
    }
    
public:
    //  クラス名取得
    const char* getClassName() const {
        return class_name_;
    }
    
    //  指定のクラスか判定
    bool isExactly(const RTTI& rtti) const {
        return this == &rtti;
    }
    
    //  継承元か判定
    bool isDerivesFrom(const RTTI& rtti) const {
        const RTTI* compare = this;
        while (compare) {
            if (compare == &rtti){
                return true;
            }
            compare = compare->base_rtti_;
        }
        
        return false;
    }
    
private:
    //  コピー禁止
    RTTI( const RTTI& obj );
    RTTI& operator=( const RTTI& obj );
    
private:
    //  クラス名
    const char* class_name_;
    
    //  継承元クラス情報
    const RTTI* base_rtti_;
    
};

#define RTTI_DECLARE                        \
    public:                                 \
        virtual const ::t3::RTTI& getRTTI() {     \
            return rtti_;                   \
        }                                   \
        static const ::t3::RTTI rtti_;            \
        
        
        
#define RTTI_ROOT( name )                   \
    const ::t3::RTTI name::rtti_( #name )


#define RTTI_IMPL( name, parent )                       \
    const ::t3::RTTI name::rtti_( #name, parent::rtti_ ) 
        
        


}   // namespace t3
















#endif // TRI_RTTI_HPP_INCLUDED


