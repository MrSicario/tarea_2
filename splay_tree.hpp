#pragma once
#include <iostream>
#include <memory>

namespace splayTree {
    struct Node {
        int key;
        std::weak_ptr<Node> parent;
        std::shared_ptr<Node> left;
        std::shared_ptr<Node> right;

        Node(int key) : key(key), left(nullptr), right(nullptr) {};
        ~Node(){};
    };

    class SplayTree {
        private:
            std::shared_ptr<Node> root;
            
            void zig(std::shared_ptr<Node>);
            void zag(std::shared_ptr<Node>);
            void zig_zig(std::shared_ptr<Node>);
            void zig_zag(std::shared_ptr<Node>);
            void zag_zag(std::shared_ptr<Node>);
            void zag_zig(std::shared_ptr<Node>);

            void splay(std::shared_ptr<Node>);
        
        public:
            SplayTree() : root(nullptr) {};
            SplayTree(std::shared_ptr<Node> tree) : root(tree) {};

            void insert(int key);
            bool search(int key);
    };

    void SplayTree::zig(std::shared_ptr<Node> x) {// Zig
        std::shared_ptr<Node> y = x->parent.lock();
        // Node* A = x->left;
        std::shared_ptr<Node> B = x->right;
        // Node* C = y->right;
        x->parent.reset();
        x->right = y;
        y->left = B;
        y->parent = x;
        if (B != nullptr) B->parent = y;
    }

    void SplayTree::zag(std::shared_ptr<Node> x) {
        std::shared_ptr<Node> y = x->parent.lock();
        // Node* A = y->left;
        std::shared_ptr<Node> B = x->left;
        // Node* C = x->right;
        x->parent.reset();
        x->left = y;
        y->right = B;
        y->parent = x;
        if (B != nullptr) B->parent = y;
    }

    void SplayTree::zig_zig(std::shared_ptr<Node> x) {
        std::shared_ptr<Node> y = x->parent.lock();
        std::shared_ptr<Node> z = y->parent.lock();
        std::shared_ptr<Node> B = x->right;
        std::shared_ptr<Node> C = y->right;
        if (std::shared_ptr<Node> p = z->parent.lock()) {
            x->parent = (std::weak_ptr<Node>) p;
            if (p->left == z) p->left = x;
            else p->right = x;
        } else x->parent.reset();
        x->right = y;
        y->left = B;
        y->right = z;
        y->parent = x;
        z->left = C;
        z->parent = y;
        if (B != nullptr) B->parent = y;
        if (C != nullptr) C->parent = z;
    }

    void SplayTree::zig_zag(std::shared_ptr<Node> x) {
        std::shared_ptr<Node> y = x->parent.lock();
        std::shared_ptr<Node> z = y->parent.lock();
        std::shared_ptr<Node> B = x->left;
        std::shared_ptr<Node> C = x->right;
        if (std::shared_ptr<Node> p = z->parent.lock()) {
            x->parent = (std::weak_ptr<Node>) p;
            if (p->left == z) p->left = x;
            else p->right = x;
        } else x->parent.reset();
        x->right = z;
        x->left = y;
        y->right = B;
        y->parent = x;
        z->left = C;
        z->parent = x;
        if (B != nullptr) B->parent = y;
        if (C != nullptr) C->parent = z;
    }

    void SplayTree::zag_zag(std::shared_ptr<Node> x) {
        std::shared_ptr<Node> y = x->parent.lock();
        std::shared_ptr<Node> z = y->parent.lock();
        std::shared_ptr<Node> B = y->left;
        std::shared_ptr<Node> C = x->left;
        if (std::shared_ptr<Node> p = z->parent.lock()) {
            x->parent = (std::weak_ptr<Node>) p;
            if (p->left == z) p->left = x;
            else p->right = x;
        } else x->parent.reset();
        x->left = y;
        y->right = C;
        y->left = z;
        y->parent = x;
        z->right = B;
        z->parent = y;
        if (B != nullptr) B->parent = z;
        if (C != nullptr) C->parent = y;
    }

    void SplayTree::zag_zig(std::shared_ptr<Node> x) {
        std::shared_ptr<Node> y = x->parent.lock();
        std::shared_ptr<Node> z = y->parent.lock();
        std::shared_ptr<Node> B = x->left;
        std::shared_ptr<Node> C = x->right;
        if (std::shared_ptr<Node> p = z->parent.lock()) {
            x->parent = (std::weak_ptr<Node>) p;
            if (p->left == z) p->left = x;
            else p->right = x;
        } else x->parent.reset();
        x->left = z;
        x->right = y;
        y->left = C;
        y->parent = x;
        z->right = B;
        z->parent = x;
        if (C != nullptr) C->parent = y;
        if (B != nullptr) B->parent = z;
    }

    void SplayTree::splay(std::shared_ptr<Node> x) {
        while (std::shared_ptr<Node> y = x->parent.lock()) {
            if (std::shared_ptr<Node> z = y->parent.lock()) {
                if (z->left == y && y->left == x) zig_zig(x);
                else if (z->left == y && y->right == x) zig_zag(x);
                else if (z->right == y && y->left == x) zag_zig(x);
                else if (z->right == y && y->right == x) zag_zag(x);
            } 
            else if (y->left == x) zig(x);
            else zag(x);
        }
        this->root = x;
    }

    void SplayTree::insert(int key) {
        if (this->root == nullptr) {
            this->root = std::make_shared<Node>(Node(key));
            return;
        }
        std::shared_ptr<Node> at = this->root;
        while (at != nullptr) {
            if (key < at->key) {
                if (at->left == nullptr) {
                    at->left = std::make_shared<Node>(Node(key));
                    at->left->parent = (std::weak_ptr<Node>) at;
                    splay(at->left);
                    return;
                }
                else at = at->left;
            }
            else if (key > at->key) {
                if (at->right == nullptr) {
                    at->right = std::make_shared<Node>(Node(key));
                    at->right->parent = (std::weak_ptr<Node>) at;
                    splay(at->right);
                    return;
                }
                else at = at->right;
            }
            else {
                splay(at);
                return;
            }
        }
    }

    bool SplayTree::search(int key) {
        std::shared_ptr<Node> ret = nullptr;
        std::shared_ptr<Node> at = this -> root;
        std::shared_ptr<Node> prev = nullptr;
        while (at != nullptr)
        {
            prev = at;
            if (key < at->key) at = at -> left;
            else if (key > at->key) at = at -> right;
            else
            {
                ret = at;
                break;
            }
        }
        if (ret != nullptr) {
            splay(ret);
            return true;
        }
        else if (prev != nullptr) splay(prev);
        return false;
    }

    int test_splayTree() {
        // SplayTree Testing
        std::cout << "\nTesting SplayTree:\n";
        SplayTree tree;

        // Insert values
        tree.insert(50);
        tree.insert(30);
        tree.insert(70);
        tree.insert(20);
        tree.insert(40);
        tree.insert(60);
        tree.insert(80);

        // Search for some values
        std::cout << "\tSearch 30: " << (tree.search(30) ? "Found" : "Not Found") << std::endl;
        std::cout << "\tSearch 100: " << (tree.search(100) ? "Found" : "Not Found") << std::endl;

        return 0;
    }
}