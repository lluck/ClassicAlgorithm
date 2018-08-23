#pragma once
#include "Base.h"


#define     TREE_NODE_SPACE     3

class TreeNode
{
public:
    explicit TreeNode(int value)
    {
        this->value = value;
    }

    virtual ~TreeNode() { log("freeing"); }

    void printNode(int x = 0)
    {
        int tmp = xpos - x - 2;
        if (x >= 0)
        {
            log("%*s", tmp, "");
            log("%d", this->value);
        }
        else
            log("%d ", this->value);
    }

    inline bool hasParent()
    {
        return this->parent != nullptr;
    }

    inline bool hasLeft()
    {
        return this->left != nullptr;
    }

    inline bool hasRight()
    {
        return this->right != nullptr;
    }

    inline bool isChildren(TreeNode* child)
    {
        return child && (child == this->left || child == this->right);
    }

    friend class Tree;

public:
    int value;
    int xpos;
    int ypos;
    TreeNode *parent = nullptr;
    TreeNode *left = nullptr;
    TreeNode *right = nullptr;
};


class Tree
{
public:
    Tree();
    virtual ~Tree();

    // ��֪ǰ����������У�����������
    static TreeNode* buildTreePreIn(int *preOrder, int* inOrder, int len);
    // ��֪������������У�����������
    static TreeNode* buildTreePostIn(int *postOrder, int* inOrder, int len);

    // �ͷŽڵ㼰�ӽ��
    static void free(TreeNode *p);


    // ǰ��������--�ݹ�
    void printPreOrder(TreeNode *root);
    // ǰ��������--�ǵݹ�
    void printPreOrderIter(TreeNode *root);
    // ����������--�ݹ�
    void printInOrder(TreeNode *root);
    // ����������--�ǵݹ�
    void printInOrderIter(TreeNode *root);
    // ����������--�ݹ�
    void printPostOrder(TreeNode *root);
    // ����������--�ǵݹ�
    void printPostOrderIter(TreeNode *root);

    // �㼶���
    void printTree(TreeNode *p = nullptr);

    void insert(TreeNode * & root, int value);


    // �����ڵ�������������
    TreeNode* getNearestAncestor(TreeNode *root, TreeNode *fir, TreeNode *sec);

    // �������Ŀ��, ����������ڵ���������ֵ
    int width(TreeNode *root);

    // �������ĸ߶�, Ҷ�ӽڵ��������ֵ
    int height(TreeNode *root);

    // ���Ҷ�������Ԫ��
    TreeNode* search(TreeNode *root, int value);

    // �������ʱ, ��������������ڽڵ������ֵ
    int inOrderMaxDiff(TreeNode *root, int & maxDiff, int lastValue = 0);

public:
    TreeNode *root = nullptr;
};

