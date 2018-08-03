#include "SortMerge.h"


SortMerge::SortMerge()
{
}


SortMerge::~SortMerge()
{
}


/*
0  1  2  3  4  5  6  7  8  9
----------------------------
4  3  2  1  0  9  8  7  4  2
L           M              R
left = 0, mid = 4, right = 9, size = 10
arr[left...mid]和arr[mid+1...right]归并排序
*/
void SortMerge::merge(int arr[], uint left, uint mid, uint right)
{
    uint i = left;
    uint j = mid + 1;
    uint len = right - left + 1;
    uint tmpIndex = 0;
    int * tmpArr = new int[len];

    while (i <= mid && j <= right)
    {
        // 使用等于包含当前位置, 保证排序稳定性
        if (arr[i] <= arr[j])
            tmpArr[tmpIndex++] = arr[i++];
        else
            tmpArr[tmpIndex++] = arr[j++];
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
void SortMerge::sort(int arr[], uint size)
{
    uint left = 0;
    uint mid = 0;
    uint right = 0;
    
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

            merge(arr, left, mid, right);
        }
    }
}


int main(int argc, char* argv[])
{
    int arr[12] = { 4, 3, 2, 1, 0, 9, 8, 7, 4, 2, -1, 2 };
    int size = sizeof(arr) / sizeof(arr[0]);
    SortMerge st;

    printArr(arr, size);
    st.sort(arr, size);
    printArr(arr, size);

    return 0;
}

