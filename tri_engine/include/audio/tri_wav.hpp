#ifndef TRI_WAV3_HPP_INCLUDED
#define TRI_WAV3_HPP_INCLUDED

#include "kernel/io/tri_filepath.hpp"
#include <cstdint>

namespace t3 {
inline namespace audio {

class Wav {

public:
    Wav();
    ~Wav();

public:
    void load(FilePath& filepath);



private:
    uint8_t* data_;
    int channel_;
    int bit_per_sample_;
    int sampling_rate_;

};


}   // namespace audio
}   // namespace t3

#endif // TRI_WAV_HPP_INCLUDED
