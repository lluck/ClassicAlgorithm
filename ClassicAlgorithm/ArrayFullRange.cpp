#include "ArrayFullRange.h"


ArrayFullRange::ArrayFullRange()
{
}


ArrayFullRange::~ArrayFullRange()
{
}


void ArrayFullRange::fullRange(char arr[], uint size)
{
    if (!arr || size < 2)
        return;

    fullRangeRecursion(arr, 0, size);
}



// pos表示当前选取到第几个数, len表示共有多少数.
void ArrayFullRange::fullRangeRecursion(char arr[], uint pos, uint len)
{
    // 第i个数分别与它后面的数字交换就能得到新的排列
    for (uint i = pos; i < len; ++i)
    {
        swap(arr[pos], arr[i]);
       
        if (pos + 1 == len)
        {
            printf("1 >>in  pos=%d, i=%d, len=%d, arr=%s\n", pos, i, len, arr);
            printArr(arr, len);
            printf("1 <<out pos=%d, i=%d, len=%d, arr=%s\n", pos, i, len, arr);
        }
        else
        {
            printf("2 >>in  pos=%d, i=%d, len=%d, arr=%s\n", pos, i, len, arr);
            fullRangeRecursion(arr, pos + 1, len);
            printf("2 <<out pos=%d, i=%d, len=%d, arr=%s\n", pos, i, len, arr);
        }
       
        swap(arr[i], arr[pos]);
    }
}


int main(int argc, char* argv[])
{
    char arr[] = "abc";
    int size = strlen(arr);
    ArrayFullRange st;

    st.fullRange(arr, size);

    return 0;
}

