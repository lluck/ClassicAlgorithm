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

    // ����б�
    void printList();

    // ���Ԫ��
    void addValue(int value);

    // ��ת�б�
    void reverse();


private:
    ListNode* head = nullptr;
    uint _size = 0L;
};

