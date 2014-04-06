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

    int getChannel() const {
        return channel_;
    }
    
    int getBitPerSamle() const {
        return bit_per_sample_;
    }
    
    int getSamplingRate() const {
        return sampling_rate_;
    }

    size_t getDataSize() const {
        return size_;
    }
    
    const uint8_t* getData() const {
        return data_;
    }

private:
    uint8_t* data_;
    size_t size_;
    int channel_;
    
    int bit_per_sample_;
    int sampling_rate_;

};


}   // namespace audio
}   // namespace t3

#endif // TRI_WAV_HPP_INCLUDED
