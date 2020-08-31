#include <iostream>
#include <array>
using namespace std;

template <typename T>
class BSNode {
public:
    T value;
    BSNode* left;
    BSNode* right;
    BSNode(T val) {
        this->left = nullptr;
        this->right = nullptr;
        this->value = val;
        return;
    }
};

template <typename T>
class BSTree {
public:
    // Make real root node being left child of dummy node.
    BSNode<T>* dummy;
    
    BSTree() {
        dummy = new BSNode<T>(0);
    }

    void insert(T val) {
        BSNode<T> **dptr = find_helper(val);
        if (*dptr == nullptr) {
            *dptr = new BSNode<T>(val);
        } else {
            // skip, because already exists
        }
        return;
    }
    
    BSNode<T>* find(T val) {
        return *find_helper(val);
    }

    void remove(T val) {
        BSNode<T> **dptr = find_helper(val);
        if (*dptr != nullptr) {
            if (((*dptr)->left != nullptr) && ((*dptr)->right != nullptr)) {
                // find smallest value in right sub-tree
                BSNode<T> **dptr_min = &((*dptr)->right);
                while ((*dptr_min)->left != nullptr) {
                    dptr_min = &((*dptr_min)->left);
                }
                // connect min's parent and min's subtree
                *dptr_min = (*dptr_min)->right;
                // swap *dptr and min
                (*dptr_min)->left = (*dptr)->left;
                (*dptr_min)->right = (*dptr)->right;
                delete *dptr;
                *dptr = *dptr_min;
            } else if ((*dptr)->left == nullptr) {
                BSNode<T> *temp = (*dptr)->right;
                delete *dptr;
                *dptr = temp;
            } else if ((*dptr)->right == nullptr) {
                BSNode<T> *temp = (*dptr)->left;
                delete *dptr;
                *dptr = temp;                 
            } else {
                delete *dptr;
            }
        }
        return;
    }

private:
    // Return a double pointer that where should the node resides relative to its parent
    BSNode<T>** find_helper(T val) {
        BSNode<T>** ret = &(dummy->left);
        while (*ret != nullptr) {
            if ((*ret)->value == val) break;
            else if (val < (*ret)->value) {
                ret = &((*ret)->left);
            } else {
                ret = &((*ret)->right);
            }
        }
        return ret;
    }
};

int main() {
    BSTree<int> tree;
    array<int, 10> a = {1, 4, 3, 5, 8, 0, 9, 2, 7, 6};

    for (int i: a) {
        tree.insert(i);
    }
    for (int d = 0; d < 10; d++) {
        cout << "Delete " << d << endl;
        tree.remove(d);
        for (int i = 0; i < 10; i++) {
            cout << "\t" << i;
            if (tree.find(i) == nullptr) {
                cout << " do not exists." << endl;
            } else {
                cout << " exists!" << endl;
            }
        }
    }

    return 0;
}
