#include <iostream>
#include <array>
#include <string>
using namespace std;

class Node {
public:
    bool is_end;
    array<Node*, 128> children;
    Node() {
        is_end = false;
        for (Node*& child: children) {
            child = nullptr;
        }
        return;
    }
};

class Trie {
public:
    Node* root;
    
    Trie() {
        root = new Node;
    }

    void insert(const string& s) {
        Node* node = root;
        for (const char& c: s) {
            if (node->children[c] == nullptr) {
                node->children[c] = new Node;
            }
            node = node->children[c];
        }
        node->is_end = true;
        return;
    }
    
    bool exist(const string& s) {
        Node* node = root;
        for (const char& c: s) {
            if (node->children[c] == nullptr) {
                return false;
            }
            node = node->children[c];
        }
        if (node->is_end) {
            return true;
        } else {
            return false;
        }
    }

    void remove(const string& s) {
        Node* node = root;
        for (const char& c: s) {
            if (node->children[c] == nullptr) {
                return;
            }
            node = node->children[c];
        }
        node->is_end = false;
        return;
    }
};

int main() {
    Trie trie;
    const array<string, 8> strings = {"A", "to", "tea", "ted", "ten", "i", "in", "inn"};

    for (const string& str: strings) {
        trie.insert(str);
    }
    
    const array<string, 4> queries = {"A", "B", "te", "in"};
    for (const string& query: queries) {
        cout << query << (trie.exist(query) ? " exists." : " do not exists.") << endl;
    }

    return 0;
}
