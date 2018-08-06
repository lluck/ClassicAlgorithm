#include "InsertionSortDichotomy.h"



InsertionSortDichotomy::InsertionSortDichotomy()
{
}


InsertionSortDichotomy::~InsertionSortDichotomy()
{
}

/*
���ڲ�����������Ƚϲ����Ĵ��۱Ƚ���������Ļ������Բ��ö��ֲ��ҷ������ٱȽϲ����Ĵ���, ��Ϊ���ֲ�������
��n�ϴ�ʱ�����ֲ�������ıȽϴ�����ֱ�Ӳ���������������õö࣬����ֱ�Ӳ��������������Ҫ�
������Ԫ�س�ʼ�����Ѿ��ӽ�����ʱ��ֱ�Ӳ�������ȶ��ֲ�������Ƚϴ����١�
���ֲ�������Ԫ���ƶ�������ֱ�Ӳ���������ͬ��������Ԫ�س�ʼ���С�
*/

// ���� -------------- �ڲ��Ƚ�����
// ���ݽṹ ---------- ����
// ���ʱ�临�Ӷ� ---- O(n^2)
// ����ʱ�临�Ӷ� ---- O(nlogn)
// ƽ��ʱ�临�Ӷ� ---- O(n^2)
// ���踨���ռ� ------ O(1)
// �ȶ��� ------------ �ȶ�

void InsertionSortDichotomy::sort(int arr[], uint size)
{
    if (!arr || size < 2)
        return;

    // ���ֲ���, ʹ��int, uint����0����ʱ, ��ֵ����
    int left = 0;
    int mid = 0;
    int right = 0;

    int curVal;

    for (uint i = 1; i < size; ++i)
    {
        // ����ץ��һ���˿���
        curVal = arr[i];

        // ���������ϵ�����������õģ����Կ����ö��ַ�����
        left = 0;
        right = i - 1;

        // ���ö��ַ���λ���Ƶ�λ��
        while (left <= right)
        {
            mid = (left + right) / 2;

            if (arr[mid] > curVal)
            {
                // ������������м�������
                right = mid - 1;
            }
            else
            {
                // ���ұ��������м�������
                left = mid + 1;
            }
        }
        // end of while loop

        // ������������λ���ұߵ������������ƶ�һ����λ
        for (int j = i - 1; j >= left; --j)
        {
            arr[j + 1] = arr[j];
        }

        // ��ץ�����Ʋ�������
        arr[left] = curVal;
    }
}


int main_isd(int argc, char* argv[])
{
    int arr[12] = { 4, 3, 2, 1, 0, 9, 8, 7, 4, 2, -1, 2 };
    //int arr[9] = { 5, 2, 9, 4, 7, 6, 1, 3, 8 };
    int size = sizeof(arr) / sizeof(arr[0]);
    InsertionSortDichotomy st;

    printf("����ǰ:\n");
    printArr(arr, size);
    st.sort(arr, size);
    printf("�����:\n");
    printArr(arr, size);

    return 0;
}