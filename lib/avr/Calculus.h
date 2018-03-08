#pragma once

namespace Calculus
{
    template <typename T>
    class Differential
    {
    public:
        Differential(T gain) : gain_(gain) { reset(); }

        inline T get(const T& integral, float dt)
        {
            T newVal;
            newVal  = gain_ * integral - buffer_;
            buffer_ += gain_ * newVal * dt;
            return newVal;
        }

        inline void reset() { buffer_ = T::zero(); }
        inline void setGain(const T& gain) { gain_ = gain; }

    private:
        T gain_;
        T buffer_;
    };

    template <> inline void Differential<float>::reset() { buffer_ = 0.0; }
    template <> inline void Differential<double>::reset() { buffer_ = 0.0; }

    template <typename T>
    class Integral
    {
    public:
        Integral() { reset(); }

        inline const T& get(const T& differential, float dt)
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
