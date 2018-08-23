#pragma once
#include "Base.h"


class ListNode
{
public:
    explicit ListNode(int value)
    {
        this->value = value;
    }

    virtual ~ListNode() {}

    void printNode()
    {
        log("%d-%p ", this->value, this);
    }


public:
    int value;
    ListNode* next = nullptr;
};


class List
{
public:
    List();
    virtual ~List();

    inline bool isEmpty()
    {
        return head == nullptr;
    }

    inline uint size()
    {
        return this->_size;
    }

    // 输出列表
    void printList();

    // 添加元素
    void addValue(int value);

    // 反转列表
    void reverse();


private:
    ListNode* head = nullptr;
    uint _size = 0L;
};

