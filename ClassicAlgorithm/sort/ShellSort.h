#pragma once
#include "SortBase.h"


class ShellSort :
    public SortBase
{
public:
    ShellSort();
    virtual ~ShellSort();

    // 交叉处理各分组数据
    void sort(int arr[], uint size);
};

