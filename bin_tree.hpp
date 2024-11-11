#pragma once

namespace binTree {
    struct Node;
    class BinTree {
        private:
            std::shared_ptr<Node> root;
        public:
            BinTree() : root(nullptr) {};
            void insert(int key);
            bool search(int target);
    };
}