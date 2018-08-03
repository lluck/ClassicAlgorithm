#pragma once
class Palindrome
{
public:
    Palindrome();
    ~Palindrome();

    // 判断str[i...j]是否是回文串:复杂度为O(n)
    static bool isPalindrome(const char* str, int begin, int end);

    // 返回字符串str的最长回文子串的长度:时间复杂度为O(n3)
    // 遍历全部子串, 依次判断是否是回文, 取回文中长度最大的子串
    static int longestPalindrome_V1(const char* str);

    // 返回字符串str的最长回文子串的长度:时间复杂度为O(n3)
    // 从最长的子串开始判断, 是否是回文, 是则结束流程
    static int longestPalindrome_V2(const char* str);


    // 以mid为中心轴的回文子串的长度
    static int palindromeLen(const char* str, int mid);

    // 返回字符串str的最长回文子串的长度:时间复杂度为O(n2)
    /*
    *   假设一个字符串str是回文串，那么它一定是左右对称的，所以该字符串以某个字符str[mid]为中心的前缀和后缀一定是相同的。
    *   例如，对于回文串"aba"，以'b'为中心，它的前缀和后缀都是'a'。故，可以枚举字符串的每个字符作为回文串的中心位置，左右扩展得到回文串，
    *   然后比较得到最长的长度。
    *   注意：这里需要考虑到一个特殊情况，即存在"YXaaXY"这样长度为偶数的特殊子串，这里可以将"aa"视为'a'。
    *   该算法的时间复杂度为O(n2)。
    */
    static int longestPalindrome_V3(const char* str);


    /*

    */
    static int longestPalindrome_V4(const char* str);


    /*
    *   把一个回文串中最左或最右位置的字符与其对称轴的距离称为回文半径。
    *   Manacher定义了一个回文半径数组RL，用RL[i]表示以第i个字符为对称轴的回文串的回文半径
    *   MaxRight，表示当前访问到的所有回文子串，所能触及的最右一个字符的位置
    *   pos, 表示MaxRight对应的回文串的对称轴所在的位置
    *   step 1: 分i在MaxRight的左边、右边, 令RL[i]=min(RL[2*pos-i], MaxRight-i), 否则RL[i]=1, 从i的左右两边开始继续尝试扩展
    *   step 2: 以i为中心扩展回文串，直到左右两边字符不同，或者到达边界。
    *   step 3: 更新MaxRight和pos
    *   (4) 复杂度分析
    *   空间复杂度：插入分隔符形成新串，占用了线性的空间大小；RL数组也占用线性大小的空间，因此空间复杂度是线性的。
    *   时间复杂度：尽管代码里面有两层循环，通过amortized analysis我们可以得出，Manacher的时间复杂度是线性的。
    *   由于内层的循环只对尚未匹配的部分进行，因此对于每一个字符而言，只会进行一次，因此时间复杂度是O(n)。
    */
    static int longestPalindrome_V5(const char* str);


    static void printMatrix(int matrix[], const int size);

};

