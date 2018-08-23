#include "Search.h"
#include "RadixSort.h"

Search::Search()
{
    loopCount = 0;
}


Search::~Search()
{
}


/*
1. 顺序查找
　　说明：顺序查找适合于存储结构为顺序存储或链接存储的线性表。
  　基本思想：顺序查找也称为线形查找，属于无序查找算法。从数据结构线形表的一端开始，顺序扫描，依次将扫描到的结点关键字与给定值k相比较，
              若相等则表示查找成功；若扫描结束仍没有找到关键字等于k的结点，表示查找失败。
    复杂度分析：　
      　　查找成功时的平均查找长度为：（假设每个数据元素的概率相等） ASL = 1/n(1+2+3+…+n) = (n+1)/2 ;
        　当查找不成功时，需要n+1次比较，时间复杂度为O(n);
          所以，顺序查找的时间复杂度为O(n)。
*/
// 顺序查找, 时间复杂度为O(N), 不要求排序
int Search::sequenceSearch(int arr[], uint size, int value)
{
    for (int i = 0; i < size; ++i)
    {
        ++loopCount;
        if (arr[i] == value)
            return i;
    }
    return -1;
}



/*
2. 二分查找
    说明：元素必须是有序的，如果是无序的则要先进行排序操作。
　　基本思想：也称为是折半查找，属于有序查找算法。用给定值k先与中间结点的关键字比较，中间结点把线形表分成两个子表，若相等则查找成功；
              若不相等，再根据k与该中间结点关键字的比较结果确定下一步查找哪个子表，这样递归进行，直到查找到或查找结束发现表中没有这样的结点。
    复杂度分析：最坏情况下，关键词比较次数为log2(n+1)，且期望时间复杂度为O(log2n)；
    注：折半查找的前提条件是需要有序表顺序存储，对于静态查找表，一次排序后不再变化，折半查找能得到不错的效率。
    但对于需要频繁执行插入或删除操作的数据集来说，维护有序的排序会带来不小的工作量，那就不建议使用。——《大话数据结构》
*/
// 二分查找(折半查找), 不递归, 要求排序, 时间复杂度为O(log2N)
int Search::binarySearch(int arr[], uint size, int value)
{
    int low = 0;
    int high = size - 1;
    int mid = -1;

    while (low <= high)
    {
        ++loopCount;
        mid = (low + high) / 2;
        if (arr[mid] == value)
            return mid;
        else if (arr[mid] < value)
            low = mid + 1;
        else
            high = mid - 1;
    }

    return -1;
}


// 二分查找(折半查找), 递归, 要求排序, 时间复杂度为O(log2N)
int Search::binarySearchRecursive(int arr[], uint size, int value, int low, int high)
{
    if (!arr || low > high)
        return - 1;

    int mid = (low + high) / 2;
    mid = low + (high - low) / 2;
    ++loopCount;

    if (arr[mid] == value)
        return mid;
    else if (arr[mid] < value)
        return binarySearchRecursive(arr, size, value, mid + 1, high);
    else
        return binarySearchRecursive(arr, size, value, low, mid - 1);
}


/*
3. 插值查找
　　在介绍插值查找之前，首先考虑一个新问题，为什么上述算法一定要是折半，而不是折四分之一或者折更多呢？
  　打个比方，在英文字典里面查“apple”，你下意识翻开字典是翻前面的书页还是后面的书页呢？如果再让你查“zoo”，你又怎么查？
    很显然，这里你绝对不会是从中间开始查起，而是有一定目的的往前或往后翻。
    同样的，比如要在取值范围1 ~ 10000 之间 100 个元素从小到大均匀分布的数组中查找5， 我们自然会考虑从数组下标较小的开始查找。
    经过以上分析，折半查找这种查找方式，不是自适应的（也就是说是傻瓜式的）。二分查找中查找点计算如下：
        mid=(low+high)/2, 即mid=low+1/2*(high-low);
    通过类比，我们可以将查找的点改进为如下：
        mid=low+(key-a[low])/(a[high]-a[low])*(high-low)，
    也就是将上述的比例参数1/2改进为自适应的，根据关键字在整个有序表中所处的位置，让mid值的变化更靠近关键字key，
    这样也就间接地减少了比较次数。
    
    基本思想：基于二分查找算法，将查找点的选择改进为自适应选择，可以提高查找效率。当然，差值查找也属于有序查找。
    注：对于表长较大，而关键字分布又比较均匀的查找表来说，插值查找算法的平均性能比折半查找要好的多。
    反之，数组中如果分布非常不均匀，那么插值查找未必是很合适的选择。
    复杂度分析：查找成功或者失败的时间复杂度均为O(log2(log2n))。
*/
// 插值查找, 不递归, 要求排序, 时间复杂度为O(log2N)
int Search::insertSearch(int arr[], uint size, int value)
{
    int low = 0;
    int high = size - 1;
    int mid = 0;

    while (low <= high)
    {
        ++loopCount;
        // mid = low + (high - low) / 2;
        mid = low + (value - arr[low]) / (arr[high] - arr[low] + 0.01) * (high - low);

        if (arr[mid] == value)
            return mid;
        else if (arr[mid] < value)
            low = mid + 1;
        else
            high = mid - 1;
    }

    return -1;
}


// 插值查找, 递归, 要求排序, 时间复杂度为O(log2N)
int Search::insertSearchRecursive(int arr[], uint size, int value, int low, int high)
{
    if (!arr || low > high)
        return -1;

    int mid = low + (value - arr[low]) / (arr[high] - arr[low] + 0.01) * (high - low);
    ++loopCount;

    if (arr[mid] == value)
        return mid;
    else if (arr[mid] < value)
        return insertSearchRecursive(arr, size, value, mid + 1, high);
    else
        return insertSearchRecursive(arr, size, value, low, mid - 1);
}


int main_sech(void)
{
    int arr[12] = { 4, 3, 6, 1, 2, 9, 8, 7, 5, 12, 11, 10};
    //int arr[1] = { 8 };
    int size = sizeof(arr) / sizeof(arr[0]);

    printArr(arr, size);

    int value = 8;
    int index = -1;
    Search sh;

    index = sh.sequenceSearch(arr, size, value);
    sh.printLoopCount();

    RadixSort st;
    st.sort(arr, size);
    printArr(arr, size);

    sh.setLoopCount();
    index = sh.binarySearch(arr, size, value);
    sh.printLoopCount();
    printf("查询:[%d], 结果:[%d]\n", value, index);
    
    sh.setLoopCount();
    index = sh.binarySearchRecursive(arr, size, value, 0, size - 1);
    sh.printLoopCount();
    printf("查询:[%d], 结果:[%d]\n", value, index);
    
    sh.setLoopCount();
    index = sh.insertSearch(arr, size, value);
    sh.printLoopCount();
    printf("查询:[%d], 结果:[%d]\n", value, index);

    sh.setLoopCount();
    index = sh.insertSearchRecursive(arr, size, value, 0, size - 1);
    sh.printLoopCount();
    printf("查询:[%d], 结果:[%d]\n", value, index);

    return 0;
}
