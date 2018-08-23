#pragma once
#include "Base.h"

class Search
{
public:
    Search();
    virtual ~Search();

    // ��¼�㷨ѭ������, ��Ӽ���ʱ�临�Ӷ�
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
        printf("�㷨ѭ������:%lld\n", this->loopCount);
    }

    // ˳�����, ʱ�临�Ӷ�ΪO(N)
    int sequenceSearch(int arr[], uint size, int value);

    // ���ֲ���(�۰����), ���ݹ�, Ҫ������, ʱ�临�Ӷ�ΪO(log2N)
    int binarySearch(int arr[], uint size, int value);
    // ���ֲ���(�۰����), �ݹ�, Ҫ������, ʱ�临�Ӷ�ΪO(log2N)
    int binarySearchRecursive(int arr[], uint size, int value, int low, int high);

    // ��ֵ����, ���ݹ�, Ҫ������, ʱ�临�Ӷ�ΪO(log2N)
    int insertSearch(int arr[], uint size, int value);
    // ��ֵ����, �ݹ�, Ҫ������, ʱ�临�Ӷ�ΪO(log2N)
    int insertSearchRecursive(int arr[], uint size, int value, int low, int high);



private:
    ullint loopCount;
};

