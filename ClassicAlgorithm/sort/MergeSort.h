#pragma once
#include "SortBase.h"

class MergeSort :
    public SortBase
{
public:
	MergeSort();
    virtual ~MergeSort();

    static int merge(int arr[], uint left, uint mid, uint right);

	// �ǵݹ�(����)ʵ�ֵĹ鲢����(�Ե�����)
    void sort(int arr[], uint size);

	// �ݹ�ʵ�ֵĹ鲢����(�Զ�����)
	void sortRecursion(int arr[], uint left, uint right);
};

