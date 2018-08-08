#include <stdio.h>
#include <string.h>
#include <algorithm>
#include "Palindrome.h"



Palindrome::Palindrome()
{

}


Palindrome::~Palindrome()
{

}


// �ж�str[i...j]�Ƿ��ǻ��Ĵ�:���Ӷ�ΪO(n)
inline bool Palindrome::isPalindrome(const char* str, int begin, int end)
{
    if (!str)
        return false;

    while (begin < end && str[begin])
    {
        if (str[begin] == str[end])
        {
            ++begin;
            --end;
        }
        else
        {
            return false;
        }
    }

    return true;
}


// �����ַ���str��������Ӵ��ĳ���:ʱ�临�Ӷ�ΪO(n3)
// ����ȫ���Ӵ�, �����ж��Ƿ��ǻ���, ȡ�����г��������Ӵ�
int Palindrome::longestPalindrome_V1(const char* str)
{
    if (!str)
        return 0;

    int len = strlen(str);
    if (len == 1)
        return 1;

    int longest = 1;
    long long int count = 0L;

    for (int i = 0; i < len; ++i)
    {
        for (int j = i + 1; j < len; ++j)
        {
            ++count;
            printf("V1�ƽ��㷨ѭ������:%lld, i=%d, j=%d\n",
                count, i, j);

            if (isPalindrome(str, i, j) && longest < j - i + 1)
            {
                longest = j - i + 1;
            }

        }
    }

    return longest;

}


// �����ַ���str��������Ӵ��ĳ���:ʱ�临�Ӷ�ΪO(n3)
// ������Ӵ���ʼ�ж�, �Ƿ��ǻ���, �����������
int Palindrome::longestPalindrome_V2(const char* str)
{
    if (!str)
        return 0;

    int len = strlen(str);
    if (len == 1)
        return 1;

    long long int count = 0L;

    for (int i = 0; i < len; ++i)
    {
        for (int j = len - 1; j > 0; --j)
        {
            ++count;
            printf("V2�ƽ��㷨ѭ������:%lld, i=%d, j=%d\n",
                count, i, j);

            if (isPalindrome(str, i, j))
            {
                return j - i + 1;
            }
        }
    }

    return 0;
}



// ��midΪ������Ļ����Ӵ��ĳ���
int Palindrome::palindromeLen(const char* str, int mid)
{
    int left = mid - 1;
    int right = mid + 1;
    int len = strlen(str);

    while (str[mid] == str[right])
        ++right;

    while (left >= 0 && right < len && str[left] == str[right])
    {
        --left;
        ++right;
    }

    return right - left - 1;
}


// �����ַ���str��������Ӵ��ĳ���:ʱ�临�Ӷ�ΪO(n2)
/*
*   ����һ���ַ���str�ǻ��Ĵ�����ô��һ�������ҶԳƵģ����Ը��ַ�����ĳ���ַ�str[mid]Ϊ���ĵ�ǰ׺�ͺ�׺һ������ͬ�ġ�
*   ���磬���ڻ��Ĵ�"aba"����'b'Ϊ���ģ�����ǰ׺�ͺ�׺����'a'���ʣ�����ö���ַ�����ÿ���ַ���Ϊ���Ĵ�������λ�ã�������չ�õ����Ĵ���
*   Ȼ��Ƚϵõ���ĳ��ȡ�
*   ע�⣺������Ҫ���ǵ�һ�����������������"YXaaXY"��������Ϊż���������Ӵ���������Խ�"aa"��Ϊ'a'��
*   ���㷨��ʱ�临�Ӷ�ΪO(n2)��
*/
int Palindrome::longestPalindrome_V3(const char* str)
{
    if (!str)
        return 0;

    int len = strlen(str);
    if (len == 1)
        return 1;

    int longest = 0;
    long long int count = 0L;

    for (int i = 0; i < len; ++i)
    {
        ++count;
        int sonLen = palindromeLen(str, i);

        printf("V3������չ�㷨ѭ������:%lld, i=%d, longest=%d, sonLen=%d, sonStr=%s\n",
            count, i, longest, sonLen, str + i);

        if (sonLen > longest)
            longest = sonLen;
    }

    return longest;
}


/*

*/
int Palindrome::longestPalindrome_V4(const char* str)
{
    if (!str)
        return 0;

    int len = strlen(str);
    if (len == 1)
        return 1;

    int k = 0;
    int strLen = strlen(str);

    int* rad = new int[strLen];

    int longest = 1;
    long long int count = 0L;

    /*
    i:���ĵ�
    j:���Ƿ�Χ
    k:��󸲸Ƿ�Χ����ֵ
    */
    for (int i = 1, j = 0; i < strLen; i += k)
    {
        while (i - j - 1 >= 0 && str[i - j - 1] == str[i + j + 1])
            ++j;
        rad[i] = j;

        // �������ƾ���ķ���������ʱ��
        for (k = 1; k <= rad[i] && rad[i - k] != rad[i] - k; ++k)
        {
            rad[i + k] = std::min(rad[i - k], rad[i] - k);

            ++count;
            printf("V4Manacher�㷨ѭ������:%lld, longest=%d, i=%d, j=%d, k=%d\n",
                count, longest, i, j, k);
        }

        j = std::max(j - k, 0);
    }

    for (int i = 0; i < strLen; ++i)
    {
        if (rad[i] > longest)
            longest = rad[i];
    }

    delete[] rad;

    return longest;
}


/*
*   https://segmentfault.com/a/1190000003914228
*   ��һ�����Ĵ������������λ�õ��ַ�����Գ���ľ����Ϊ���İ뾶��
*   Manacher������һ�����İ뾶����RL����RL[i]��ʾ�Ե�i���ַ�Ϊ�Գ���Ļ��Ĵ��Ļ��İ뾶
*   MaxRight����ʾ��ǰ���ʵ������л����Ӵ������ܴ���������һ���ַ���λ��
*   pos, ��ʾMaxRight��Ӧ�Ļ��Ĵ��ĶԳ������ڵ�λ��
*   step 1: ��i��MaxRight����ߡ��ұ�, �����ʱ�ٸ���RL[j]�ĳ���ʱ��Ϊ2�����
            ��RL[i]=min(RL[2*pos-i], MaxRight-i), ����RL[i]=1, ��i���������߿�ʼ����������չ
*   step 2: ��iΪ������չ���Ĵ���ֱ�����������ַ���ͬ�����ߵ���߽硣
*   step 3: ����MaxRight��pos
*   (4) ���Ӷȷ���
*   �ռ临�Ӷȣ�����ָ����γ��´���ռ�������ԵĿռ��С��RL����Ҳռ�����Դ�С�Ŀռ䣬��˿ռ临�Ӷ������Եġ�
*   ʱ�临�Ӷȣ����ܴ�������������ѭ����ͨ��amortized analysis���ǿ��Եó���Manacher��ʱ�临�Ӷ������Եġ�
*   �����ڲ��ѭ��ֻ����δƥ��Ĳ��ֽ��У���˶���ÿһ���ַ����ԣ�ֻ�����һ�Σ����ʱ�临�Ӷ���O(n)��
*/
int Palindrome::longestPalindrome_V5(const char* str)
{
    if (!str)
        return 0;

    int strLen = strlen(str);
    int longest = 0;
    long long int count = 0L;

    int maxRight = 0;
    int pos = 0;

    int* RL = new int[strLen];

    for (int i = 0; i < strLen; ++i)
    {
        // step 1: 1����i��MaxRight�����, ��RL[i]=min(RL[2*pos-i], MaxRight-i), ����RL[i]=1, ֻ�ܴ�i���������߿�ʼ������չ
        if (i < maxRight)
        {
            /*
            *   ��i��MaxRight�����, i�����pos�ĶԳƵ�j�ϵĻ��İ뾶RL[j]���̡ܺܶ�Ҳ���ܺܳ�
            *   1) �϶�ʱ, j�Ļ��ĳ��Ȱ�����pos�Ļ��ķ�Χ��, RL[i] >= RL[j], ����������iΪ�Գ��ᣬ����������������չ��
            *      ֱ�����������ַ���ͬ�����ߵ���߽�
            *      RL[i] = RL[j] = RL[2 * pos - i], j = pos - (i - pos) = 2 * pos - i
            *   2) �ϳ�ʱ, j�Ļ��ĳ��ȳ�����pos�Ļ��ķ�Χ, ��ʱֻ��ȷ��������MaxRight�Ĳ����ǻ��ĵ�
            *      ��������ȿ�ʼ��������iΪ����������������չ��ֱ�����������ַ���ͬ�����ߵ���߽�
            *      RL[i] = maxRight - i
            */
            RL[i] = std::min(RL[2 * pos - i], maxRight - i);
        }
        else
            RL[i] = 1;

        // step 2: ��iΪ������չ���Ĵ���ֱ�����������ַ���ͬ�����ߵ���߽�
        // ע�⴦��߽�:��߽�, �ұ߽�
        while (i - RL[i] >= 0 && i + RL[i] < strLen && str[i - RL[i]] == str[i + RL[i]])
        {
            ++RL[i];
            ++count;
        }

        ++count;

        // ����MaxRight, pos
        if (RL[i] + i - 1 > maxRight)
        {
            maxRight = RL[i] + i - 1;
            pos = i;
        }

        // ��������Ĵ��ĳ���
        if (RL[i] > longest)
            longest = RL[i];

        printMatrix(RL, strLen);
        printf("V5Manacher�㷨ѭ������:%lld, longest=%d, i=%d, maxRight=%d, pos=%d\n",
            count, longest, i, maxRight, pos);
    }

    printMatrix(RL, strLen);

    delete [] RL;

    // RL[i]-1��ֵ��������ԭ���Ǹ�û�в�����ָ����Ĵ��У���λ��iΪ�Գ��������Ĵ��ĳ���
    return longest - 1;
}

void Palindrome::printMatrix(int matrix[], const int size)
{
    for (int i = 0; i < size; ++i)
        printf("%d ", matrix[i]);
    printf("\n");
}


//------------------------------ main -------------------------------------------


int mainPd(int argc, char* argv[])
{
    char* p = nullptr;

    const char* str = "aba";
    str = "aahesh";
    str = "abac";
    str = "cccabacc";
    str = "YXaaXY";
    str = "abcdefg";

    Palindrome pd;
    bool result = false;
    int longest = 0;

    result = pd.isPalindrome(str, 0, strlen(str) - 1);

    longest = pd.longestPalindrome_V1(str);
    printf("str:%s, �Ƿ��ǻ���:%d, ������Ӵ�����:%d\n", str, result, longest);

    longest = pd.longestPalindrome_V2(str);
    printf("str:%s, �Ƿ��ǻ���:%d, ������Ӵ�����:%d\n", str, result, longest);

    longest = pd.longestPalindrome_V3(str);
    printf("str:%s, �Ƿ��ǻ���:%d, ������Ӵ�����:%d\n", str, result, longest);

    str = "#a#b#a#";
    str = "#a#b#c#d#e#f#g#";
    longest = pd.longestPalindrome_V4(str);
    printf("str:%s, �Ƿ��ǻ���:%d, ������Ӵ�����:%d\n", str, result, longest);

    str = "#a#b#a#";
    longest = pd.longestPalindrome_V5(str);
    printf("str:%s, �Ƿ��ǻ���:%d, ������Ӵ�����:%d\n", str, result, longest);

    return 0;
}