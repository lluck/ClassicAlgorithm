#include "CountingSort.h"



CountingSort::CountingSort()
{
}


CountingSort::~CountingSort()
{
}


/*
计数排序用到一个额外的计数数组C，根据数组C来将原数组A中的元素排到正确的位置。
通俗地理解，例如有10个年龄不同的人，假如统计出有8个人的年龄不比小明大（即小于等于小明的年龄，这里也包括了小明），
那么小明的年龄就排在第8位，通过这种思想可以确定每个人的位置，也就排好了序。
当然，年龄一样时需要特殊处理（保证稳定性）：通过反向填充目标数组，填充完毕后将对应的数字统计递减，可以确保计数排序的稳定性。

计数排序的步骤如下：
    1.统计数组A中每个值A[i]出现的次数，存入C[A[i]]
    2.从前向后，使数组C中的每个值等于其与前一项相加，这样数组C[A[i]]就变成了代表数组A中小于等于A[i]的元素个数
    3.反向填充目标数组B：将数组元素A[i]放在数组B的第C[A[i]]个位置（下标为C[A[i]] - 1），每放一个元素就将C[A[i]]递减

计数排序的时间复杂度和空间复杂度与数组A的数据范围（A中元素的最大值与最小值的差加上1）有关，因此对于数据范围很大的数组，
计数排序需要大量时间和内存。
例如：对0到99之间的数字进行排序，计数排序是最好的算法，然而计数排序并不适合按字母顺序排序人名，将计数排序用在基数排序算法中，
能够更有效的排序数据范围很大的数组。
*/

// 分类 ------------ 内部非比较排序
// 数据结构 --------- 数组
// 最差时间复杂度 ---- O(n + k)
// 最优时间复杂度 ---- O(n + k)
// 平均时间复杂度 ---- O(n + k)
// 所需辅助空间 ------ O(n + k)
// 稳定性 ----------- 稳定
// n:排序数组长度, k:基数个数, 为100，排序[0,99]内的整数

void CountingSort::sort(int arr[], uint size)
{
    // 基数为100，排序[0,99]内的整数
    const uint sampleNum = 100;
    // 计数数组
    int sampleArray[sampleNum];

    // 初始化，将数组C中的元素置0(此步骤可省略，整型数组元素默认值为0)
    for (uint i = 0; i < sampleNum; ++i)
        sampleArray[i] = 0;
 
    // 使C[i]保存着等于i的元素个数
    for (uint i = 0; i < size; ++i)
        ++sampleArray[arr[i]];

    // 使C[i]保存着小于等于i的元素个数，排序后元素i就放在第C[i]个输出位置上
    for (uint i = 1; i < size; ++i)
    {
        sampleArray[i] += sampleArray[i - 1];
    }

    // 分配临时空间,长度为n，用来暂存中间数据
    int* arrB = new int[size];

    // 从后向前扫描保证计数排序的稳定性(重复元素相对次序不变)
    for (int i = size - 1; i >= 0; --i)
    {
        // 把每个元素A[i]放到它在输出数组B中的正确位置上
        // 当再遇到重复元素时会被放在当前元素的前一个位置上保证计数排序的稳定性
        arrB[--sampleArray[arr[i]]] = arr[i];
    }

    // 把临时空间B中的数据拷贝回A--原始数组arr
    for (uint i = 0; i < size; ++i)
        arr[i] = arrB[i];

    // 释放临时空间
    delete[] arrB;
}


int main_cs(int argc, char* argv[])
{
    int arr[13] = { 4, 3, 2, 1, 0, 9, 8, 7, 4, 2, 3, 2, 1 };
    //int arr[9] = { 5, 2, 9, 4, 7, 6, 1, 3, 8 };
    int size = sizeof(arr) / sizeof(arr[0]);
    CountingSort st;

    printf("排序前:\n");
    printArr(arr, size);
    st.sort(arr, size);
    printf("排序后:\n");
    printArr(arr, size);

    return 0;
}