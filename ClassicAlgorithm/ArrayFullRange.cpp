#include "ArrayFullRange.h"


ArrayFullRange::ArrayFullRange()
{
}


ArrayFullRange::~ArrayFullRange()
{
}


/*
参考链接:https://www.cnblogs.com/nowornever-L/p/6008954.html

全排列就是从第一个数字起每个数分别与它后面的数字交换。
去重的全排列就是从第一个数字起每个数分别与它后面非重复出现的数字交换。就是第i个数与第j个数交换时，要求[i,j)中没有与第j个数相等的数。

1.全排列的定义和公式：
从n个数中选取m（m<=n）个数按照一定的顺序进行排成一个列，叫作从n个元素中取m个元素的一个排列。由排列的定义，显然不同的顺序是一个不同的排列。
从n个元素中取m个元素的所有排列的个数，称为排列数。从n个元素取出n个元素的一个排列，称为一个全排列。全排列的排列数公式为n!，通过乘法原理可以得到。

2.时间复杂度：
n个数（字符、对象）的全排列一共有n!种，所以全排列算法至少时间O(n!)的。如果要对全排列进行输出，那么输出的时间要O(n∗n!)，
因为每一个排列都有n个数据。所以实际上，全排列算法对大型的数据是无法处理的，而一般情况下也不会要求我们去遍历一个大型数据的全排列。

全排列的本质是一个DFS的过程
*/
void ArrayFullRange::fullRange(char arr[], uint size)
{
    if (!arr || size < 2)
        return;

    //fullRangeByRecursion(arr, 0, size);
    fullRangeByDictionary(arr, size);
}



// pos表示当前选取到第几个数, len表示共有多少数.
void ArrayFullRange::fullRangeByRecursion(char arr[], uint pos, uint len)
{
    // 第i个数分别与它后面的数字交换就能得到新的排列
    for (uint i = pos; i < len; ++i)
    {
        // 重复的值, 不再交换
        if (neddSwap(arr, pos, i))
        {
            swap(arr[pos], arr[i]);

            if (pos + 1 == len)
                printArr(arr, len);
            else
                fullRangeByRecursion(arr, pos + 1, len);

            swap(arr[i], arr[pos]);
        }
    }
}



//在arr数组中，[begin, end)中是否有数字与下标为end的数字相等
bool ArrayFullRange::neddSwap(char arr[], uint begin, uint end)
{
    for (uint i = begin; i < end; ++i)
    {
        if (arr[i] == arr[end])
            return false;
    }
    return true;
}


/*
* 基于逆序数的全排列输出
* 默认给定的是升序排列数组

使用字典序输出全排列的思路是，首先输出字典序最小的排列，然后输出字典序次小的排列，……，最后输出字典序最大的排列。
这里就涉及到一个问题，对于一个已知排列，如何求出其字典序中的下一个排列。这里给出算法。
    1.对于排列a[1...n]，找到所有满足a[k]<a[k+1](0<k<n-1)的k的最大值，如果这样的k不存在，则说明当前排列已经是a的所有排列中字典序最大者，所有排列输出完毕。
    2.在a[k+1...n]中，寻找满足这样条件的元素l，使得在所有a[l]>a[k]的元素中，a[l]取得最小值。也就是说a[l]>a[k]，但是小于所有其他大于a[k]的元素。
    3.交换a[l]与a[k].
    4.对于a[k+1...n]，反转该区间内元素的顺序。也就是说a[k+1]与a[n]交换，a[k+2]与a[n-1]交换，……，这样就得到了a[1...n]在字典序中的下一个排列。

*/
void ArrayFullRange::fullRangeByDictionary(char arr[], uint size)
{
    // 创建索引数组
    uint* indexArr = (uint*)malloc(sizeof(uint*) * size);

    // 索引数组初始化为默认索引值, 默认是升序排列数组
    for (uint i = 0; i < size; ++i)
        indexArr[i] = i;

    /*
    重复值处理:
        1.对原始数组计数统计
        2.然后依次输出计数后的数组:按顺序、个数, 依次输出
        3.输出的同时, 设置索引数组的值
    */
    const uint BUCKET_SIZE = 26;
    int* buckets = new int[BUCKET_SIZE];
    for (uint i = 0; i < BUCKET_SIZE; ++i)
        buckets[i] = 0;

    // 原始数组字符计数
    for (uint i = 0; i < size; ++i)
        ++buckets[arr[i] - 'a'];

    printf("--------------原数组,计数:\n");
    printArr(arr, size);
    printArr(buckets, BUCKET_SIZE);
    

    // 原始字符下标索引
    uint curArrIndex = 0;
    // 索引数组的下标索引
    uint curIndexArrIndex = 0;
    // 取2者最大值, 支持原始arr数组短长度, 而且包含a...z超出arr长度后的字母
    uint sizeVal = std::max(size, BUCKET_SIZE);
    for (uint i = 0; i < sizeVal; ++i)
    {
        uint bucketsSize = buckets[i];

        // 根据计数个数N, 输出N个原始数组的指定值, 同时设置索引数组的下标索引值
        while (buckets[i] > 0)
        {
            // 索引数组的下标索引值
            indexArr[curArrIndex] = curIndexArrIndex;

            // 输出原始数组的指定值
            arr[curArrIndex] = 'a' + i;
            // 待输出个数减1
            --buckets[i];
            // 原始数组下表增加
            ++curArrIndex;
        }

        // 索引数组的下标索引值, 每处理一个字符增加bucketsSize次
        curIndexArrIndex += bucketsSize;
    }

    printf("--------------计数调整后数组,计数:\n");
    printArr(arr, size);
    printArr(buckets, BUCKET_SIZE);
    printArr(indexArr, size);
    printf("--------------\n");

    // 使用do while循环, 先输出原始排列数值
    ullint totalCount = 0L;
    do
    {
        ++totalCount;

        // 还有下一个排列数值, 输出
        printArrByIndex(arr, size, indexArr);
        printArr(indexArr, size);
    }while (hasNext(indexArr, size));

    printf("排列组合数:totalCount=%lld\n", totalCount);

    // 释放索引数组内存
    free(indexArr);
    delete[] buckets;
}


// 是否还有下一个排列数组
bool ArrayFullRange::hasNext(uint arr[], uint size)
{
    // 从右边末尾第2个数值开始比较, 因为默认给定的是升序排列数组
    int ascPos = size - 2;

    // 如果是逆序继续往前查找, 查找第一个顺序位置, 直到数组全部元素都已经是逆序排列, 说明已经排列完成
    // 使用等于, 以支持相同字符的排列
    while (ascPos >= 0 && arr[ascPos] >= arr[ascPos + 1])
        --ascPos;

    // 数组中不存在顺序位置
    // 数组全部元素都已经是逆序排列, 说明已经排列完成
    //达到字典序最大值, 没有下一个排列值
    if (ascPos < 0)
        return false;

    // 从右边末尾第2个数值开始比较, 在ascPos右边[后边]查找大于ascPos值的最小值
    // 该值作为下一个排列中pos处的值, 通过交换, 填充到pos位置处, 而且这个值一定存在
    // 交换后, assPos右边[后边]一定是一个逆序排列的数组, 
    // 因为被交换的值是查找到的大于ascPos值的最小值, 而且交换前ascPos右边[后边]也是逆序排列的数组
    // if (descPos == INT_MAX)是必须的, 因为要满足条件arr[j] > arr[ascPos]时才能设置descPos的值
    int descPos = INT_MAX;
    for (int j = size - 1; j > ascPos; --j)
    {
        // 查找大于ascPos值的最小值
        if (arr[j] > arr[ascPos])
        {
            if (descPos == INT_MAX || arr[j] < arr[descPos])
                descPos = j;
        }
    }

    // 交换指定值
    swap(arr[ascPos], arr[descPos]);
    // 将数组中的元素翻转
    reverse(arr + ascPos + 1, size - ascPos - 1);
    return true;
}



int main_afg(int argc, char* argv[])
{
    char arr[] = "nncnn";
    int size = strlen(arr);

    /*reverse(arr, size);
    printArr(arr, size);*/

    ArrayFullRange st;

    st.fullRange(arr, size);
    

    return 0;
}