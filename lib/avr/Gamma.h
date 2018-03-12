#pragma once
#ifndef EMBEDDEDUTILS_GAMMA_H
#define EMBEDDEDUTILS_GAMMA_H

template <typename TYPE, size_t SIZE>
class GammaTable
{
public:

    GammaTable(const float gamma, const size_t scale = static_cast<float>(SIZE))
    : gamma(gamma), scale(scale)
    {
        create();
    }

    void setGamma(const float g)
    {
        gamma = g;
        create();
    }

    void setScale(const float s)
    {
        scale = s;
        create();
    }

    const TYPE& operator [](const size_t index) const { return gamma_array[index]; }
    const size_t size() const { return gamma_array.size(); }

    const float getGamma() const { return gamma; }
    const float getRange() const { return scale; }

private:

    void create()
    {
        for (size_t i = 0; i < gamma_array.size(); ++i)
        {
            gamma_array[i] = static_cast<TYPE>(pow(static_cast<float>(i) / static_cast<float>(SIZE), gamma) * scale);
        }
    }

    float gamma;
    float scale;
    RingQueue<TYPE> gamma_array {size};
};

#endif // EMBEDDEDUTILS_GAMMA_H
