
#include "gfx/tri_image_png.hpp"
#include <iostream>
#include "dbg/tri_dbg.hpp"
#include "kernel/tri_kernel.hpp"
#include "platform/platform_sdk.hpp"



namespace  {


    
struct my_png_buffer {
    const uint8_t* data_;
    std::size_t data_len_;
    uint32_t data_offset_;
};

void png_memread_func(
    png_structp png_ptr,
    png_bytep buf,
    png_size_t size
) {
    my_png_buffer* png_buff = (my_png_buffer*)png_get_io_ptr(png_ptr);
    if (png_buff->data_offset_ + size <= png_buff->data_len_) {
        memcpy(buf, png_buff->data_ + png_buff->data_offset_, size);
        png_buff->data_offset_ += size;
    }
    else {
        png_error(png_ptr,"png_mem_read_func failed");
    }
}
    
void png_data_read(
    png_structp png_ptr,
    my_png_buffer* file
) {
    png_set_read_fn(
        png_ptr,
        (png_voidp)file,
        (png_rw_ptr)png_memread_func
    );
}

}   // unname namespace


namespace t3 {

// *********************************************
//  コンストラクタ
PngImage::PngImage(std::string path)
{
    FILE* fp;
    
    fp = fopen( path.c_str(), "rb" );
    png_structp png_ptr = png_create_read_struct(
        PNG_LIBPNG_VER_STRING,
        nullptr,
        nullptr,
        nullptr
    );
    
    png_infop info_ptr = png_create_info_struct( png_ptr );
    
    png_init_io( png_ptr, fp );
    png_read_info( png_ptr,info_ptr );
    png_get_IHDR(
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
    data_ = T3_NEW uint8_t[size_];
    
    uint8_t** rec = T3_NEW uint8_t*[height_];
    
    for ( int i = 0; i < height_; ++i ){
        rec[i] = &data_[i*rb];
    }
    
    png_read_image( png_ptr, rec );
    
    png_destroy_read_struct( &png_ptr, &info_ptr, nullptr );
 
    fclose( fp );
}


PngImage::PngImage(
    File& file
) {
    png_structp png_ptr = png_create_read_struct(
        PNG_LIBPNG_VER_STRING,
        nullptr,
        nullptr,
        nullptr
    );
    T3_NULL_ASSERT(png_ptr);


    //  本物のpngデータか確認
    bool is_png = png_check_sig((png_bytep)file.getData(), 8);
    T3_ASSERT(is_png);



    png_infop info_ptr = png_create_info_struct(png_ptr);
    T3_NULL_ASSERT(info_ptr);

    my_png_buffer mybuf;
    mybuf.data_ = file.getData();
    mybuf.data_len_ = file.getDataSize();
    mybuf.data_offset_ = 0;
    png_data_read(png_ptr, &mybuf);
    png_read_info(png_ptr, info_ptr);
    png_get_IHDR(
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
    data_ = T3_NEW uint8_t[size_];
    
    uint8_t** rec = T3_NEW uint8_t*[height_];
    
    for ( int i = 0; i < height_; ++i ){
        rec[i] = &data_[i*rb];
    }

    png_read_image( png_ptr, rec );
    
    png_destroy_read_struct( &png_ptr, &info_ptr, nullptr );


    T3_DELETE[] rec;
}
    
// *********************************************
//  デストラクタ
PngImage::~PngImage(){
    T3_TRACE( "png data is deleted." );


    T3_DELETE[] data_;
}
    
    
    
}   // namespace t3














