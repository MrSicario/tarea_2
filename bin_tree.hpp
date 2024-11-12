#pragma once
#include <memory>
#include <stack>

namespace binTree {
    struct Node;
    class BinTree {
        private:
            std::shared_ptr<Node> root;
            std::stack<std::shared_ptr<Node>> stack;
        public:
            BinTree() : root(nullptr) {};
            ~BinTree();
            void insert(int key);
            bool search(int target);
    };
}