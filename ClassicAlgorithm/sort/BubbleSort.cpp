#include "BubbleSort.h"



BubbleSort::BubbleSort()
{
}


BubbleSort::~BubbleSort()
{
}


/*
它重复地走访过要排序的元素，依次比较相邻两个元素，如果他们的顺序错误就把他们调换过来，直到没有元素再需要交换，排序完成。
这个算法的名字由来是因为越小(或越大)的元素会经由交换慢慢“浮”到数列的顶端。

冒泡排序算法的运作如下：
	1.比较相邻的元素，如果前一个比后一个大，就把它们两个调换位置。
	2.对每一对相邻元素作同样的工作，从开始第一对到结尾的最后一对。这步做完后，最后的元素会是最大的数。
	3.针对所有的元素重复以上的步骤，除了最后一个。
	4.持续每次对越来越少的元素重复上面的步骤，直到没有任何一对数字需要比较。
*/

// 分类 -------------- 内部比较排序
// 数据结构 ---------- 数组
// 最差时间复杂度 ---- O(n^2)
// 最优时间复杂度 ---- 如果能在内部循环第一次运行时,使用一个旗标来表示有无需要交换的可能,可以把最优时间复杂度降低到O(n)
// 平均时间复杂度 ---- O(n^2)
// 所需辅助空间 ------ O(1)
// 稳定性 ------------ 稳定

void BubbleSort::sort(int arr[], uint size)
{
	if (!arr || size < 2)
		return;

	// 每次是否有被交换的元素, 判断数组是否已经排序完成
	int hasChanged = 0;

	for (uint i = 0; i < size - 1; ++i)
	{
		hasChanged = 0;

		for (uint j = i + 1; j < size; ++j)
		{
			if (arr[i] > arr[j])
			{
				swap(arr[i], arr[j]);
				hasChanged = 1;
			}
		}

		// 没有元素被交换, 判断数组是否已经排序完成
		if (hasChanged == 0)
			break;

		printArr(arr, size);
		printf("hasChanged:%d\n", hasChanged);
	}

}


int main_bs(int argc, char* argv[])
{
	int arr[14] = { 4, 3, 2, 1, 0, 9, 8, 7, 4, 2, -1, 2, 9, 10 };
	//int arr[9] = { 5, 2, 9, 4, 7, 6, 1, 3, 8 };
	int size = sizeof(arr) / sizeof(arr[0]);
	BubbleSort st;

	printf("排序前:\n");
	printArr(arr, size);
	st.sort(arr, size);
	printf("排序后:\n");
	printArr(arr, size);

	return 0;
}
