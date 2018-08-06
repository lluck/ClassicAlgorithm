#include <string.h>
#include "RadixSort.h"


RadixSort::RadixSort()
{
}


RadixSort::~RadixSort()
{
}


/*
��������(Radix Sort)��Ͱ�������չ�����Ļ���˼���ǣ���������λ���и�ɲ�ͬ�����֣�Ȼ��ÿ��λ���ֱ�Ƚϡ�
���������ǣ������д��Ƚ���ֵͳһΪͬ������λ���ȣ���λ�϶̵���ǰ�油�㡣Ȼ�󣬴����λ��ʼ�����ν���һ������
���������λ����һֱ�����λ��������Ժ�, ���оͱ��һ���������С�

[Ͱʽ����/��������]������һ�ֻ��ڱȽϵ����򷽷�������һ�ֱȽ����������ʽ������������ʽ��Ҫ�����������������������������
    1.�����������е�ֵ����һ����ö�ٵķ�Χ֮�ࣻ
    2.�����������ڵ������ö�ٵķ�Χ��Ӧ��̫�󣬷���������̫��

��������˵���˾��ǽ��ж�ε�Ͱʽ����
���������Ѿ�������һ�ֳ��������ʽ�����������һ�����򷽷���Ӧ�ã��������������������������򷽷���
�������������˼·���ǽ����������ݲ�ֳɶ���ؼ��ֽ�������Ҳ����˵�����������ʵ���Ƕ�ؼ�������
��ؼ��������˼·�ǽ����������������ؼ��ֲ�ֳɶ������ؼ��֣���1������ؼ��֣���2������ؼ��֣���3������ؼ���......
Ȼ�󣬸����ӹؼ��ֶԴ��������ݽ�������
��ؼ�������ʱ�����ֽ��������
    1.���λ���ȷ���MSD��(Most Significant Digit first)
    2.���λ���ȷ���LSD��(Least Significant Digit first)

�㷨ִ�в��裺
    (1)���������ҳ�������(Ϊ����ȷ���������Ǽ�λ��)��
    (2)����һ���������С��ͬ����ʱ����tmp��
    (3)��һ��count����ͳ��ԭ������ĳһλ(�ӵ�λ���λͳ��)��ͬ�����ݳ��ֵĴ�����
    (4)��һ��start�������ԭ������ĳһλ(�����λ�����λ����)��ͬ���ݳ��ֵ�λ�ã�
    (5)��Ͱ�����ݴ�С������tmp�����ռ�������
    (6)�ظ�(3)(4)(5)ֱ������λ����ͳ�Ʋ����������tmp�ռ�������
    (7)��tmp���鿽�ص�ԭ�����У�
*/

// LSD�����ӵ�λ���λ��
// ʱ�临�Ӷ�
// ƽ�����:O(d * (n + r))
// ����:O(d * (n + r))
// ������:O(d * (n + r))
// �ռ临�Ӷ�
// O(n + r)
// �ȶ���:�ȶ�
// ���У�d Ϊλ����r Ϊ������n Ϊԭ��������� 
// �ڻ��������У���Ϊû�бȽϲ����������ڸ��Ӷ��ϣ���õ��������������ʱ������һ�µģ���Ϊ O(d * (n + r))��

void RadixSort::sort(int arr[], uint size)
{
    if (!arr || size < 2)
        return;

    // ȡ���ֵ
    int maxValue = max(arr, size);

    // LSD�����ӵ�λ���λ��
    for (int pow = 1; maxValue / pow > 0; pow *= 10)
    {
        // pow=1 10 100 1000, �ֱ��ʾ�Ӹ�λ��ʮλ����λ����
        this->countSort(arr, size, pow);
    }
}


void RadixSort::countSort(int arr[], uint size, int pow)
{
    const int sampleCount = 10;

    // �����ݳ��ֵĴ����洢��buckets[]��, ��ʼ������������Ϊ0
    int buckets[sampleCount];
    for (uint i = 0; i < sampleCount; ++i)
        buckets[i] = 0;

    // �����ݳ��ֵĴ����洢��buckets[]��
    for (uint i = 0; i < size; ++i)
    {
        int value = arr[i] / pow % 10;
        ++buckets[value];
    }
    // ����buckets[i]��Ŀ�����ø��ĺ��buckets[i]��ֵ���Ǹ�������output[]�е�λ�á�
    for (uint i = 1; i < sampleCount; ++i)
        buckets[i] += buckets[i - 1];

    // �洢"����������"����ʱ����
    int* result = new int[size];
    //��ʼ��tmp����
    memset(result, 0, size *sizeof(int));
    for (int i = size - 1; i >= 0; --i)
    {
        // �����ݴ洢����ʱ����output[]��, �Ӻ���ǰ��, ��֤�����ȶ���
        int value = arr[i] / pow % 10;
        result[--buckets[value]] = arr[i];
    }

    // ������õ����ݸ�ֵ��a[]
    for (uint i = 0; i < size; ++i)
        arr[i] = result[i];

    // �ͷ���ʱ����
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