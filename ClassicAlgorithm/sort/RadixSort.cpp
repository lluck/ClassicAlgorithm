#include <string.h>
#include "RadixSort.h"


RadixSort::RadixSort()
{
}


RadixSort::~RadixSort()
{
}


/*
基数排序(Radix Sort)是桶排序的扩展，它的基本思想是：将整数按位数切割成不同的数字，然后按每个位数分别比较。
具体做法是：将所有待比较数值统一为同样的数位长度，数位较短的数前面补零。然后，从最低位开始，依次进行一次排序。
这样从最低位排序一直到最高位排序完成以后, 数列就变成一个有序序列。

[桶式排序/计数排序]不再是一种基于比较的排序方法，它是一种比较巧妙的排序方式，但这种排序方式需要待排序的序列满足以下两个特征：
    1.待排序列所有的值处于一个可枚举的范围之类；
    2.待排序列所在的这个可枚举的范围不应该太大，否则排序开销太大。

基数排序，说白了就是进行多次的桶式排序。
基数排序已经不再是一种常规的排序方式，它更多地像一种排序方法的应用，基数排序必须依赖于另外的排序方法。
基数排序的总体思路就是将待排序数据拆分成多个关键字进行排序，也就是说，基数排序的实质是多关键字排序。
多关键字排序的思路是将待排数据里德排序关键字拆分成多个排序关键字；第1个排序关键字，第2个排序关键字，第3个排序关键字......
然后，根据子关键字对待排序数据进行排序。
多关键字排序时有两种解决方案：
    1.最高位优先法（MSD）(Most Significant Digit first)
    2.最低位优先法（LSD）(Least Significant Digit first)

算法执行步骤：
    (1)遍历序列找出最大的数(为的是确定最大的数是几位数)；
    (2)开辟一个与数组大小相同的临时数组tmp；
    (3)用一个count数组统计原数组中某一位(从低位向高位统计)相同的数据出现的次数；
    (4)用一个start数组计算原数组中某一位(从最低位向最高位计算)相同数据出现的位置；
    (5)将桶中数据从小到大用tmp数组收集起来；
    (6)重复(3)(4)(5)直到所有位都被统计并计算过，用tmp收集起来；
    (7)将tmp数组拷回到原数组中；
*/

// LSD——从低位向高位排
// 时间复杂度
// 平均情况:O(d * (n + r))
// 最坏情况:O(d * (n + r))
// 最好情况:O(d * (n + r))
// 空间复杂度
// O(n + r)
// 稳定性:稳定
// 其中，d 为位数，r 为基数，n 为原数组个数。 
// 在基数排序中，因为没有比较操作，所以在复杂度上，最好的情况与最坏的情况在时间上是一致的，均为 O(d * (n + r))。

void RadixSort::sort(int arr[], uint size)
{
    if (!arr || size < 2)
        return;

    // 取最大值
    int maxValue = max(arr, size);

    // LSD——从低位向高位排
    for (int pow = 1; maxValue / pow > 0; pow *= 10)
    {
        // pow=1 10 100 1000, 分别表示从个位、十位、百位排序
        this->countSort(arr, size, pow);
    }
}


void RadixSort::countSort(int arr[], uint size, int pow)
{
    const int sampleCount = 10;

    // 将数据出现的次数存储在buckets[]中, 初始化数量都设置为0
    int buckets[sampleCount];
    for (uint i = 0; i < sampleCount; ++i)
        buckets[i] = 0;

    // 将数据出现的次数存储在buckets[]中
    for (uint i = 0; i < size; ++i)
    {
        int value = arr[i] / pow % 10;
        ++buckets[value];
    }
    // 更改buckets[i]。目的是让更改后的buckets[i]的值，是该数据在output[]中的位置。
    for (uint i = 1; i < sampleCount; ++i)
        buckets[i] += buckets[i - 1];

    // 存储"被排序数据"的临时数组
    int* result = new int[size];
    //初始化tmp数组
    memset(result, 0, size *sizeof(int));
    for (int i = size - 1; i >= 0; --i)
    {
        // 将数据存储到临时数组output[]中, 从后往前数, 保证排序稳定性
        int value = arr[i] / pow % 10;
        result[--buckets[value]] = arr[i];
    }

    // 将排序好的数据赋值给a[]
    for (uint i = 0; i < size; ++i)
        arr[i] = result[i];

    // 释放临时数组
    delete [] result;
}


int main_rs(int argc, char* argv[])
{
    int arr[12] = { 4, 303, 202, 1, 0, 9999, 12345, 7, 4, 2, 120, 200 };
    int size = sizeof(arr) / sizeof(arr[0]);
    RadixSort st;

    printArr(arr, size);
    st.sort(arr, size);
    printArr(arr, size);

    return 0;
}
