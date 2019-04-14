#pragma once
#include"ibrightimage.h"
class IThreshHoldAlgorithm
{
public:
    virtual int FindTreshHold(const IBrightImage& image) = 0;
};
