#pragma once
#include <iostream>
#include <memory>

namespace bt {
    struct Node {
        int key;
        std::weak_ptr<Node> parent;
        std::shared_ptr<Node> left;
        std::shared_ptr<Node> right;

        Node(int key) : key(key), left(nullptr), right(nullptr) {};
        ~Node(){};
    };

    class BinTree {
        private:
            std::shared_ptr<Node> root;
        public:
            BinTree() : root(nullptr) {};
            void insert(int key);
            bool search(int target);
    };

    void BinTree::insert(int key) {
        if (this->root == nullptr) {
            this->root = std::make_shared<Node>(Node(key));
            return;
        }
        std::shared_ptr<Node> at = this->root;
        while (at != nullptr) {
            if (key < at->key) {
                if (at->left == nullptr) {
                    at->left = std::make_shared<Node>(Node(key));
                    at->left->parent = at;
                    return;
                }
                else at = at->left;
            }
            else if (key > at->key) {
                if (at->right == nullptr) {
                    at->right = std::make_shared<Node>(Node(key));
                    at->right->parent = at;
                    return;
                }
                else at = at->right;
            }
            else
                return;
        }
    }

    bool BinTree::search(int key) {
        std::shared_ptr<Node> at = this->root;
        while (at != nullptr) {
            if (at->key == key)
                return true;
            else if (key < at->key)
                at = at->left;
            else if (key > at->key)
                at = at->right;
        }
        return false;
    }

    int test_binTree() {
        // BinTree Testing
        std::cout << "Testing BinTree:\n";
        BinTree binTree;

        // Insert values
        binTree.insert(50);
        binTree.insert(30);
        binTree.insert(70);
        binTree.insert(20);
        binTree.insert(40);
        binTree.insert(60);
        binTree.insert(80);

        // Search for some values
        std::cout << "\tSearch 30: " << (binTree.search(30) ? "Found" : "Not Found") << std::endl;
        std::cout << "\tSearch 100: " << (binTree.search(100) ? "Found" : "Not Found") << std::endl;

        return 0;
    }
}