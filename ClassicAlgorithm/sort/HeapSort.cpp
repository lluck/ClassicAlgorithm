#include "HeapSort.h"



HeapSort::HeapSort()
{
}


HeapSort::~HeapSort()
{
}

/*
��������ָ���ö��������ݽṹ����Ƶ�һ��ѡ�������㷨������һ�ֽ�����ȫ�������Ľṹ��ͨ������ͨ��һά������ʵ�ֵģ���
���������ʣ������ѣ�Ҳ�д���ѡ��󶥶ѣ�Ϊ�������и�����ֵ���Ǵ������ĺ��ӽڵ㡣
���������Ĺ��̣�
	1.��������������鹹��һ�����ѣ���Ϊ��ʼ��������
	2.�ѶѶ�Ԫ�أ����ֵ���Ͷ�βԪ�ػ���
	3.�Ѷѣ����������ĳߴ���С1��������heapify(A, 0)���µĶѶ�Ԫ�ؿ�ʼ���жѵ���
	4.�ظ�����2��ֱ���ѵĳߴ�Ϊ1
*/

// ���� -------------- �ڲ��Ƚ�����
// ���ݽṹ ---------- ����
// ���ʱ�临�Ӷ� ---- O(nlogn)
// ����ʱ�临�Ӷ� ---- O(nlogn)
// ƽ��ʱ�临�Ӷ� ---- O(nlogn)
// ���踨���ռ� ------ O(1)
// �ȶ��� ------------ ���ȶ�
void HeapSort::sort(int arr[], uint size)
{
	if (!arr || size < 2)
		return;

	uint heapSize = size;
	buildBigHeap(arr, size);

	// �ѣ���������Ԫ�ظ�������1��δ�������
	while (heapSize > 1)
	{
		// ���Ѷ�Ԫ����ѵ����һ��Ԫ�ػ��������Ӷ���ȥ�����һ��Ԫ��
		// �˴������������п��ܰѺ���Ԫ�ص��ȶ��Դ��ң����Զ������ǲ��ȶ��������㷨
		--heapSize;
		swap(arr[0], arr[heapSize]);
		// ���µĶѶ�Ԫ�ؿ�ʼ���½��жѵ�����ʱ�临�Ӷ�O(logn)
		heapify(arr, 0, heapSize);
	}
}


// ����һ������, ʱ�临�Ӷ�O(n)
void HeapSort::buildBigHeap(int arr[], uint size)
{
	// ������, ��1����(ֱ��)�ӽڵ�Ŀռ�
	// unsigned int ���ܼ���-1
	uint len = size / 2 - 1;
	for (uint i = 0; i <= len; ++i)
	{
		// ��ÿһ����Ҷ��㿪ʼ���½��жѵ���
		heapify(arr, len - i, size);
	}
}


// ��A[i]���½��жѵ���
void HeapSort::heapify(int arr[], uint i, uint size)
{
	uint leftChild = 2 * i + 1;			// ��������
	uint rightChild = 2 * i + 2;		// �Һ�������
	uint max = i;

	// Ѱ��(ֱ��)�ӽڵ������ֵ, ��ֹ�������鷶Χ
	if (leftChild < size && arr[leftChild] > arr[max])
		max = leftChild;
	if (rightChild < size && arr[rightChild] > arr[max])
		max = rightChild;

	if (max != i)
	{
		// �ѵ�ǰ�����������(ֱ��)�ӽڵ���н���
		swap(arr[max], arr[i]);
		// �ݹ���ã������ӵ�ǰ�������(ֱ��)�ӽڵ����½��жѵ���, ֱ�����������������
		heapify(arr, max, size);
	}
}



int main_hs(int argc, char* argv[])
{
	int arr[12] = { 4, 3, 2, 1, 0, 9, 8, 7, 4, 2, -1, 2 };
    //int arr[9] = { 5, 2, 9, 4, 7, 6, 1, 3, 8 };
	int size = sizeof(arr) / sizeof(arr[0]);
	HeapSort st;

	printf("����ǰ:");
	printArr(arr, size);
	st.sort(arr, size);
	printf("�����:");
	printArr(arr, size);

	return 0;
}