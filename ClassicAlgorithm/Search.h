#pragma once
#include "Base.h"

class Search
{
public:
    Search();
    virtual ~Search();

    // 记录算法循环次数, 间接计算时间复杂度
    void setLoopCount(ullint count = 0)
    {
        this->loopCount = count;
    }
    ullint getLoopCount()
    {
        return this->loopCount;
    }
    void printLoopCount()
    {
        printf("算法循环次数:%lld\n", this->loopCount);
    }

    // 顺序查找, 时间复杂度为O(N)
    int sequenceSearch(int arr[], uint size, int value);

    // 二分查找(折半查找), 不递归, 要求排序, 时间复杂度为O(log2N)
    int binarySearch(int arr[], uint size, int value);
    // 二分查找(折半查找), 递归, 要求排序, 时间复杂度为O(log2N)
    int binarySearchRecursive(int arr[], uint size, int value, int low, int high);

    // 插值查找, 不递归, 要求排序, 时间复杂度为O(log2N)
    int insertSearch(int arr[], uint size, int value);
    // 插值查找, 递归, 要求排序, 时间复杂度为O(log2N)
    int insertSearchRecursive(int arr[], uint size, int value, int low, int high);



private:
    ullint loopCount;
};

