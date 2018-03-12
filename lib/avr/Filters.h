#pragma once
#ifndef EMBEDDEDUTILS_FILTERS_H
#define EMBEDDEDUTILS_FILTERS_H

namespace Filter
{
    template <typename T>
    class LPF
    {
    public:
        LPF(float gain) : gain_(gain), buffer_(0.0) {}

        inline T get(const T& curr_val, float dt)
        {
            T new_val = curr_val;
            new_val += (new_val - buffer_) * gain_ * (double)dt;
            buffer_ = new_val;
            return new_val;
        }

        inline void reset() { buffer_ = T::zero(); }
        inline void setGain(float gain) { gain_ = gain; }

    private:
        double gain_;
        T buffer_;
    };

    template <> inline void LPF<float>::reset() { buffer_ = 0.0; }
    template <> inline void LPF<double>::reset() { buffer_ = 0.0; }

    template <typename T>
    class HPF
    {
        HPF(float gain) : gain_(gain), buffer_(0.0) {}

        inline T get(const T& curr_val, float dt)
        {
            T new_val = curr_val - buffer_;
            buffer_ += new_val * gain_ * dt;
            return new_val;
        }

        inline void reset() { buffer_ = T::zero(); }
        inline void setGain(float gain) { gain_ = gain; }

    private:
        float gain_;
        T buffer_;
    };

    template <> inline void HPF<float>::reset() { buffer_ = 0.0; }
    template <> inline void HPF<double>::reset() { buffer_ = 0.0; }

//    template <typename T>
//    class BPF
//    {
//
//    };

}

#endif // EMBEDDEDUTILS_FILTERS_H
