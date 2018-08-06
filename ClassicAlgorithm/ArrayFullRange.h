#pragma once
#include "Base.h"

class ArrayFullRange
{
public:
    ArrayFullRange();
    virtual ~ArrayFullRange();

    void fullRange(char arr[], uint size);
private:
    void fullRangeRecursion(char arr[], uint pos, uint len);
};

