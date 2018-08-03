#pragma once
#include "SortBase.h"

class SortMerge :
    public SortBase
{
public:
    SortMerge();
    virtual ~SortMerge();

    static void merge(int arr[], uint left, uint mid, uint right);

    void sort(int arr[], uint size);
};

