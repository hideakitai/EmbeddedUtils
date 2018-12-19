#pragma once
#ifndef EMBEDDEDUTILS_GAMMA_H
#define EMBEDDEDUTILS_GAMMA_H

template <typename TYPE, std::size_t SIZE>
class GammaTable
{
public:

    GammaTable(const float gamma, const std::size_t scale = static_cast<float>(SIZE))
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

    const TYPE& operator [](const std::size_t index) const { return gamma_array[index]; }
    const std::size_t size() const { return gamma_array.size(); }

    const float getGamma() const { return gamma; }
    const float getRange() const { return scale; }

private:

    void create()
    {
        for (std::size_t i = 0; i < gamma_array.size(); ++i)
        {
            gamma_array[i] = static_cast<TYPE>(std::pow(static_cast<float>(i) / static_cast<float>(SIZE), gamma) * scale);
        }
    }

    float gamma;
    float scale;
    RingQueue<TYPE, SIZE> gamma_array;
};

#endif // EMBEDDEDUTILS_GAMMA_H
