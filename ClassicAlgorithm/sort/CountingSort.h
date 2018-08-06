#pragma once
#include "SortBase.h"


class CountingSort :
    public SortBase
{
public:
    CountingSort();
    virtual ~CountingSort();

    void sort(int arr[], uint size);
};

