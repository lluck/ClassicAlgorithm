#pragma once
#include "SortBase.h"


class ShellSort :
    public SortBase
{
public:
    ShellSort();
    virtual ~ShellSort();

    // ���洦�����������
    void sort(int arr[], uint size);
};

