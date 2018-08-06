#pragma once
#include "SortBase.h"

class InsertionSortDichotomy :
    public SortBase
{
public:
    InsertionSortDichotomy();
    virtual ~InsertionSortDichotomy();

    void sort(int arr[], uint size);
};

