#pragma once
#include "Base.h"

/*
Ô­ÎÄµØÖ·:http://www.cnblogs.com/eniac12/p/5329396.html
         http://www.cnblogs.com/eniac12/p/5332117.html
*/

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


