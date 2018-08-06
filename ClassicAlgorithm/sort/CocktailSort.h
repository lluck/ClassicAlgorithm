#pragma once
#include "SortBase.h"

class CocktailSort :
	public SortBase
{
public:
	CocktailSort();
	virtual ~CocktailSort();

	void sort(int arr[], uint size);
};

