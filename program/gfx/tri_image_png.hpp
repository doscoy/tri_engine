
#ifndef TRI_PNG_HPP_INCLUDED
#define TRI_PNG_HPP_INCLUDED


namespace t3 {
    
struct PngImage {
    
    explicit PngImage( const char* const path );
    ~PngImage();
    unsigned int width_;
    unsigned int height_;
    unsigned char* data_;
    int bit_depth_;
    int color_type_;
    int interlace_type_;
    int size_;
};


}   // namespace t3

#endif // TRI_PNG_HPP_INCLUDED
