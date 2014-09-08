#ifndef TRI_WAV3_HPP_INCLUDED
#define TRI_WAV3_HPP_INCLUDED

#include "kernel/io/tri_filepath.hpp"
#include <cstdint>
#include <fstream>

namespace t3 {
inline namespace audio {

class Wav {

public:
    struct Info {
        Info()
            : size_(0)
            , time_(0.0f)
            , channel_(0)
            , bit_per_sample_(0)
            , sampling_rate_(0)
            , data_pos_(0)
        {
        }
    
        size_t size_;
        float time_;
        short channel_;
        short bit_per_sample_;
        int sampling_rate_;
        std::streamoff data_pos_;
    };

public:
    Wav();
    ~Wav();

public:
    void load(const FilePath& filepath);

    
    
    int bitPerSample() const {
        return info_.bit_per_sample_;
    }
    
    int samplingRate() const {
        return info_.sampling_rate_;
    }

    size_t size() const {
        return info_.size_;
    }
    
    const uint8_t* getData() const {
        return data_;
    }

    int channel() const {
        return info_.channel_;
    }

    bool isStereo() const {
        return channel() == 2;
    }
    
    bool isMonaural() const {
        return channel() == 1;
    }
    
    float time() {
        return info_.time_;
    }
    
    
    void open(const FilePath& filepath);
    size_t read(void* out, size_t size);
    void close();
    void readReset();


private:
    std::ifstream file_;
    Info info_;
    size_t readed_size_;
    uint8_t* data_;
};


}   // namespace audio
}   // namespace t3

#endif // TRI_WAV_HPP_INCLUDED
