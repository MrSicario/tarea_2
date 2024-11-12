#pragma once
#include <memory>
#include <stack>

namespace splayTree {
    struct Node;
    class SplayTree {
        private:
            std::shared_ptr<Node> root;
            std::stack<std::shared_ptr<Node>> stck;
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
            ~SplayTree();
            void insert(int key);
            bool search(int key);
    };
}