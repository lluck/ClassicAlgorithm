#include "MergeSort.h"


MergeSort::MergeSort()
{
}


MergeSort::~MergeSort()
{
}


/*

归并排序是创建在归并操作上的一种有效的排序算法，效率为O(nlogn)，1945年由冯·诺伊曼首次提出。
归并排序的实现分为递归实现与非递归(迭代)实现。
递归实现的归并排序是算法设计中分治策略的典型应用，我们将一个大问题分割成小问题分别解决，然后用所有小问题的答案来解决整个大问题。
非递归(迭代)实现的归并排序首先进行是两两归并，然后四四归并，然后是八八归并，一直下去直到归并了整个数组。

归并排序算法主要依赖归并(Merge)操作。归并操作指的是将两个已经排序的序列合并成一个序列的操作，归并操作步骤如下：
	1.申请空间，使其大小为两个已经排序序列之和，该空间用来存放合并后的序列
	2.设定两个指针，最初位置分别为两个已经排序序列的起始位置
	3.比较两个指针所指向的元素，选择相对小的元素放入到合并空间，并移动指针到下一位置
	4.重复步骤3直到某一指针到达序列尾
	5.将另一序列剩下的所有元素直接复制到合并序列尾
*/

// 分类 -------------- 内部比较排序
// 数据结构 ---------- 数组
// 最差时间复杂度 ---- O(nlogn)
// 最优时间复杂度 ---- O(nlogn)
// 平均时间复杂度 ---- O(nlogn)
// 所需辅助空间 ------ O(n)
// 稳定性 ------------ 稳定


/*
0  1  2  3  4  5  6  7  8  9
----------------------------
4  3  2  1  0  9  8  7  4  2
L           M              R
left = 0, mid = 4, right = 9, size = 10
arr[left...mid]和arr[mid+1...right]归并排序

-----------------------------------------------------------------------------------------------------------------
数组小和（单调和）:
数组小和的定义如下：例如，数组s=[1,3,5,2,4,6]
在s[0]的左边小于或等于s[0]的数的和为0
在s[1]的左边小于或等于s[1]的数的和为1
在s[2]的左边小于或等于s[2]的数的和为1+3=4
在s[3]的左边小于或等于s[3]的数的和为1
在s[4]的左边小于或等于s[4]的数的和为1+3+2=6
在s[5]的左边小于或等于s[5]的数的和为1+3+5+2+4=15
所以s的小和为0+1+4+1+6+15=27
给定一个数组s，实现函数返回s的小和。

二重循环暴力求解，时间复杂度O(n^2), 利用归并排序，在对有序子数组进行merge的同时，累加数组小和，时间复杂度O(nlogn)

-----------------------------------------------------------------------------------------------------------------
数组中的逆序对个数:
有一组数，对于其中任意两个数组，若前面一个大于后面一个数字，则这两个数字组成一个逆序对。
测试样例：
	[1,2,3,4,5,6,7,0], 8    返回：7

*/
int MergeSort::merge(int arr[], uint left, uint mid, uint right)
{
    uint i = left;
    uint j = mid + 1;
    uint len = right - left + 1;
    uint tmpIndex = 0;
    int * tmpArr = new int[len];

	int smallestSum = 0;
	int reversePairCount = 0;

    while (i <= mid && j <= right)
    {
        // 使用等于包含当前位置, 保证排序稳定性
		if (arr[i] <= arr[j])
		{
			// 当前一个数组元素小于或等于后一个数组元素时，累加小和
			// s[i] <= s[j] 等价于 s[i] <= s[j]...s[right]
			// 因为s[j]...s[right]已经排好序了, 所以s[i]小于s[j]...s[right]的每一个数
			smallestSum += arr[i] * (right - j + 1);

			tmpArr[tmpIndex++] = arr[i++];
		}
		else
		{
			// 当前一个数组元素大于后一个数组元素时，累加逆序对
			// s[i] > s[j] 等价于 s[i]...s[mid] > s[j]
			// 因为s[i]...s[mid]已经排好序了, 所以s[i]...s[mid]的每一个数大于s[j]
			reversePairCount += (mid - i + 1);

			tmpArr[tmpIndex++] = arr[j++];
		}
    }

    // 左边数组剩余部分处理
    for (; i <= mid; ++i)
        tmpArr[tmpIndex++] = arr[i];
    // 右边数组剩余部分处理
    for (; j <= right; ++j)
        tmpArr[tmpIndex++] = arr[j];

    // 数据写回原始数组
    for (i = 0; i < len; ++i)
        arr[left + i] = tmpArr[i];

	//return smallestSum;
	return reversePairCount;
}


/*
0  1  2  3  4  5  6  7  8  9 10
-------------------------------
4  3  2  1  0  9  8  7  4  2  0
LM R  LM R  LM R  LM R  LM R       i = 1, 每个数组长度为1, 每次归并处理数组长度 = 2
L  M     R  L  M     R             i = 2, 每个数组长度为2, 每次归并处理数组长度 = 4
L        M           R             i = 4, 每个数组长度为4, 每次归并处理数组长度 = 8
LM                   M        R    i = 8, 每个数组长度为8, 每次归并处理数组长度 = 16
left = 0, mid = 0, right = 1, size = 2
left = 0, mid = 1, right = 3, size = 4
arr[left...mid]和arr[mid+1...right]归并排序
*/
// 非递归(迭代)实现的归并排序(自底向上)
void MergeSort::sort(int arr[], uint size)
{
	if (!arr || size < 2)
		return;

    uint left = 0;
    uint mid = 0;
    uint right = 0;

	int smallestSum = 0;			 // 最小数组和
	int reversePairCount = 0;		// 数组中的逆序对个数
    
    // 外层循环时间复杂度log2N
    for (uint i = 1; i < size; i *= 2)
    {
        left = 0;
        right = 0;

        // 内存循环时间复杂度N
        for (int j = 0; right < size - 1; j += 2)
        {
            // 指向左边数组初始位置
            left = i * j;
            // 初始位置+数组长度
            mid = left + i - 1;
            // 右边数组还足够一个数组长度, 使用一个长度位置, 否则使用数组最后一个位置
            right = (mid + i < size) ? (mid + i) : (size - 1);

			//smallestSum += merge(arr, left, mid, right);
			reversePairCount += merge(arr, left, mid, right);
        }
    }

	printf("最小数组和:%d\n", smallestSum);
	printf("数组中的逆序对个数:%d\n", reversePairCount);
}


// 递归实现的归并排序(自顶向下)
void MergeSort::sortRecursion(int arr[], uint left, uint right)
{
	// 当待排序的序列长度为1时，递归结束, 开始回溯进行merge操作
	if (!arr || left == right)
		return;

	uint mid = (left + right) / 2;

	// 左边子数组递归处理
	sortRecursion(arr, left, mid);
	// 右边子数组递归处理
	sortRecursion(arr, mid + 1, right);

	// 归并处理
	merge(arr, left, mid, right);
}


int main_ms(int argc, char* argv[])
{
    //int arr[12] = { 4, 3, 2, 1, 0, 9, 8, 7, 4, 2, -1, 2 };
	//int arr[6] = { 1, 3, 5, 2, 4, 6 };
	int arr[8] = { 1,2,3,4,5,6,7,0 };
    int size = sizeof(arr) / sizeof(arr[0]);
	MergeSort st;

	printf("排序前:");
    printArr(arr, size);
    st.sort(arr, size);
	//st.sortRecursion(arr, 0, size - 1);
	printf("排序后:");
	printArr(arr, size);

    return 0;
}

