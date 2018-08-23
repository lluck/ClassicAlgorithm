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

    // 已知前序和中序序列，构建二叉树
    static TreeNode* buildTreePreIn(int *preOrder, int* inOrder, int len);
    // 已知后序和中序序列，构建二叉树
    static TreeNode* buildTreePostIn(int *postOrder, int* inOrder, int len);

    // 释放节点及子结点
    static void free(TreeNode *p);


    // 前序遍历输出--递归
    void printPreOrder(TreeNode *root);
    // 前序遍历输出--非递归
    void printPreOrderIter(TreeNode *root);
    // 中序遍历输出--递归
    void printInOrder(TreeNode *root);
    // 中序遍历输出--非递归
    void printInOrderIter(TreeNode *root);
    // 后序遍历输出--递归
    void printPostOrder(TreeNode *root);
    // 后序遍历输出--非递归
    void printPostOrderIter(TreeNode *root);

    // 层级输出
    void printTree(TreeNode *p = nullptr);

    void insert(TreeNode * & root, int value);


    // 两个节点的最近公共祖先
    TreeNode* getNearestAncestor(TreeNode *root, TreeNode *fir, TreeNode *sec);

    // 二叉树的宽度, 二叉树各层节点个数的最大值
    int width(TreeNode *root);

    // 二叉树的高度, 叶子节点的最大深度值
    int height(TreeNode *root);

    // 查找二叉树中元素
    TreeNode* search(TreeNode *root, int value);

    // 中序遍历时, 排序二叉树的相邻节点的最大差值
    int inOrderMaxDiff(TreeNode *root, int & maxDiff, int lastValue = 0);

public:
    TreeNode *root = nullptr;
};

