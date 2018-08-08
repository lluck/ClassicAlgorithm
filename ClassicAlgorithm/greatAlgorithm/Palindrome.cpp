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


// 判断str[i...j]是否是回文串:复杂度为O(n)
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


// 返回字符串str的最长回文子串的长度:时间复杂度为O(n3)
// 遍历全部子串, 依次判断是否是回文, 取回文中长度最大的子串
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
            printf("V1破解算法循环次数:%lld, i=%d, j=%d\n",
                count, i, j);

            if (isPalindrome(str, i, j) && longest < j - i + 1)
            {
                longest = j - i + 1;
            }

        }
    }

    return longest;

}


// 返回字符串str的最长回文子串的长度:时间复杂度为O(n3)
// 从最长的子串开始判断, 是否是回文, 是则结束流程
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
            printf("V2破解算法循环次数:%lld, i=%d, j=%d\n",
                count, i, j);

            if (isPalindrome(str, i, j))
            {
                return j - i + 1;
            }
        }
    }

    return 0;
}



// 以mid为中心轴的回文子串的长度
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


// 返回字符串str的最长回文子串的长度:时间复杂度为O(n2)
/*
*   假设一个字符串str是回文串，那么它一定是左右对称的，所以该字符串以某个字符str[mid]为中心的前缀和后缀一定是相同的。
*   例如，对于回文串"aba"，以'b'为中心，它的前缀和后缀都是'a'。故，可以枚举字符串的每个字符作为回文串的中心位置，左右扩展得到回文串，
*   然后比较得到最长的长度。
*   注意：这里需要考虑到一个特殊情况，即存在"YXaaXY"这样长度为偶数的特殊子串，这里可以将"aa"视为'a'。
*   该算法的时间复杂度为O(n2)。
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

        printf("V3中心扩展算法循环次数:%lld, i=%d, longest=%d, sonLen=%d, sonStr=%s\n",
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
    i:中心点
    j:覆盖范围
    k:最大覆盖范围测试值
    */
    for (int i = 1, j = 0; i < strLen; i += k)
    {
        while (i - j - 1 >= 0 && str[i - j - 1] == str[i + j + 1])
            ++j;
        rad[i] = j;

        // 利用类似镜像的方法缩短了时间
        for (k = 1; k <= rad[i] && rad[i - k] != rad[i] - k; ++k)
        {
            rad[i + k] = std::min(rad[i - k], rad[i] - k);

            ++count;
            printf("V4Manacher算法循环次数:%lld, longest=%d, i=%d, j=%d, k=%d\n",
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
*   把一个回文串中最左或最右位置的字符与其对称轴的距离称为回文半径。
*   Manacher定义了一个回文半径数组RL，用RL[i]表示以第i个字符为对称轴的回文串的回文半径
*   MaxRight，表示当前访问到的所有回文子串，所能触及的最右一个字符的位置
*   pos, 表示MaxRight对应的回文串的对称轴所在的位置
*   step 1: 分i在MaxRight的左边、右边, 在左边时再根据RL[j]的长短时分为2种情况
            令RL[i]=min(RL[2*pos-i], MaxRight-i), 否则RL[i]=1, 从i的左右两边开始继续尝试扩展
*   step 2: 以i为中心扩展回文串，直到左右两边字符不同，或者到达边界。
*   step 3: 更新MaxRight和pos
*   (4) 复杂度分析
*   空间复杂度：插入分隔符形成新串，占用了线性的空间大小；RL数组也占用线性大小的空间，因此空间复杂度是线性的。
*   时间复杂度：尽管代码里面有两层循环，通过amortized analysis我们可以得出，Manacher的时间复杂度是线性的。
*   由于内层的循环只对尚未匹配的部分进行，因此对于每一个字符而言，只会进行一次，因此时间复杂度是O(n)。
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
        // step 1: 1）当i在MaxRight的左边, 令RL[i]=min(RL[2*pos-i], MaxRight-i), 否则RL[i]=1, 只能从i的左右两边开始尝试扩展
        if (i < maxRight)
        {
            /*
            *   当i在MaxRight的左边, i相对于pos的对称点j上的回文半径RL[j]可能很短、也可能很长
            *   1) 较短时, j的回文长度包含在pos的回文范围内, RL[i] >= RL[j], 继续尝试以i为对称轴，继续往左右两边扩展，
            *      直到左右两边字符不同，或者到达边界
            *      RL[i] = RL[j] = RL[2 * pos - i], j = pos - (i - pos) = 2 * pos - i
            *   2) 较长时, j的回文长度超出了pos的回文范围, 这时只能确定不超过MaxRight的部分是回文的
            *      从这个长度开始，尝试以i为中心向左右两边扩展，直到左右两边字符不同，或者到达边界
            *      RL[i] = maxRight - i
            */
            RL[i] = std::min(RL[2 * pos - i], maxRight - i);
        }
        else
            RL[i] = 1;

        // step 2: 以i为中心扩展回文串，直到左右两边字符不同，或者到达边界
        // 注意处理边界:左边界, 右边界
        while (i - RL[i] >= 0 && i + RL[i] < strLen && str[i - RL[i]] == str[i + RL[i]])
        {
            ++RL[i];
            ++count;
        }

        ++count;

        // 更新MaxRight, pos
        if (RL[i] + i - 1 > maxRight)
        {
            maxRight = RL[i] + i - 1;
            pos = i;
        }

        // 更新最长回文串的长度
        if (RL[i] > longest)
            longest = RL[i];

        printMatrix(RL, strLen);
        printf("V5Manacher算法循环次数:%lld, longest=%d, i=%d, maxRight=%d, pos=%d\n",
            count, longest, i, maxRight, pos);
    }

    printMatrix(RL, strLen);

    delete [] RL;

    // RL[i]-1的值，正是在原本那个没有插入过分隔符的串中，以位置i为对称轴的最长回文串的长度
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
    printf("str:%s, 是否是回文:%d, 最长回文子串长度:%d\n", str, result, longest);

    longest = pd.longestPalindrome_V2(str);
    printf("str:%s, 是否是回文:%d, 最长回文子串长度:%d\n", str, result, longest);

    longest = pd.longestPalindrome_V3(str);
    printf("str:%s, 是否是回文:%d, 最长回文子串长度:%d\n", str, result, longest);

    str = "#a#b#a#";
    str = "#a#b#c#d#e#f#g#";
    longest = pd.longestPalindrome_V4(str);
    printf("str:%s, 是否是回文:%d, 最长回文子串长度:%d\n", str, result, longest);

    str = "#a#b#a#";
    longest = pd.longestPalindrome_V5(str);
    printf("str:%s, 是否是回文:%d, 最长回文子串长度:%d\n", str, result, longest);

    return 0;
}