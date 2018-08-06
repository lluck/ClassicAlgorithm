#pragma once
#include "SortBase.h"

class MergeSort :
    public SortBase
{
public:
	MergeSort();
    virtual ~MergeSort();

    static int merge(int arr[], uint left, uint mid, uint right);

	// 非递归(迭代)实现的归并排序(自底向上)
    void sort(int arr[], uint size);

	// 递归实现的归并排序(自顶向下)
	void sortRecursion(int arr[], uint left, uint right);
};

