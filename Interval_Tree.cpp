#include <iostream>
#include <vector>
#include <fstream>
#include <queue>

template <typename T>
class IntervalTree
{
private:
    enum Color {
        Red = 0,
        Black = 1
    };
public:
    struct IntervalTreeNode {
        T low, high, max;
        IntervalTreeNode* left;
        IntervalTreeNode* right;
        IntervalTreeNode* parent;
        bool color;
    };
private:
    IntervalTreeNode* root;
    IntervalTreeNode* nil;

public:
    IntervalTree() {
        nil = new IntervalTreeNode;
        nil->color = Black;
        nil->left = nil->right = nil->parent = nullptr;
        nil->low = nil->high = nil->max = 0;
        root = nil;
    }

    IntervalTreeNode* getRoot() {
        return root;
    }

    void insertInterval(T low, T high) {
        IntervalTreeNode* z = new IntervalTreeNode{low, high, high, nil, nil, nil, Red};
        IntervalTreeInsert(z);
    }

    void IntervalTreeInsert(IntervalTreeNode* z) {
        IntervalTreeNode* y = nil;
        IntervalTreeNode* x = root;
        while (x != nil) {
            y = x;
            if (z->low < x->low) {
                x = x->left;
            } else {
                x = x->right;
            }
        }
        z->parent = y;
        if (y == nil) {
            root = z;
        } else if (z->low < y->low) {
            y->left = z;
        } else {
            y->right = z;
        }
        z->left = nil;
        z->right = nil;
        z->color = Red;
        IntervalInsertFixup(z);
        updateMax(z);
    }

    void IntervalInsertFixup(IntervalTreeNode* z) {
        while (z->parent->color == Red) {
            if (z->parent == z->parent->parent->left) {
                IntervalTreeNode* y = z->parent->parent->right;
                if (y->color == Red) {
                    z->parent->color = Black;
                    y->color = Black;
                    z->parent->parent->color = Red;
                    z = z->parent->parent;
                } else {
                    if (z == z->parent->right) {
                        z = z->parent;
                        LeftRotate(z);
                    }
                    z->parent->color = Black;
                    z->parent->parent->color = Red;
                    RightRotate(z->parent->parent);
                }
            } else {
                IntervalTreeNode* y = z->parent->parent->left;
                if (y->color == Red) {
                    z->parent->color = Black;
                    y->color = Black;
                    z->parent->parent->color = Red;
                    z = z->parent->parent;
                } else {
                    if (z == z->parent->left) {
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

    void LeftRotate(IntervalTreeNode* x) {
        IntervalTreeNode* y = x->right;
        x->right = y->left;
        if (y->left != nil) {
            y->left->parent = x;
        }
        y->parent = x->parent;
        if (x->parent == nil) {
            root = y;
        } else if (x == x->parent->left) {
            x->parent->left = y;
        } else {
            x->parent->right = y;
        }
        y->left = x;
        x->parent = y;
        updateMax(x);
        updateMax(y);
    }

    void RightRotate(IntervalTreeNode* y) {
        IntervalTreeNode* x = y->left;
        y->left = x->right;
        if (x->right != nil) {
            x->right->parent = y;
        }
        x->parent = y->parent;
        if (y->parent == nil) {
            root = x;
        } else if (y == y->parent->right) {
            y->parent->right = x;
        } else {
            y->parent->left = x;
        }
        x->right = y;
        y->parent = x;
        updateMax(y);
        updateMax(x);
    }

    void updateMax(IntervalTreeNode* node) {
        while (node != nil) {
            node->max = std::max(node->high, std::max(node->left->max, node->right->max));
            node = node->parent;
        }
    }

    bool doOverlap(T low1, T high1, T low2, T high2) {
        return (low1 <= high2 && low2 <= high1);
    }

    void intervalSearchAll(IntervalTreeNode* node, T low, T high, std::vector<IntervalTreeNode*>& result) {
        if (node == nil) return;

        if (doOverlap(low, high, node->low, node->high)) {
            result.push_back(node);
        }

        if (node->left != nil && node->left->max >= low) {
            intervalSearchAll(node->left, low, high, result);
        }

        intervalSearchAll(node->right, low, high, result);
    }

    void PreOrderTraversal(IntervalTreeNode* node) {
        if (node != nil) {
            std::cout << "[" << node->low << ", " << node->high << "] ";
            PreOrderTraversal(node->left);
            PreOrderTraversal(node->right);
        }
    }
};

int main() {
    std::ifstream infile("");
    int size;
    infile >> size;
    std::vector<std::pair<int, int>> intervals(size);
    for (int i = 0; i < size; ++i) {
        infile >> intervals[i].first >> intervals[i].second;
    }

    IntervalTree<int> tree;
    for (const auto& interval : intervals) {
        tree.insertInterval(interval.first, interval.second);
    }

    int low, high;
    std::cout << "Enter interval to search (low high): ";
    std::cin >> low >> high;
    std::vector<IntervalTree<int>::IntervalTreeNode*> result;
    tree.intervalSearchAll(tree.getRoot(), low, high, result);
    if (!result.empty()) {
        std::cout << "Overlapping intervals found: ";
        for (const auto& node : result) {
            std::cout << "[" << node->low << ", " << node->high << "] ";
        }
        std::cout << std::endl;
    } else {
        std::cout << "No overlapping intervals found." << std::endl;
    }
    system("pause");
    return 0;
}