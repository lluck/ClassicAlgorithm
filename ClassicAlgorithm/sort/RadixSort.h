#pragma once
#include "SortBase.h"
class RadixSort :
    public SortBase
{
public:
    RadixSort();
    virtual ~RadixSort();

    void sort(int arr[], uint size);

private:
    void countSort(int arr[], uint size, int pow);
};

