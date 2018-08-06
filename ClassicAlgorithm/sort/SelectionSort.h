#pragma once
#include "SortBase.h"

class SelectionSort :
	public SortBase
{
public:
	SelectionSort();
	virtual ~SelectionSort();

	void sort(int arr[], uint size);
};

