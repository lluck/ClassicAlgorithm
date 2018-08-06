#pragma once
#include "SortBase.h"

class HeapSort :
	public SortBase
{
public:
	HeapSort();
	virtual ~HeapSort();

	void sort(int arr[], uint size);

	// 建立一个最大堆, 时间复杂度O(n)
	void buildBigHeap(int arr[], uint size);

	// 从A[i]向下进行堆调整
	void heapify(int arr[], uint i, uint size);
};

