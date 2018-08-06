#pragma once
#include "SortBase.h"

class HeapSort :
	public SortBase
{
public:
	HeapSort();
	virtual ~HeapSort();

	void sort(int arr[], uint size);

	// ����һ������, ʱ�临�Ӷ�O(n)
	void buildBigHeap(int arr[], uint size);

	// ��A[i]���½��жѵ���
	void heapify(int arr[], uint i, uint size);
};

