#include "CocktailSort.h"



CocktailSort::CocktailSort()
{
}


CocktailSort::~CocktailSort()
{
}


/*
鸡尾酒排序，也叫定向冒泡排序，是冒泡排序的一种改进。此算法与冒泡排序的不同处在于从低到高然后从高到低，
而冒泡排序则仅从低到高去比较序列里的每个元素。他可以得到比冒泡排序稍微好一点的效能
*/

// 分类 -------------- 内部比较排序
// 数据结构 ---------- 数组
// 最差时间复杂度 ---- O(n^2)
// 最优时间复杂度 ---- 如果序列在一开始已经大部分排序过的话,会接近O(n)
// 平均时间复杂度 ---- O(n^2)
// 所需辅助空间 ------ O(1)
// 稳定性 ------------ 稳定

void CocktailSort::sort(int arr[], uint size)
{
	if (!arr || size < 2)
		return;

	uint left = 0;
	uint right = size - 1;

	// 每次是否有被交换的元素, 判断数组是否已经排序完成
	int hasChanged = 0;

	while (left < right)
	{
		hasChanged = 0;

		// 将最大元素放到后面
		for (uint i = left; i < right; ++i)
		{
			// 比较后面的元素:i + 1
			if (arr[i] > arr[i + 1])
			{
				swap(arr[i], arr[i + 1]);
				hasChanged = 1;
				printArr(arr, size);
				printf("left=%d, right=%d, hasChanged=%d, i=%d\n", left, right, hasChanged, i);
			}
		}

		// 后面的元素已经排序完成
		--right;

		printf("---\n");

		// 将最小元素放到前面
		for (uint j = right; j > left; --j)
		{
			// 比较前面的元素:j - 1
			if (arr[j - 1] > arr[j])
			{
				swap(arr[j - 1], arr[j]);
				hasChanged = 1;
				printArr(arr, size);
				printf("left=%d, right=%d, hasChanged=%d, j =%d\n", left, right, hasChanged, j);
			}
		}

		// 前面的元素已经排序完成
		++left;

		// 没有元素被交换, 判断数组是否已经排序完成
		if (hasChanged == 0)
			break;

		printf("left=%d, right=%d, hasChanged=%d\n", left, right, hasChanged);
		printArr(arr, size);
	}
	// end of while loop
}


int main_cts(int argc, char* argv[])
{
	int arr[14] = { 4, 3, 2, 1, 0, 9, 8, 7, 4, 2, -1, 2, 9, 10 };
	//int arr[9] = { 5, 2, 9, 4, 7, 6, 1, 3, 8 };
	int size = sizeof(arr) / sizeof(arr[0]);
	CocktailSort st;

	printf("排序前:\n");
	printArr(arr, size);
	st.sort(arr, size);
	printf("排序后:\n");
	printArr(arr, size);

	return 0;
}
