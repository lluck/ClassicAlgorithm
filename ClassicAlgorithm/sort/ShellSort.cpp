#include "ShellSort.h"



ShellSort::ShellSort()
{
}


ShellSort::~ShellSort()
{
}


/*
希尔排序，也叫递减增量排序，是插入排序的一种更高效的改进版本。希尔排序是不稳定的排序算法。
希尔排序是基于插入排序的以下两点性质而提出改进方法的：
    1.插入排序在对几乎已经排好序的数据操作时，效率高，即可以达到线性排序的效率
    2.但插入排序一般来说是低效的，因为插入排序每次只能将数据移动一位
  　　
希尔排序通过将比较的全部元素分为几个区域来提升插入排序的性能。这样可以让一个元素可以一次性地朝最终位置前进一大步。
然后算法再取越来越小的步长进行排序，算法的最后一步就是普通的插入排序，但是到了这步，
需排序的数据几乎是已排好的了（此时插入排序较快）。
假设有一个很小的数据在一个已按升序排好序的数组的末端。如果用复杂度为O(n^2)的排序（冒泡排序或直接插入排序），
可能会进行n次的比较和交换才能将该数据移至正确位置。
而希尔排序会用较大的步长移动数据，所以小数据只需进行少数比较和交换即可到正确位置。
*/

// 分类 -------------- 内部比较排序
// 数据结构 ---------- 数组
// 最差时间复杂度 ---- 根据步长序列的不同而不同。已知最好的为O(n(logn)^2)
// 最优时间复杂度 ---- O(n)
// 平均时间复杂度 ---- 根据步长序列的不同而不同。
// 所需辅助空间 ------ O(1)
// 稳定性 ------------ 不稳定


// 交叉处理各分组数据
void ShellSort::sort(int arr[], uint size)
{
    if (!arr || size < 2)
        return;

    // 增量gap，并逐步减半缩小增量
    for (int gap = size / 2; gap > 0; gap /= 2)
    {
        //从第gap个元素，逐个对其所在组进行直接插入排序操作
        for (uint i = gap; i < size; ++i)
        {
            int j = i;

            // 依次处理gap前面的各分组数据:如果前面包含若干分组数据的话
            while (j - gap >= 0 && arr[j - gap] > arr[j])
            {
                swap(arr[j - gap], arr[j]);
                j -= gap;
            }
        }
    }
}


int main_shst(int argc, char* argv[])
{
    int arr[13] = { 4, 3, 2, 1, 0, 9, 8, 7, 4, 2, -1, 2, 1 };
    //int arr[9] = { 5, 2, 9, 4, 7, 6, 1, 3, 8 };
    int size = sizeof(arr) / sizeof(arr[0]);
    ShellSort st;

    printf("排序前:\n");
    printArr(arr, size);
    st.sort(arr, size);
    printf("排序后:\n");
    printArr(arr, size);

    return 0;
}