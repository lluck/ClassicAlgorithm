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
arr[left...mid]��arr[mid+1...right]�鲢����
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
        // ʹ�õ��ڰ�����ǰλ��, ��֤�����ȶ���
        if (arr[i] <= arr[j])
            tmpArr[tmpIndex++] = arr[i++];
        else
            tmpArr[tmpIndex++] = arr[j++];
    }

    // �������ʣ�ಿ�ִ���
    for (; i <= mid; ++i)
        tmpArr[tmpIndex++] = arr[i];
    // �ұ�����ʣ�ಿ�ִ���
    for (; j <= right; ++j)
        tmpArr[tmpIndex++] = arr[j];

    // ����д��ԭʼ����
    for (i = 0; i < len; ++i)
        arr[left + i] = tmpArr[i];
}


/*
0  1  2  3  4  5  6  7  8  9 10
-------------------------------
4  3  2  1  0  9  8  7  4  2  0
LM R  LM R  LM R  LM R  LM R       i = 1, ÿ�����鳤��Ϊ1, ÿ�ι鲢�������鳤�� = 2
L  M     R  L  M     R             i = 2, ÿ�����鳤��Ϊ2, ÿ�ι鲢�������鳤�� = 4
L        M           R             i = 4, ÿ�����鳤��Ϊ4, ÿ�ι鲢�������鳤�� = 8
LM                   M        R    i = 8, ÿ�����鳤��Ϊ8, ÿ�ι鲢�������鳤�� = 16
left = 0, mid = 0, right = 1, size = 2
left = 0, mid = 1, right = 3, size = 4
arr[left...mid]��arr[mid+1...right]�鲢����
*/
void SortMerge::sort(int arr[], uint size)
{
    uint left = 0;
    uint mid = 0;
    uint right = 0;
    
    // ���ѭ��ʱ�临�Ӷ�log2N
    for (uint i = 1; i < size; i *= 2)
    {
        left = 0;
        right = 0;

        // �ڴ�ѭ��ʱ�临�Ӷ�N
        for (int j = 0; right < size - 1; j += 2)
        {
            // ָ����������ʼλ��
            left = i * j;
            // ��ʼλ��+���鳤��
            mid = left + i - 1;
            // �ұ����黹�㹻һ�����鳤��, ʹ��һ������λ��, ����ʹ���������һ��λ��
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

