#pragma once
#include <Arduino.h>

namespace Calculus
{
    template <typename T>
    class Differential
    {
    public:
        Differential(float gain) : gain_(gain), buffer_(0.0) {}

        inline T get(const T& integral, const float& dt)
        {
            T newVal;
            newVal  = gain_ * integral - buffer_;
            buffer_ += gain_ * newVal * dt;
            return newVal;
        }

        inline void reset() { buffer_ = T::zero(); }
        inline void setGain(float gain) { gain_ = gain; }

    private:
        float gain_;
        T buffer_;
    };

    template <> inline void Differential<float>::reset() { buffer_ = 0.0; }
    template <> inline void Differential<double>::reset() { buffer_ = 0.0; }

    template <typename T>
    class Integral
    {
    public:
        Integral() : buffer_(0.0) {}

        inline const T& get(T& differential, float& dt)
        {
            buffer_ += differential * dt;
            return buffer_;
        }

        inline void reset() { buffer_ = T::zero(); }

private:
        T buffer_;
    };

    template <> inline void Integral<float>::reset() { buffer_ = 0.0; }
    template <> inline void Integral<double>::reset() { buffer_ = 0.0; }
}
