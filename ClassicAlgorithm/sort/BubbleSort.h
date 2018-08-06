#pragma once
#include "SortBase.h"


class BubbleSort :
	public SortBase
{
public:
	BubbleSort();
	virtual ~BubbleSort();

	void sort(int arr[], uint size);
};

