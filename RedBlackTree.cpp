#include <iostream>
#include <vector>
#include <time.h>
#include <algorithm>
#include <list>

template <typename T>
class RedBlackTree
{
private:
    enum Color {
        Red = 0,
        Black = 1
    };
    struct RedBlackTreeNode {
        T key;
        RedBlackTreeNode* left;
        RedBlackTreeNode* right;
        RedBlackTreeNode* parent;
        bool color;
    };
    RedBlackTreeNode* root;
    RedBlackTreeNode* nil;
public:
    RedBlackTree(/* args */);
    ~RedBlackTree();
    void RedBlackTreeInit(T key)
    {
        nil->color = Black;
        nil->left = root;
        nil->right = root;
        root->parent = nil;
        root->color = Black;
        root->left = nil;
        root->right = nil;
        root->key = key;
    }
    void LeftRotate(RedBlackTreeNode* x)
    {
        auto y = x->right;//set y
        x->right = y->left;
        if (y->left != nil)
        {
            y->left->parent = x;
        }
        y->parent = x->parent;
        if (x->parent == nil)
        {
            root = y;
        }
        else if (x == x->parent->left)
        {
            x->parent->left = y;
        }
        else
        {
            x->parent->right = y;
        }
    }
    void Rightrotate(RedBlackTreeNode* y)
    {
        auto x = y->left;//set x
        y->left = x->right;
        if (x->right != nil)
        {
            x->right->parent = y;
        }
        x->parent = y->parent;
        if (y->parent == nil)
        {
            root = x;
        }
        else if (y == y->parent->right)
        {
            y->parent->right = x;
        }
        else
        {
            y->parent->left = x;
        }
        x.right = y;
        y->parent = x;
    }
    void RedBlackTreeInsert(RedBlackTree* root, T key)
    {
        RedBlackTreeNode* z;
        z->key = key;
        z->left = nil;
        z->right = nil;
        auto y = nil;
        auto x = root;
        while (x != nil)
        {
            y = x;
            if (z->key < x->key)
            {
                x = x->left;
            }
            else
            {
                x = x->right;
            }
        }
        z->parent = y;
        if (y == nil)
        {
            root = z;
        }
        else if (z->key < y->key)
        {
            y->left = z;
        }
        else
        {
            y->right = z;
        }
        z->left = nil;
        z->right = nil;
        z->color = Red;
        RedBlackTreeInsertFixup(root, z);
    }
    void RedBlackFixup(RedBlackTreeNode *root, RedBlackTreeNode *z)
    {
        while (z->parent->color == Red)
        {
            if (z->parent == z->parent->parent->left)
            {
                auto y = z->parent->parent->right;
                if (y->color == Red)
                {
                    z->parent->color = Black;//case 1
                    y->color = Black;
                    z->parent->parent->color = Red;
                    z = z->parent->parent;
                }
                else
                {
                    if (z == z->parent->right)
                    {
                        z = z->parent;
                        LeftRotate(z);
                    }
                    z->parent->color = Black;
                    z->parent->parent->color = Red;
                    RightRotate(z->parent->parent);
                }
            }
            else
            {
                auto y = z->parent->parent->left;
                if (y->color == Red)
                {
                    z->parent->color = Black;
                    y->color = Black;
                    z->parent->parent->color = Red;
                    z = z->parent->parent;
                }
                else
                {
                    if (z == z->parent->left)
                    {
                        z = z->parent;
                        RightRotate(z);
                    }
                    z->parent->color = Black;
                    z->parent->parent->color = Red;
                    LeftRotate(z->parent->parent);
                }
            }
        }
        root->color = Black;
    }
    

};
