#include "InsertionSortDichotomy.h"



InsertionSortDichotomy::InsertionSortDichotomy()
{
}


InsertionSortDichotomy::~InsertionSortDichotomy()
{
}

/*
对于插入排序，如果比较操作的代价比交换操作大的话，可以采用二分查找法来减少比较操作的次数, 称为二分插入排序
当n较大时，二分插入排序的比较次数比直接插入排序的最差情况好得多，但比直接插入排序的最好情况要差，
所当以元素初始序列已经接近升序时，直接插入排序比二分插入排序比较次数少。
二分插入排序元素移动次数与直接插入排序相同，依赖于元素初始序列。
*/

// 分类 -------------- 内部比较排序
// 数据结构 ---------- 数组
// 最差时间复杂度 ---- O(n^2)
// 最优时间复杂度 ---- O(nlogn)
// 平均时间复杂度 ---- O(n^2)
// 所需辅助空间 ------ O(1)
// 稳定性 ------------ 稳定

void InsertionSortDichotomy::sort(int arr[], uint size)
{
    if (!arr || size < 2)
        return;

    // 二分查找, 使用int, uint减至0以下时, 数值错误
    int left = 0;
    int mid = 0;
    int right = 0;

    int curVal;

    for (uint i = 1; i < size; ++i)
    {
        // 右手抓到一张扑克牌
        curVal = arr[i];

        // 拿在左手上的牌总是排序好的，所以可以用二分法查找
        left = 0;
        right = i - 1;

        // 采用二分法定位新牌的位置
        while (left <= right)
        {
            mid = (left + right) / 2;

            if (arr[mid] > curVal)
            {
                // 从左边子数组中继续查找
                right = mid - 1;
            }
            else
            {
                // 从右边子数组中继续查找
                left = mid + 1;
            }
        }
        // end of while loop

        // 将欲插入新牌位置右边的牌整体向右移动一个单位
        for (int j = i - 1; j >= left; --j)
        {
            arr[j + 1] = arr[j];
        }

        // 将抓到的牌插入手牌
        arr[left] = curVal;
    }
}


int main_isd(int argc, char* argv[])
{
    int arr[12] = { 4, 3, 2, 1, 0, 9, 8, 7, 4, 2, -1, 2 };
    //int arr[9] = { 5, 2, 9, 4, 7, 6, 1, 3, 8 };
    int size = sizeof(arr) / sizeof(arr[0]);
    InsertionSortDichotomy st;

    printf("排序前:\n");
    printArr(arr, size);
    st.sort(arr, size);
    printf("排序后:\n");
    printArr(arr, size);

    return 0;
}