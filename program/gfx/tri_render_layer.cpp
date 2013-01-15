

#include "tri_render_layer.hpp"
#include <cstring>


namespace t3{

RenderLayer::RenderLayer()
    : pause_( false )
    , priority_( PRIORITY_NORMAL )
{
    
}

RenderLayer::~RenderLayer()
{

}

void RenderLayer::setPriority( const int priority )
{
    T3_ASSERT( priority >= PRIORITY_LOWEST && priority <= PRIORITY_HIGHEST  );
    priority_ = priority;
}

void RenderLayer::setLayerName( const char* const name )
{
    std::strncpy( layer_name_, name, LAYER_NAME_SIZE );
}



}   // namespace t3

