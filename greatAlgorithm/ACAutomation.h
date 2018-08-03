#pragma once

#include <string.h>

#define     AC_AUTOMATION_KIND              26
#define     AC_AUTOMATION_MAX_QUEUE_LEN     6

struct Node
{
    Node* fail;                             // ʧ��ָ��
    Node* next[AC_AUTOMATION_KIND];         // Tireÿ���ڵ�ĸ��ӽڵ㣨������ĸ��
    int count;                              // �Ƿ�Ϊ�õ��ʵ����һ���ڵ�, ����ڵ��ǲ���һ�����ʵĽ�β���Լ���Ӧ�ĸ���
    char value;                             // valueֵ

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

    // д������
    void insert(const char* str, Node* root);

    /*
    *    ����ʧ��ָ��Ĺ��̸���������һ�仰��������ڵ��ϵ���ĸΪC�����������׵�ʧ��ָ���ߣ�ֱ���ߵ�һ���ڵ㣬���Ķ�����Ҳ����ĸΪC�Ľڵ㡣
    *    Ȼ��ѵ�ǰ�ڵ��ʧ��ָ��ָ���Ǹ���ĸҲΪC�Ķ��ӡ����һֱ�ߵ���root��û�ҵ����ǾͰ�ʧ��ָ��ָ��root��
    *    �����������ֻ��Ҫ���Ȱ�root�������(root��ʧ��ָ��ָ���Լ�����NULL)�����Ժ�����ÿ����һ���㣬�Ͱ��������ж��Ӽ�����У�����Ϊ�ա�
    */
    // ����ʧ��ָ��:ʹ�ö�������
    void build_ac_automation(Node* root);

    /*
    *    ����ʧ��ָ��Ĺ��̸���������һ�仰��������ڵ��ϵ���ĸΪC�����������׵�ʧ��ָ���ߣ�ֱ���ߵ�һ���ڵ㣬���Ķ�����Ҳ����ĸΪC�Ľڵ㡣
    *    Ȼ��ѵ�ǰ�ڵ��ʧ��ָ��ָ���Ǹ���ĸҲΪC�Ķ��ӡ����һֱ�ߵ���root��û�ҵ����ǾͰ�ʧ��ָ��ָ��root��
    *    �����������ֻ��Ҫ���Ȱ�root�������(root��ʧ��ָ��ָ���Լ�����NULL)�����Ժ�����ÿ����һ���㣬�Ͱ��������ж��Ӽ�����У�����Ϊ�ա�
    */
    // ����ʧ��ָ��:ʹ��deque
    void build_ac_automation_deque(Node* root);

    /*
    *   ƥ����̷����������(1)��ǰ�ַ�ƥ�䣬��ʾ�ӵ�ǰ�ڵ�����������һ��·�����Ե���Ŀ���ַ�����ʱֻ���ظ�·��������һ���ڵ����ƥ�伴�ɣ�
    *   Ŀ���ַ���ָ�������¸��ַ�����ƥ�䣻(2)��ǰ�ַ���ƥ�䣬��ȥ��ǰ�ڵ�ʧ��ָ����ָ����ַ�����ƥ�䣬ƥ���������ָ��ָ��root������
    *   �ظ���2�������е�����һ����ֱ��ģʽ���ߵ���βΪֹ��
    */
    int query(const char* str, Node* root);

    void printACAutomation(Node* root);
};

