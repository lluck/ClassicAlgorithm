#pragma once
#include "SortBase.h"


class InsertionSort :
	public SortBase
{
public:
	InsertionSort();
	virtual ~InsertionSort();

	void sort(int arr[], uint size);
};

