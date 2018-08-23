#include "Search.h"
#include "RadixSort.h"

Search::Search()
{
    loopCount = 0;
}


Search::~Search()
{
}


/*
1. ˳�����
����˵����˳������ʺ��ڴ洢�ṹΪ˳��洢�����Ӵ洢�����Ա�
  ������˼�룺˳�����Ҳ��Ϊ���β��ң�������������㷨�������ݽṹ���α��һ�˿�ʼ��˳��ɨ�裬���ν�ɨ�赽�Ľ��ؼ��������ֵk��Ƚϣ�
              ��������ʾ���ҳɹ�����ɨ�������û���ҵ��ؼ��ֵ���k�Ľ�㣬��ʾ����ʧ�ܡ�
    ���Ӷȷ�������
      �������ҳɹ�ʱ��ƽ�����ҳ���Ϊ��������ÿ������Ԫ�صĸ�����ȣ� ASL = 1/n(1+2+3+��+n) = (n+1)/2 ;
        �������Ҳ��ɹ�ʱ����Ҫn+1�αȽϣ�ʱ�临�Ӷ�ΪO(n);
          ���ԣ�˳����ҵ�ʱ�临�Ӷ�ΪO(n)��
*/
// ˳�����, ʱ�临�Ӷ�ΪO(N), ��Ҫ������
int Search::sequenceSearch(int arr[], uint size, int value)
{
    for (int i = 0; i < size; ++i)
    {
        ++loopCount;
        if (arr[i] == value)
            return i;
    }
    return -1;
}



/*
2. ���ֲ���
    ˵����Ԫ�ر���������ģ�������������Ҫ�Ƚ������������
��������˼�룺Ҳ��Ϊ���۰���ң�������������㷨���ø���ֵk�����м���Ĺؼ��ֱȽϣ��м�������α�ֳ������ӱ����������ҳɹ���
              ������ȣ��ٸ���k����м���ؼ��ֵıȽϽ��ȷ����һ�������ĸ��ӱ������ݹ���У�ֱ�����ҵ�����ҽ������ֱ���û�������Ľ�㡣
    ���Ӷȷ����������£��ؼ��ʱȽϴ���Ϊlog2(n+1)��������ʱ�临�Ӷ�ΪO(log2n)��
    ע���۰���ҵ�ǰ����������Ҫ�����˳��洢�����ھ�̬���ұ�һ��������ٱ仯���۰�����ܵõ������Ч�ʡ�
    ��������ҪƵ��ִ�в����ɾ�����������ݼ���˵��ά�����������������С�Ĺ��������ǾͲ�����ʹ�á������������ݽṹ��
*/
// ���ֲ���(�۰����), ���ݹ�, Ҫ������, ʱ�临�Ӷ�ΪO(log2N)
int Search::binarySearch(int arr[], uint size, int value)
{
    int low = 0;
    int high = size - 1;
    int mid = -1;

    while (low <= high)
    {
        ++loopCount;
        mid = (low + high) / 2;
        if (arr[mid] == value)
            return mid;
        else if (arr[mid] < value)
            low = mid + 1;
        else
            high = mid - 1;
    }

    return -1;
}


// ���ֲ���(�۰����), �ݹ�, Ҫ������, ʱ�临�Ӷ�ΪO(log2N)
int Search::binarySearchRecursive(int arr[], uint size, int value, int low, int high)
{
    if (!arr || low > high)
        return - 1;

    int mid = (low + high) / 2;
    mid = low + (high - low) / 2;
    ++loopCount;

    if (arr[mid] == value)
        return mid;
    else if (arr[mid] < value)
        return binarySearchRecursive(arr, size, value, mid + 1, high);
    else
        return binarySearchRecursive(arr, size, value, low, mid - 1);
}


/*
3. ��ֵ����
�����ڽ��ܲ�ֵ����֮ǰ�����ȿ���һ�������⣬Ϊʲô�����㷨һ��Ҫ���۰룬���������ķ�֮һ�����۸����أ�
  ������ȷ�����Ӣ���ֵ�����顰apple����������ʶ�����ֵ��Ƿ�ǰ�����ҳ���Ǻ������ҳ�أ����������顰zoo����������ô�飿
    ����Ȼ����������Բ����Ǵ��м俪ʼ���𣬶�����һ��Ŀ�ĵ���ǰ�����󷭡�
    ͬ���ģ�����Ҫ��ȡֵ��Χ1 ~ 10000 ֮�� 100 ��Ԫ�ش�С������ȷֲ��������в���5�� ������Ȼ�ῼ�Ǵ������±��С�Ŀ�ʼ���ҡ�
    �������Ϸ������۰�������ֲ��ҷ�ʽ����������Ӧ�ģ�Ҳ����˵��ɵ��ʽ�ģ������ֲ����в��ҵ�������£�
        mid=(low+high)/2, ��mid=low+1/2*(high-low);
    ͨ����ȣ����ǿ��Խ����ҵĵ�Ľ�Ϊ���£�
        mid=low+(key-a[low])/(a[high]-a[low])*(high-low)��
    Ҳ���ǽ������ı�������1/2�Ľ�Ϊ����Ӧ�ģ����ݹؼ����������������������λ�ã���midֵ�ı仯�������ؼ���key��
    ����Ҳ�ͼ�ӵؼ����˱Ƚϴ�����
    
    ����˼�룺���ڶ��ֲ����㷨�������ҵ��ѡ��Ľ�Ϊ����Ӧѡ�񣬿�����߲���Ч�ʡ���Ȼ����ֵ����Ҳ����������ҡ�
    ע�����ڱ��ϴ󣬶��ؼ��ֲַ��ֱȽϾ��ȵĲ��ұ���˵����ֵ�����㷨��ƽ�����ܱ��۰����Ҫ�õĶࡣ
    ��֮������������ֲ��ǳ������ȣ���ô��ֵ����δ���Ǻܺ��ʵ�ѡ��
    ���Ӷȷ��������ҳɹ�����ʧ�ܵ�ʱ�临�ӶȾ�ΪO(log2(log2n))��
*/
// ��ֵ����, ���ݹ�, Ҫ������, ʱ�临�Ӷ�ΪO(log2N)
int Search::insertSearch(int arr[], uint size, int value)
{
    int low = 0;
    int high = size - 1;
    int mid = 0;

    while (low <= high)
    {
        ++loopCount;
        // mid = low + (high - low) / 2;
        mid = low + (value - arr[low]) / (arr[high] - arr[low] + 0.01) * (high - low);

        if (arr[mid] == value)
            return mid;
        else if (arr[mid] < value)
            low = mid + 1;
        else
            high = mid - 1;
    }

    return -1;
}


// ��ֵ����, �ݹ�, Ҫ������, ʱ�临�Ӷ�ΪO(log2N)
int Search::insertSearchRecursive(int arr[], uint size, int value, int low, int high)
{
    if (!arr || low > high)
        return -1;

    int mid = low + (value - arr[low]) / (arr[high] - arr[low] + 0.01) * (high - low);
    ++loopCount;

    if (arr[mid] == value)
        return mid;
    else if (arr[mid] < value)
        return insertSearchRecursive(arr, size, value, mid + 1, high);
    else
        return insertSearchRecursive(arr, size, value, low, mid - 1);
}


int main_sech(void)
{
    int arr[12] = { 4, 3, 6, 1, 2, 9, 8, 7, 5, 12, 11, 10};
    //int arr[1] = { 8 };
    int size = sizeof(arr) / sizeof(arr[0]);

    printArr(arr, size);

    int value = 8;
    int index = -1;
    Search sh;

    index = sh.sequenceSearch(arr, size, value);
    sh.printLoopCount();

    RadixSort st;
    st.sort(arr, size);
    printArr(arr, size);

    sh.setLoopCount();
    index = sh.binarySearch(arr, size, value);
    sh.printLoopCount();
    printf("��ѯ:[%d], ���:[%d]\n", value, index);
    
    sh.setLoopCount();
    index = sh.binarySearchRecursive(arr, size, value, 0, size - 1);
    sh.printLoopCount();
    printf("��ѯ:[%d], ���:[%d]\n", value, index);
    
    sh.setLoopCount();
    index = sh.insertSearch(arr, size, value);
    sh.printLoopCount();
    printf("��ѯ:[%d], ���:[%d]\n", value, index);

    sh.setLoopCount();
    index = sh.insertSearchRecursive(arr, size, value, 0, size - 1);
    sh.printLoopCount();
    printf("��ѯ:[%d], ���:[%d]\n", value, index);

    return 0;
}
