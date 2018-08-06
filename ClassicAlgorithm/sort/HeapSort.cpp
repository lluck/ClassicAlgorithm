#include "HeapSort.h"



HeapSort::HeapSort()
{
}


HeapSort::~HeapSort()
{
}

/*
堆排序是指利用堆这种数据结构所设计的一种选择排序算法。堆是一种近似完全二叉树的结构（通常堆是通过一维数组来实现的），
并满足性质：以最大堆（也叫大根堆、大顶堆）为例，其中父结点的值总是大于它的孩子节点。
定义堆排序的过程：
	1.由输入的无序数组构造一个最大堆，作为初始的无序区
	2.把堆顶元素（最大值）和堆尾元素互换
	3.把堆（无序区）的尺寸缩小1，并调用heapify(A, 0)从新的堆顶元素开始进行堆调整
	4.重复步骤2，直到堆的尺寸为1
*/

// 分类 -------------- 内部比较排序
// 数据结构 ---------- 数组
// 最差时间复杂度 ---- O(nlogn)
// 最优时间复杂度 ---- O(nlogn)
// 平均时间复杂度 ---- O(nlogn)
// 所需辅助空间 ------ O(1)
// 稳定性 ------------ 不稳定
void HeapSort::sort(int arr[], uint size)
{
	if (!arr || size < 2)
		return;

	uint heapSize = size;
	buildBigHeap(arr, size);

	// 堆（无序区）元素个数大于1，未完成排序
	while (heapSize > 1)
	{
		// 将堆顶元素与堆的最后一个元素互换，并从堆中去掉最后一个元素
		// 此处交换操作很有可能把后面元素的稳定性打乱，所以堆排序是不稳定的排序算法
		--heapSize;
		swap(arr[0], arr[heapSize]);
		// 从新的堆顶元素开始向下进行堆调整，时间复杂度O(logn)
		heapify(arr, 0, heapSize);
	}
}


// 建立一个最大堆, 时间复杂度O(n)
void HeapSort::buildBigHeap(int arr[], uint size)
{
	// 倒序处理, 减1留出(直接)子节点的空间
	// unsigned int 不能减至-1
	uint len = size / 2 - 1;
	for (uint i = 0; i <= len; ++i)
	{
		// 从每一个非叶结点开始向下进行堆调整
		heapify(arr, len - i, size);
	}
}


// 从A[i]向下进行堆调整
void HeapSort::heapify(int arr[], uint i, uint size)
{
	uint leftChild = 2 * i + 1;			// 左孩子索引
	uint rightChild = 2 * i + 2;		// 右孩子索引
	uint max = i;

	// 寻找(直接)子节点中最大值, 防止超出数组范围
	if (leftChild < size && arr[leftChild] > arr[max])
		max = leftChild;
	if (rightChild < size && arr[rightChild] > arr[max])
		max = rightChild;

	if (max != i)
	{
		// 把当前结点和它的最大(直接)子节点进行交换
		swap(arr[max], arr[i]);
		// 递归调用，继续从当前结点的最大(直接)子节点向下进行堆调整, 直到遍历整个数组完成
		heapify(arr, max, size);
	}
}



int main_hs(int argc, char* argv[])
{
	int arr[12] = { 4, 3, 2, 1, 0, 9, 8, 7, 4, 2, -1, 2 };
    //int arr[9] = { 5, 2, 9, 4, 7, 6, 1, 3, 8 };
	int size = sizeof(arr) / sizeof(arr[0]);
	HeapSort st;

	printf("排序前:");
	printArr(arr, size);
	st.sort(arr, size);
	printf("排序后:");
	printArr(arr, size);

	return 0;
}