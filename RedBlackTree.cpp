#include <iostream>
#include <vector>
#include <time.h>
#include <algorithm>
#include <list>
#include <fstream>
#include <queue>

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
    RedBlackTreeNode* getRoot() {
        return root;
    }
    std::vector<int> insertAndTrackCases(const std::vector<T>& data) {
        std::vector<int> cases;
        RedBlackTreeInit(data[0]);
        for (int i = 1; i < data.size(); i++) {
            RedBlackTreeNode* z = new RedBlackTreeNode{data[i], nil, nil, nil, Red};
            RedBlackTreeInsert(z, cases);
        }
        return cases;
    }
    void RedBlackTreeInit(T key)
    {
        nil = new RedBlackTreeNode;
        nil->color = Black;
        nil->parent = nullptr;
        root = new RedBlackTreeNode;
        root->parent = nil;
        root->color = Black;
        root->left = nil;
        root->right = nil;
        root->key = key;
        nil->left = root;
        nil->right = root;
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
        y->left = x;
        x->parent = y;
    }
    void RightRotate(RedBlackTreeNode* y)
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
        x->right = y;
        y->parent = x;
    }
    void RedBlackTreeInsert(RedBlackTreeNode* z, std::vector<int>& cases)
    {
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
        RedBlackInsertFixup(z);
    }
    void RedBlackInsertFixup(RedBlackTreeNode *z)
    {
        while (z->parent->color == Red)
        {
            if (z->parent == z->parent->parent->left)
            {
                auto y = z->parent->parent->right;
                if (y->color == Red)
                {
                    std::cout << "case 1" << std::endl;
                    z->parent->color = Black;//case 1
                    y->color = Black;
                    z->parent->parent->color = Red;
                    z = z->parent->parent;
                }
                else
                {
                    if (z == z->parent->right)
                    {
                        std::cout << "case 2" << std::endl;
                        z = z->parent;//case 2
                        LeftRotate(z);
                    }
                    std::cout << "case 3" << std::endl;
                    z->parent->color = Black;//case 3
                    z->parent->parent->color = Red;
                    RightRotate(z->parent->parent);
                }
            }
            else
            {
                auto y = z->parent->parent->left;
                if (y->color == Red)
                {
                    std::cout << "case 4" << std::endl;
                    z->parent->color = Black;//case 4
                    y->color = Black;
                    z->parent->parent->color = Red;
                    z = z->parent->parent;
                }
                else
                {
                    if (z == z->parent->left)
                    {
                        std::cout << "case 5" << std::endl;
                        z = z->parent;//case 5
                        RightRotate(z);
                    }
                    std::cout << "case 6" << std::endl;
                    z->parent->color = Black;//case 6
                    z->parent->parent->color = Red;
                    LeftRotate(z->parent->parent);
                }
            }
        }
        root->color = Black;
    }
    void RedBlackTreeDelete(RedBlackTreeNode* z)
    {
        RedBlackTreeNode* y = z;
        RedBlackTreeNode* x;
        bool yOriginalColor = y->color;
        if (z->left == nil)
        {
            x = z->right;
            RedBlackTransplant(root, z, z->right);
        }
        else if (z->right == nil)
        {
            x = z->left;
            RedBlackTransplant(root, z, z->left);
        }
        else
        {
            y = RedBlackTreeMinimum(z->right);
            yOriginalColor = y->color;
            x = y->right;
            if (y->parent == z)
            {
                x->parent = y;
            }
            else
            {
                RedBlackTransplant(root, y, y->right);
                y->right = z->right;
                y->right->parent = y;
            }
            RedBlackTransplant(root, z, y);
            y->left = z->left;
            y->left->parent = y;
            y->color = z->color;
        }
        if (yOriginalColor == Black)
        {
            RedBlackDeleteFixup(root, x);
        }
    }
    void RedBlackTransplant(RedBlackTreeNode* u, RedBlackTreeNode* v)
    {
        if (u->parent == nil)
        {
            root = v;
        }
        else if (u == u->parent->left)
        {
            u->parent->left = v;
        }
        else
        {
            u->parent->right = v;
        }
        v->parent = u->parent;
    }
    RedBlackTreeNode* RedBlackTreeMinimum(RedBlackTreeNode* x)
    {
        while (x->left != nil)
        {
            x = x->left;
        }
        return x;
    }
    void RedBlackDeleteFixup(RedBlackTreeNode* x)//Delete fixup
    {
        while (x!= root && x->color == Black)
        {
            if (x == x->parent->left)
            {
                auto w = x->parent->right;
                if (w->color == Red)
                {
                    w->color = Black;
                    x->parent->color = Red;
                    LeftRotate(x->parent);
                    w = x->parent->right;
                }
                if (w->left->color == Black && w->right->color == Black)
                {
                    w->color = Red;
                    x = x->parent;
                }
                else
                {
                    if (w->right->color == Black)
                    {
                        w->left->color = Black;
                        w->color = Red;
                        RightRotate(w);
                        w = x->parent->right;
                    }
                    w->color = x->parent->color;
                    x->parent->color = Black;
                    w->right->color = Black;
                    LeftRotate(x->parent);
                    x = root;
                }
            }
            else
            {
                auto w = x->parent->left;
                if (w->color == Red)
                {
                    w->color = Black;
                    x->parent->color = Red;
                    RightRotate(x->parent);
                    w = x->parent->left;
                }
                if (w->right->color == Black && w->left->color == Black)
                {
                    w->color = Red;
                    x = x->parent;
                }
                else
                {
                    if (w->left->color == Black)
                    {
                        w->right->color = Black;
                        w->color = Red;
                        LeftRotate(w);
                        w = x->parent->left;
                    }
                    w->color = x->parent->color;
                    x->parent->color = Black;
                    w->left->color = Black;
                    RightRotate(x->parent);
                    x = root;
                }
            }
            x->color = Black;
        }
    }
    RedBlackTreeNode* RedBlackTreeSearch(RedBlackTreeNode* x, T key)//Find the node with key
    {
        if (x == key) return NULL;
        if (x->key == key)
        {
            return x;
        }
        if (key < x->key)
        {
            return RedBlackTreeSearch(x->left, key);
        }
        else
        {
            return RedBlackTreeSearch(x->right, key);
        }
    }
    void PreOrderTraversal(RedBlackTreeNode* node, std::ofstream& outFile) {//Traversal the tree with preorder
        if (node != nil) {
            std::cout << node->key << " ";
            outFile << node->key << " " << (node->color == Red ? "Red" : "Black") << std::endl;
            PreOrderTraversal(node->left, outFile);
            PreOrderTraversal(node->right, outFile);
        }
    }
    void InOrderTraversal(RedBlackTreeNode* node, std::ofstream& outFile) {//Traversal the tree with inorder
        if (node != nil) {
            InOrderTraversal(node->left, outFile);
            std::cout << node->key << " ";
            outFile << node->key << " " << (node->color == Red ? "Red" : "Black") << std::endl;
            InOrderTraversal(node->right, outFile);
        }
    }
    void LevelOrderTraversal(std::ofstream& outFile) {//Traversal the tree with level order
        if (root == nil) return;
        std::queue<RedBlackTreeNode*> q;
        q.push(root);
        while (!q.empty()) {
            RedBlackTreeNode* node = q.front();
            q.pop();
            outFile << node->key << " " << (node->color == Red ? "Red" : "Black") << std::endl;
            std::cout << node->key << " ";
            if (node->left != nil) q.push(node->left);
            if (node->right != nil) q.push(node->right);
        }
    }
};

int main() {
    std::ifstream infile("");
    int size;
    infile >> size;
    std::vector<int> nodes(size);
    for (int i = 0; i < size; ++i) {
        infile >> nodes[i];
    }

    RedBlackTree<int> tree;
    auto cases = tree.insertAndTrackCases(nodes);

    std::ofstream nlrFile("");
    std::ofstream lnrFile("");
    std::ofstream lotFile("");

    tree.PreOrderTraversal(tree.getRoot(), nlrFile);
    tree.InOrderTraversal(tree.getRoot(), lnrFile);
    tree.LevelOrderTraversal(lotFile);
    system("pause");
    return 0;
}


