#include <iostream>
#include <memory>
#include "bin_tree.hpp"

namespace binTree {
    struct Node {
        int key;
        std::shared_ptr<Node> left;
        std::shared_ptr<Node> right;

        Node(int key) : key(key), left(nullptr), right(nullptr) {};
        ~Node(){};
    };
    /** 
     * 
     * Inserta la llave ingresada en el A.B.B.
     * 
     * Si la llave ya se encuentra en el A.B.B. no se inserta y termina la operación.
     * 
     * @param key Int a insertar en el A.B.B.
    */
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
                    return;
                }
                else at = at->left;
            }
            else if (key > at->key) {
                if (at->right == nullptr) {
                    at->right = std::make_shared<Node>(Node(key));
                    return;
                }
                else at = at->right;
            }
            else
                return;
        }
    }
    /**
     * 
     * Busca si la llave está en el A.B.B.
     * 
     * @param key Llave a buscar
     * @returns `true` si la llave se encuentra, `false` en caso contrario.
     */
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