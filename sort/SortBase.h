#pragma once
#include "Base.h"


class SortBase
{
public:
    SortBase();
    virtual ~SortBase();

    virtual void sort(int arr[], uint size) = 0;

protected:
    ullint timeComlexity;
    ullint spaceComplexity;
};


