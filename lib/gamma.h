//
//  gammma.h
//
//  Created by yutaAsai on 2017/02/06.
//
//

#ifndef gammma_h
#define gammma_h
#include <cmath>
#include <array>

template <typename type , std::size_t size>
void makeGamma(float gamma ,std::array<type ,size> & gammaArray){
    uint64_t maxSize = gammaArray.size() - 1;
    for(int i = 0 ; i < gammaArray.size() ; ++i){
        gammaArray[i] = (type) (std::pow( (float) i / (float)maxSize , gamma) * maxSize + 0.5);
    }
}

template <typename type , std::size_t size>
void makeGammaWithRangeAll(float gamma ,type InputMax ,type OutputMax ,std::array<type ,size> & gammaArray){
    for(int i = 0 ; i < gammaArray.size() ; ++i){
        gammaArray[i] = (type) (std::pow( (float) i / (float)InputMax , gamma) * OutputMax + 0.5);
    }
}

template <typename type , std::size_t size>
void makeGammaWithRange(float gamma ,type InputMax ,type OutputMax ,std::array<type ,size> & gammaArray){
    for(int i = 0 ; i < gammaArray.size() ; ++i){
        gammaArray[i] = (type) (std::pow( (float) gammaArray[i] / (float)InputMax , gamma) * OutputMax + 0.5);
    }
}

template <typename type , std::size_t arraySize>
class GammaTable{
public:
    GammaTable()
            :inMax(arraySize - 1)
            ,outMax(arraySize - 1)
            ,gammaVal(1.0)
    {
        for(uint32_t i  = 0 ; i < gammaArray.size(); ++i){
            gammaArray[i] = i;
        }
    }

    GammaTable(const float gammaValue)
            :inMax(arraySize - 1)
            ,outMax(arraySize - 1)
            ,gammaVal(gammaValue)
    {
        makeGammaWithRange(gammaVal(gammaValue) ,inMax ,outMax ,gammaArray);
    }

    GammaTable(const float gammaValue ,const type InputMaxRange ,const type OutputMaxRange)
            :inMax(InputMaxRange)
            ,outMax(OutputMaxRange)
            ,gammaVal(gammaValue)
    {
        makeGammaWithRangeAll(gammaVal,inMax ,outMax ,gammaArray);
    }

    void setGammaValue(const float gammaValue){
        gammaVal = gammaValue;
        makeGammaWithRangeAll(gammaVal ,inMax ,outMax ,gammaArray);
    }

    void setRange(const type InputMaxRange ,const type OutputMaxRange){
        inMax = InputMaxRange;
        outMax = OutputMaxRange;
        makeGammaWithRangeAll(gammaVal ,inMax ,outMax ,gammaArray);
    }

    type& operator [](const size_t index) {
        return gammaArray[index];
    }

    type& at(const size_t index) {
        return gammaArray.at(index);
    }

    std::size_t size() const{
        return gammaArray.size();
    }

private:
    type inMax,outMax;
    float gammaVal;
    std::array<type , arraySize> gammaArray;
};

#endif /* gammma_h */
