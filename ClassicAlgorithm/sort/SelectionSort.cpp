#include "SelectionSort.h"



SelectionSort::SelectionSort()
{
}


SelectionSort::~SelectionSort()
{
}


/*
选择排序也是一种简单直观的排序算法。它的工作原理很容易理解：初始时在序列中找到最小（大）元素，放到序列的起始位置作为已排序序列；
然后，再从剩余未排序元素中继续寻找最小（大）元素，放到已排序序列的末尾。以此类推，直到所有元素均排序完毕。

注意选择排序与冒泡排序的区别：冒泡排序通过依次交换相邻两个顺序不合法的元素位置，从而将当前最小（大）元素放到合适的位置；
而选择排序每遍历一次都记住了当前最小（大）元素的位置，最后仅需一次交换操作即可将其放到合适的位置。

选择排序是不稳定的排序算法，不稳定发生在最小元素与A[i]交换的时刻。
比如序列：{ 5, 8, 5, 2, 9 }，一次选择的最小元素是2，然后把2和第一个5进行交换，从而改变了两个元素5的相对次序
*/

// 分类 -------------- 内部比较排序
// 数据结构 ---------- 数组
// 最差时间复杂度 ---- O(n^2)
// 最优时间复杂度 ---- O(n^2)
// 平均时间复杂度 ---- O(n^2)
// 所需辅助空间 ------ O(1)
// 稳定性 ------------ 不稳定

void SelectionSort::sort(int arr[], uint size)
{
	if (!arr || size < 2)
		return;

	uint minIndex = 0;

	// 每次是否有被交换的元素, 判断数组是否已经排序完成
	int hasChanged = 0;

	for (uint i = 0; i < size - 1; ++i)
	{
		minIndex = i;
		hasChanged = 0;

		// 找出未排序序列中的最小值
		for (uint j = i + 1; j < size; ++j)
		{
			if (arr[j] <= arr[minIndex])
			{
				minIndex = j;
			}
		}

		// 放到已排序序列的末尾，该操作很有可能把稳定性打乱，所以选择排序是不稳定的排序算法
		if (minIndex != i)
		{
			swap(arr[i], arr[minIndex]);
			hasChanged = 1;
		}

		printArr(arr, size);

		// 没有元素被交换, 判断数组是否已经排序完成
		if (hasChanged == 0)
			break;
	}
}


int main_ss(int argc, char* argv[])
{
	int arr[14] = { 4, 3, 2, 1, 0, 9, 8, 7, 4, 2, -1, 2, 9, 10 };
	//int arr[9] = { 5, 2, 9, 4, 7, 6, 1, 3, 8 };
	int size = sizeof(arr) / sizeof(arr[0]);
	SelectionSort st;

	printf("排序前:\n");
	printArr(arr, size);
	st.sort(arr, size);
	printf("排序后:\n");
	printArr(arr, size);

	return 0;
}