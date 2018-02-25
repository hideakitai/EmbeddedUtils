#pragma once
#include <Arduino.h>

namespace Filter
{
    template <typename T>
    class LPF
    {
    public:
        LPF() { reset(); }
        LPF(T gain) : gain_(gain), buffer_() {}

        inline T get(const T& curr_val, float dt)
        {
            T new_val = curr_val;
            new_val += (new_val - buffer_) * gain_ * (double)dt;
            buffer_ = new_val;
            return new_val;
        }

        inline void reset() { buffer_ = T::zero(); }
        inline void setGain(T gain) { gain_ = gain; }

    private:
        T gain_;
        T buffer_;
    };

    template <> inline Eigen::Vector3f LPF<Eigen::Vector3f>::get(const Eigen::Vector3f& curr_val, float dt)
    {
        Eigen::Vector3f new_val = curr_val.array() + (new_val.array() - buffer_.array()) * gain_.array() * (double)dt;
        buffer_ = new_val.matrix();
        return new_val;
    }

    template <> inline void LPF<float>::reset() { buffer_ = 0.0; }
    template <> inline void LPF<double>::reset() { buffer_ = 0.0; }
    template <> inline void LPF<Eigen::Vector3f>::reset() { buffer_ = Eigen::Vector3f::Zero(); }

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
