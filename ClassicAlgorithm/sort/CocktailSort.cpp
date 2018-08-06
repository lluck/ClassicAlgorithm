#include "CocktailSort.h"



CocktailSort::CocktailSort()
{
}


CocktailSort::~CocktailSort()
{
}


/*
��β������Ҳ�ж���ð��������ð�������һ�ָĽ������㷨��ð������Ĳ�ͬ�����ڴӵ͵���Ȼ��Ӹߵ��ͣ�
��ð����������ӵ͵���ȥ�Ƚ��������ÿ��Ԫ�ء������Եõ���ð��������΢��һ���Ч��
*/

// ���� -------------- �ڲ��Ƚ�����
// ���ݽṹ ---------- ����
// ���ʱ�临�Ӷ� ---- O(n^2)
// ����ʱ�临�Ӷ� ---- ���������һ��ʼ�Ѿ��󲿷�������Ļ�,��ӽ�O(n)
// ƽ��ʱ�临�Ӷ� ---- O(n^2)
// ���踨���ռ� ------ O(1)
// �ȶ��� ------------ �ȶ�

void CocktailSort::sort(int arr[], uint size)
{
	if (!arr || size < 2)
		return;

	uint left = 0;
	uint right = size - 1;

	// ÿ���Ƿ��б�������Ԫ��, �ж������Ƿ��Ѿ��������
	int hasChanged = 0;

	while (left < right)
	{
		hasChanged = 0;

		// �����Ԫ�طŵ�����
		for (uint i = left; i < right; ++i)
		{
			// �ȽϺ����Ԫ��:i + 1
			if (arr[i] > arr[i + 1])
			{
				swap(arr[i], arr[i + 1]);
				hasChanged = 1;
				printArr(arr, size);
				printf("left=%d, right=%d, hasChanged=%d, i=%d\n", left, right, hasChanged, i);
			}
		}

		// �����Ԫ���Ѿ��������
		--right;

		printf("---\n");

		// ����СԪ�طŵ�ǰ��
		for (uint j = right; j > left; --j)
		{
			// �Ƚ�ǰ���Ԫ��:j - 1
			if (arr[j - 1] > arr[j])
			{
				swap(arr[j - 1], arr[j]);
				hasChanged = 1;
				printArr(arr, size);
				printf("left=%d, right=%d, hasChanged=%d, j =%d\n", left, right, hasChanged, j);
			}
		}

		// ǰ���Ԫ���Ѿ��������
		++left;

		// û��Ԫ�ر�����, �ж������Ƿ��Ѿ��������
		if (hasChanged == 0)
			break;

		printf("left=%d, right=%d, hasChanged=%d\n", left, right, hasChanged);
		printArr(arr, size);
	}
	// end of while loop
}


int main_cts(int argc, char* argv[])
{
	int arr[14] = { 4, 3, 2, 1, 0, 9, 8, 7, 4, 2, -1, 2, 9, 10 };
	//int arr[9] = { 5, 2, 9, 4, 7, 6, 1, 3, 8 };
	int size = sizeof(arr) / sizeof(arr[0]);
	CocktailSort st;

	printf("����ǰ:\n");
	printArr(arr, size);
	st.sort(arr, size);
	printf("�����:\n");
	printArr(arr, size);

	return 0;
}
