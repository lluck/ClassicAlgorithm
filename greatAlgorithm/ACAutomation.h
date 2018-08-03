#pragma once

#include <string.h>

#define     AC_AUTOMATION_KIND              26
#define     AC_AUTOMATION_MAX_QUEUE_LEN     6

struct Node
{
    Node* fail;                             // 失败指针
    Node* next[AC_AUTOMATION_KIND];         // Tire每个节点的个子节点（最多个字母）
    int count;                              // 是否为该单词的最后一个节点, 这个节点是不是一个单词的结尾，以及相应的个数
    char value;                             // value值

    Node()
    {
        fail = NULL;
        count = 0;
        memset(next, NULL, sizeof(next));
        value = 0x00;
    }

};


class ACAutomation
{
public:
    ACAutomation();
    ~ACAutomation();

    // 写入数据
    void insert(const char* str, Node* root);

    /*
    *    构造失败指针的过程概括起来就一句话：设这个节点上的字母为C，沿着他父亲的失败指针走，直到走到一个节点，他的儿子中也有字母为C的节点。
    *    然后把当前节点的失败指针指向那个字母也为C的儿子。如果一直走到了root都没找到，那就把失败指针指向root。
    *    具体操作起来只需要：先把root加入队列(root的失败指针指向自己或者NULL)，这以后我们每处理一个点，就把它的所有儿子加入队列，队列为空。
    */
    // 构造失败指针:使用定长队列
    void build_ac_automation(Node* root);

    /*
    *    构造失败指针的过程概括起来就一句话：设这个节点上的字母为C，沿着他父亲的失败指针走，直到走到一个节点，他的儿子中也有字母为C的节点。
    *    然后把当前节点的失败指针指向那个字母也为C的儿子。如果一直走到了root都没找到，那就把失败指针指向root。
    *    具体操作起来只需要：先把root加入队列(root的失败指针指向自己或者NULL)，这以后我们每处理一个点，就把它的所有儿子加入队列，队列为空。
    */
    // 构造失败指针:使用deque
    void build_ac_automation_deque(Node* root);

    /*
    *   匹配过程分两种情况：(1)当前字符匹配，表示从当前节点沿着树边有一条路径可以到达目标字符，此时只需沿该路径走向下一个节点继续匹配即可，
    *   目标字符串指针移向下个字符继续匹配；(2)当前字符不匹配，则去当前节点失败指针所指向的字符继续匹配，匹配过程随着指针指向root结束。
    *   重复这2个过程中的任意一个，直到模式串走到结尾为止。
    */
    int query(const char* str, Node* root);

    void printACAutomation(Node* root);
};

