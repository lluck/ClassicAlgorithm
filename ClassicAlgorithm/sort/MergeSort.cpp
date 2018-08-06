#include "MergeSort.h"


MergeSort::MergeSort()
{
}


MergeSort::~MergeSort()
{
}


/*

�鲢�����Ǵ����ڹ鲢�����ϵ�һ����Ч�������㷨��Ч��ΪO(nlogn)��1945���ɷ롤ŵ�����״������
�鲢�����ʵ�ַ�Ϊ�ݹ�ʵ����ǵݹ�(����)ʵ�֡�
�ݹ�ʵ�ֵĹ鲢�������㷨����з��β��Եĵ���Ӧ�ã����ǽ�һ��������ָ��С����ֱ�����Ȼ��������С����Ĵ���������������⡣
�ǵݹ�(����)ʵ�ֵĹ鲢�������Ƚ����������鲢��Ȼ�����Ĺ鲢��Ȼ���ǰ˰˹鲢��һֱ��ȥֱ���鲢���������顣

�鲢�����㷨��Ҫ�����鲢(Merge)�������鲢����ָ���ǽ������Ѿ���������кϲ���һ�����еĲ������鲢�����������£�
	1.����ռ䣬ʹ���СΪ�����Ѿ���������֮�ͣ��ÿռ�������źϲ��������
	2.�趨����ָ�룬���λ�÷ֱ�Ϊ�����Ѿ��������е���ʼλ��
	3.�Ƚ�����ָ����ָ���Ԫ�أ�ѡ�����С��Ԫ�ط��뵽�ϲ��ռ䣬���ƶ�ָ�뵽��һλ��
	4.�ظ�����3ֱ��ĳһָ�뵽������β
	5.����һ����ʣ�µ�����Ԫ��ֱ�Ӹ��Ƶ��ϲ�����β
*/

// ���� -------------- �ڲ��Ƚ�����
// ���ݽṹ ---------- ����
// ���ʱ�临�Ӷ� ---- O(nlogn)
// ����ʱ�临�Ӷ� ---- O(nlogn)
// ƽ��ʱ�临�Ӷ� ---- O(nlogn)
// ���踨���ռ� ------ O(n)
// �ȶ��� ------------ �ȶ�


/*
0  1  2  3  4  5  6  7  8  9
----------------------------
4  3  2  1  0  9  8  7  4  2
L           M              R
left = 0, mid = 4, right = 9, size = 10
arr[left...mid]��arr[mid+1...right]�鲢����

-----------------------------------------------------------------------------------------------------------------
����С�ͣ������ͣ�:
����С�͵Ķ������£����磬����s=[1,3,5,2,4,6]
��s[0]�����С�ڻ����s[0]�����ĺ�Ϊ0
��s[1]�����С�ڻ����s[1]�����ĺ�Ϊ1
��s[2]�����С�ڻ����s[2]�����ĺ�Ϊ1+3=4
��s[3]�����С�ڻ����s[3]�����ĺ�Ϊ1
��s[4]�����С�ڻ����s[4]�����ĺ�Ϊ1+3+2=6
��s[5]�����С�ڻ����s[5]�����ĺ�Ϊ1+3+5+2+4=15
����s��С��Ϊ0+1+4+1+6+15=27
����һ������s��ʵ�ֺ�������s��С�͡�

����ѭ��������⣬ʱ�临�Ӷ�O(n^2), ���ù鲢�����ڶ��������������merge��ͬʱ���ۼ�����С�ͣ�ʱ�临�Ӷ�O(nlogn)

-----------------------------------------------------------------------------------------------------------------
�����е�����Ը���:
��һ�������������������������飬��ǰ��һ�����ں���һ�����֣����������������һ������ԡ�
����������
	[1,2,3,4,5,6,7,0], 8    ���أ�7

*/
int MergeSort::merge(int arr[], uint left, uint mid, uint right)
{
    uint i = left;
    uint j = mid + 1;
    uint len = right - left + 1;
    uint tmpIndex = 0;
    int * tmpArr = new int[len];

	int smallestSum = 0;
	int reversePairCount = 0;

    while (i <= mid && j <= right)
    {
        // ʹ�õ��ڰ�����ǰλ��, ��֤�����ȶ���
		if (arr[i] <= arr[j])
		{
			// ��ǰһ������Ԫ��С�ڻ���ں�һ������Ԫ��ʱ���ۼ�С��
			// s[i] <= s[j] �ȼ��� s[i] <= s[j]...s[right]
			// ��Ϊs[j]...s[right]�Ѿ��ź�����, ����s[i]С��s[j]...s[right]��ÿһ����
			smallestSum += arr[i] * (right - j + 1);

			tmpArr[tmpIndex++] = arr[i++];
		}
		else
		{
			// ��ǰһ������Ԫ�ش��ں�һ������Ԫ��ʱ���ۼ������
			// s[i] > s[j] �ȼ��� s[i]...s[mid] > s[j]
			// ��Ϊs[i]...s[mid]�Ѿ��ź�����, ����s[i]...s[mid]��ÿһ��������s[j]
			reversePairCount += (mid - i + 1);

			tmpArr[tmpIndex++] = arr[j++];
		}
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

	//return smallestSum;
	return reversePairCount;
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
// �ǵݹ�(����)ʵ�ֵĹ鲢����(�Ե�����)
void MergeSort::sort(int arr[], uint size)
{
	if (!arr || size < 2)
		return;

    uint left = 0;
    uint mid = 0;
    uint right = 0;

	int smallestSum = 0;			 // ��С�����
	int reversePairCount = 0;		// �����е�����Ը���
    
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

			//smallestSum += merge(arr, left, mid, right);
			reversePairCount += merge(arr, left, mid, right);
        }
    }

	printf("��С�����:%d\n", smallestSum);
	printf("�����е�����Ը���:%d\n", reversePairCount);
}


// �ݹ�ʵ�ֵĹ鲢����(�Զ�����)
void MergeSort::sortRecursion(int arr[], uint left, uint right)
{
	// ������������г���Ϊ1ʱ���ݹ����, ��ʼ���ݽ���merge����
	if (!arr || left == right)
		return;

	uint mid = (left + right) / 2;

	// ���������ݹ鴦��
	sortRecursion(arr, left, mid);
	// �ұ�������ݹ鴦��
	sortRecursion(arr, mid + 1, right);

	// �鲢����
	merge(arr, left, mid, right);
}


int main_ms(int argc, char* argv[])
{
    //int arr[12] = { 4, 3, 2, 1, 0, 9, 8, 7, 4, 2, -1, 2 };
	//int arr[6] = { 1, 3, 5, 2, 4, 6 };
	int arr[8] = { 1,2,3,4,5,6,7,0 };
    int size = sizeof(arr) / sizeof(arr[0]);
	MergeSort st;

	printf("����ǰ:");
    printArr(arr, size);
    st.sort(arr, size);
	//st.sortRecursion(arr, 0, size - 1);
	printf("�����:");
	printArr(arr, size);

    return 0;
}

