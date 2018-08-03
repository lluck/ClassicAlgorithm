#pragma once
class Palindrome
{
public:
    Palindrome();
    ~Palindrome();

    // �ж�str[i...j]�Ƿ��ǻ��Ĵ�:���Ӷ�ΪO(n)
    static bool isPalindrome(const char* str, int begin, int end);

    // �����ַ���str��������Ӵ��ĳ���:ʱ�临�Ӷ�ΪO(n3)
    // ����ȫ���Ӵ�, �����ж��Ƿ��ǻ���, ȡ�����г��������Ӵ�
    static int longestPalindrome_V1(const char* str);

    // �����ַ���str��������Ӵ��ĳ���:ʱ�临�Ӷ�ΪO(n3)
    // ������Ӵ���ʼ�ж�, �Ƿ��ǻ���, �����������
    static int longestPalindrome_V2(const char* str);


    // ��midΪ������Ļ����Ӵ��ĳ���
    static int palindromeLen(const char* str, int mid);

    // �����ַ���str��������Ӵ��ĳ���:ʱ�临�Ӷ�ΪO(n2)
    /*
    *   ����һ���ַ���str�ǻ��Ĵ�����ô��һ�������ҶԳƵģ����Ը��ַ�����ĳ���ַ�str[mid]Ϊ���ĵ�ǰ׺�ͺ�׺һ������ͬ�ġ�
    *   ���磬���ڻ��Ĵ�"aba"����'b'Ϊ���ģ�����ǰ׺�ͺ�׺����'a'���ʣ�����ö���ַ�����ÿ���ַ���Ϊ���Ĵ�������λ�ã�������չ�õ����Ĵ���
    *   Ȼ��Ƚϵõ���ĳ��ȡ�
    *   ע�⣺������Ҫ���ǵ�һ�����������������"YXaaXY"��������Ϊż���������Ӵ���������Խ�"aa"��Ϊ'a'��
    *   ���㷨��ʱ�临�Ӷ�ΪO(n2)��
    */
    static int longestPalindrome_V3(const char* str);


    /*

    */
    static int longestPalindrome_V4(const char* str);


    /*
    *   ��һ�����Ĵ������������λ�õ��ַ�����Գ���ľ����Ϊ���İ뾶��
    *   Manacher������һ�����İ뾶����RL����RL[i]��ʾ�Ե�i���ַ�Ϊ�Գ���Ļ��Ĵ��Ļ��İ뾶
    *   MaxRight����ʾ��ǰ���ʵ������л����Ӵ������ܴ���������һ���ַ���λ��
    *   pos, ��ʾMaxRight��Ӧ�Ļ��Ĵ��ĶԳ������ڵ�λ��
    *   step 1: ��i��MaxRight����ߡ��ұ�, ��RL[i]=min(RL[2*pos-i], MaxRight-i), ����RL[i]=1, ��i���������߿�ʼ����������չ
    *   step 2: ��iΪ������չ���Ĵ���ֱ�����������ַ���ͬ�����ߵ���߽硣
    *   step 3: ����MaxRight��pos
    *   (4) ���Ӷȷ���
    *   �ռ临�Ӷȣ�����ָ����γ��´���ռ�������ԵĿռ��С��RL����Ҳռ�����Դ�С�Ŀռ䣬��˿ռ临�Ӷ������Եġ�
    *   ʱ�临�Ӷȣ����ܴ�������������ѭ����ͨ��amortized analysis���ǿ��Եó���Manacher��ʱ�临�Ӷ������Եġ�
    *   �����ڲ��ѭ��ֻ����δƥ��Ĳ��ֽ��У���˶���ÿһ���ַ����ԣ�ֻ�����һ�Σ����ʱ�临�Ӷ���O(n)��
    */
    static int longestPalindrome_V5(const char* str);


    static void printMatrix(int matrix[], const int size);

};

