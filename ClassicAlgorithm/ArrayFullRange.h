#pragma once
#include "Base.h"

class ArrayFullRange
{
public:
    ArrayFullRange();
    virtual ~ArrayFullRange();

    void fullRange(char arr[], uint size);

private:
    void fullRangeByRecursion(char arr[], uint pos, uint len);
    bool neddSwap(char arr[], uint begin, uint end);

    void fullRangeByDictionary(char arr[], uint size);
    bool hasNext(uint arr[], uint size);
};