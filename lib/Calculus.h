#pragma once
#include <Arduino.h>
#include "Eigen/Eigen"
#include "Helper.h"

namespace Calculus
{
    template <typename T>
    class Differential
    {
    public:

        Differential() { reset(); }
        Differential(T gain) : gain_(gain) { reset(); }

        template <typename U = T, typename std::enable_if<!EMBEDDEDUTILS_HAS_FUNCTION(U, array)>::type* = nullptr>
        inline T get(const T& integral, float dt)
        {
            T newVal;
            newVal  = integral * gain_ - buffer_;
            buffer_ += gain_ * newVal * dt;
            return newVal;
        }

        template <typename U = T, typename std::enable_if<EMBEDDEDUTILS_HAS_FUNCTION(U, array)>::type* = nullptr>
        inline T get(const T& integral, float dt)
        {
            T newVal = integral.array() * gain_.array() - buffer_.array();
            buffer_ = buffer_.array() + gain_.array() * newVal.array() * dt;
            return newVal;
        }

        template <typename U = T, typename std::enable_if<EMBEDDEDUTILS_HAS_FUNCTION(U, zero)>::type* = nullptr>
        inline void reset() { buffer_ = U::zero(); }

        template <typename U = T, typename std::enable_if<EMBEDDEDUTILS_HAS_FUNCTION(U, setZero)>::type* = nullptr>
        inline void reset() { buffer_.setZero(); }

        template <typename U = T, typename std::enable_if<std::is_floating_point<U>::value>::type* = nullptr>
        inline void reset() { buffer_ = 0.0; }

        inline void setGain(const T& gain) { gain_ = gain; }

    private:

        T gain_;
        T buffer_;
    };


    template <typename T>
    class Integral
    {
    public:

        Integral() { reset(); }

        template <typename U = T, typename std::enable_if<!EMBEDDEDUTILS_HAS_FUNCTION(U, array)>::type* = nullptr>
        inline const T& get(const T& differential, float dt)
        {
            buffer_ += differential * dt;
            return buffer_;
        }

        template <typename U = T, typename std::enable_if<EMBEDDEDUTILS_HAS_FUNCTION(U, array)>::type* = nullptr>
        inline const T& get(const T& differential, float dt)
        {
            buffer_ = buffer_.array() + differential.array() * dt;
            return buffer_;
        }

        template <typename U = T, typename std::enable_if<EMBEDDEDUTILS_HAS_FUNCTION(U, zero)>::type* = nullptr>
        inline void reset() { buffer_ = U::zero(); }

        template <typename U = T, typename std::enable_if<EMBEDDEDUTILS_HAS_FUNCTION(U, setZero)>::type* = nullptr>
        inline void reset() { buffer_.setZero(); }

        template <typename U = T, typename std::enable_if<std::is_floating_point<U>::value>::type* = nullptr>
        inline void reset() { buffer_ = 0.0; }

private:

        T buffer_;
    };

}
