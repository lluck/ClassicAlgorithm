#include "QuickSort.h"



QuickSort::QuickSort()
{
}


QuickSort::~QuickSort()
{
}


/*
快速排序是由东尼·霍尔所发展的一种排序算法。在平均状况下，排序n个元素要O(nlogn)次比较。在最坏状况下则需要O(n^2)次比较，
但这种状况并不常见。事实上，快速排序通常明显比其他O(nlogn)算法更快，因为它的内部循环可以在大部分的架构上很有效率地被实现出来。

快速排序使用分治策略(Divide and Conquer)来把一个序列分为两个子序列。步骤为
	1.从序列中挑出一个元素，作为"基准"(pivot).
	2.把所有比基准值小的元素放在基准前面，所有比基准值大的元素放在基准的后面（相同的数可以到任一边），这个称为分区(partition)操作。
	3.对每个分区递归地进行步骤1~2，递归的结束条件是序列的大小是0或1，这时整体已经被排好序了。

快速排序是不稳定的排序算法，不稳定发生在基准元素与A[tail+1]交换的时刻。
比如序列：{ 1, 3, 4, 2, 8, 9, 8, 7, 5 }，基准元素是5，一次划分操作后5要和第一个8进行交换，从而改变了两个元素8的相对次序
*/

// 分类 ------------ 内部比较排序
// 数据结构 --------- 数组
// 最差时间复杂度 ---- 每次选取的基准都是最大（或最小）的元素，导致每次只划分出了一个分区，需要进行n-1次划分才能结束递归，时间复杂度为O(n^2)
// 最优时间复杂度 ---- 每次选取的基准都是中位数，这样每次都均匀的划分出两个分区，只需要logn次划分就能结束递归，时间复杂度为O(nlogn)
// 平均时间复杂度 ---- O(nlogn)
// 所需辅助空间 ------ 主要是递归造成的栈空间的使用(用来保存left和right等局部变量)，取决于递归树的深度，一般为O(logn)，最差为O(n)       
// 稳定性 ---------- 不稳定

void QuickSort::sort(int arr[], uint size)
{
	if (!arr || size < 2)
		return;

	uint left = 0;
	uint right = size - 1;
	uint pivot = left;

	// 左右2边没有遍历完成
	while (left < right)
	{
		// 从右边开始查询比基准值小的位置
		while (left < right && arr[right] >= arr[pivot])
			--right;

		// 从左边查询比基准值大的位置
		while (left < right && arr[left] <= arr[pivot])
			++left;
		
		// 2边位置相等时不用交换
		if(left < right)
			swap(arr[left], arr[right]);

		printArr(arr, size);
	}

	// 使用left的值, 和上面while循环中left、right哪个先处理有关系, 使用后面处理的值, 即left值
	swap(arr[left], arr[pivot]);
	printArr(arr, size);

	// 依次递归遍历左右子数组, 直到子数组长度为1
	sort(arr, left);
	sort(arr + left + 1, size - left - 1);
}


int main_qs(int argc, char* argv[])
{
	int arr[12] = { 4, 3, 2, 1, 0, 9, 8, 7, 4, 2, -1, 2 };
	//int arr[5] = { 3, 4, 5, 1, 2 };
	int size = sizeof(arr) / sizeof(arr[0]);
	QuickSort st;

	printf("排序前:");
	printArr(arr, size);
	st.sort(arr, size);
	printf("排序后:");
	printArr(arr, size);

	return 0;
}

