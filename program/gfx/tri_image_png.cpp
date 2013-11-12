
#include "tri_image_png.hpp"
#include <iostream>
#include "../dbg/tri_dbg.hpp"
#include "../kernel/tri_kernel.hpp"



namespace libpng {

#include "png.h"
    
}   // namespace libpng



namespace t3 {

// *********************************************
//  コンストラクタ
PngImage::PngImage( const char* const path )
{
    FILE* fp;
    
    libpng::png_structp png_ptr;
    libpng::png_infop info_ptr;
    fp = fopen( path, "rb" );
    png_ptr = libpng::png_create_read_struct(
        PNG_LIBPNG_VER_STRING,
        nullptr,
        nullptr,
        nullptr
    );
    
    info_ptr = libpng::png_create_info_struct( png_ptr );
    
    libpng::png_init_io( png_ptr, fp );
    libpng::png_read_info( png_ptr,info_ptr );
    libpng::png_get_IHDR( 
        png_ptr,
        info_ptr,
        &width_,
        &height_,
        &bit_depth_,
        &color_type_,
        &interlace_type_, 
        nullptr,
        nullptr
    );
    T3_TRACE( "w= %d  h=%d\n", width_, height_ );
    
    // メモリ領域確保
    int rb = (int)png_get_rowbytes(png_ptr, info_ptr);
    size_ = height_ * rb;
    data_ = new uint8_t[size_];
    
    uint8_t** rec = new uint8_t*[height_];
    
    for ( int i = 0; i < height_; ++i ){
        rec[i] = &data_[i*rb];
    }
    
    libpng::png_read_image( png_ptr, rec );
    
    libpng::png_destroy_read_struct( &png_ptr, &info_ptr, nullptr );
  //  delete[] rec;
    fclose( fp );
}
    
    
// *********************************************
//  デストラクタ
PngImage::~PngImage(){
    T3_TRACE( "png data is deleted." );
//    delete data_;
}
    
    
    
}   // namespace t3














