#pragma once
#include "SortBase.h"

class QuickSort :
	public SortBase
{
public:
	QuickSort();

	virtual ~QuickSort();

	void sort(int arr[], uint size);

};

