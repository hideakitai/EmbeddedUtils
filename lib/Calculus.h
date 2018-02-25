#pragma once
#include <Arduino.h>
#include "Eigen/Eigen"

namespace Calculus
{
    template <typename T>
    class Differential
    {
    public:

        Differential() { reset(); }
        Differential(T gain) : gain_(gain) { reset(); }

        inline T get(const T& integral, float dt)
        {
            T newVal;
            newVal  = integral * gain_ - buffer_;
            buffer_ += gain_ * newVal * dt;
            return newVal;
        }

        inline void reset() { buffer_.setZero(); }
        inline void setGain(const T& gain) { gain_ = gain; }

    private:
        T gain_;
        T buffer_;
    };

//    template <> inline T Differential<float>::get(const T& integral, float dt)
//    {
//        T newVal;
//        newVal  = integral * gain_ - buffer_;
//        buffer_ += gain_ * newVal * dt;
//        return newVal;
//    }
//
//    template <> inline T Differential<double>::get(const T& integral, float dt)
//    {
//        T newVal;
//        newVal  = integral * gain_ - buffer_;
//        buffer_ += gain_ * newVal * dt;
//        return newVal;
//    }
//
//    template <> inline T Differential<Vec3f>::get(const T& integral, float dt)
//    {
//        T newVal;
//        newVal  = integral * gain_ - buffer_;
//        buffer_ += gain_ * newVal * dt;
//        return newVal;
//    }

    template <> inline Eigen::Vector3f Differential<Eigen::Vector3f>::get(const Eigen::Vector3f& integral, float dt)
    {
        Eigen::Vector3f newVal = integral.array() * gain_.array() - buffer_.array();
        buffer_ = buffer_.array() + gain_.array() * newVal.array() * dt;
        return newVal;
    }

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

        inline void reset() { buffer_.setZero(); }

private:
        T buffer_;
    };

    template <> inline void Integral<float>::reset() { buffer_ = 0.0; }
    template <> inline void Integral<double>::reset() { buffer_ = 0.0; }
}
