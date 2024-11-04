#include <iostream>
#include <memory>

using namespace std;

struct Node {
    int key;
    std::shared_ptr<Node> parent;
    std::weak_ptr<Node> left;
    std::weak_ptr<Node> right;

    Node(int key) : key(key), parent(nullptr), left(weak_ptr<Node>()), right(weak_ptr<Node>()) {};
    ~Node(){};
};

class BinTree {
    private:
        shared_ptr<Node> root;
    public:
        BinTree() : root(nullptr) {};
        void insert(int key);
        bool search(int target);
};

void BinTree::insert(int key) {
    if (this->root == nullptr) {
        shared_ptr<Node> new_node = make_shared<Node>(Node(key));
        this->root = new_node;
        return;
    }
    shared_ptr<Node> at = this->root;
    while (at != nullptr) {
        if (key < at->key) {
            if (at->left.expired()) {
                shared_ptr<Node> new_node = make_shared<Node>(Node(key));
                new_node->parent = at;
                at->left = new_node;
                return;
            }
            else at = at->left.lock();
        }
        else if (key > at->key) {
            if (at->right.expired()) {
                shared_ptr<Node> new_node = make_shared<Node>(Node(key));
                new_node->parent = at;
                at->right = new_node;
                return;
            }
            else at = at->right.lock();
        }
        else
            return;
    }
}

bool BinTree::search(int key) {
    shared_ptr<Node> at = this->root;
    while (at != nullptr) {
        if (at->key == key)
            return true;
        else if (key < at->key)
            at = at->left.lock();
        else if (key > at->key)
            at = at->right.lock();
    }
    return false;
}

class SplayTree {
    private:
        shared_ptr<Node> root;
        
        void zig(shared_ptr<Node>);
        void zig_zig(shared_ptr<Node>);
        void zig_zag(shared_ptr<Node>);

        void splay(shared_ptr<Node>);
    
    public:
        SplayTree() : root(nullptr) {};
        SplayTree(shared_ptr<Node> tree) : root(tree) {};

        void insert(int val);
        bool search(int val);
};

void SplayTree::zig(shared_ptr<Node> x) {// Zig || Zag
    shared_ptr<Node> y = x->parent;
    if (y->left.lock() == x) {// Zig
        // Node* A = x->left;
        shared_ptr<Node> B = x->right.lock();
        // Node* C = y->right;
        x->parent = nullptr;
        x->right = y;
        y->parent = x;
        y->left = B;
        if (B != nullptr) B->parent = y;
    }
    else {// Zag
        // Node* A = y->left;
        shared_ptr<Node> B = x->left.lock();
        // Node* C = x->right;
        x->parent = nullptr;
        x->left = y;
        y->parent = x;
        y->right = B;
        if (B != nullptr) B->parent = y;
    }
}

void SplayTree::zig_zig(shared_ptr<Node> x) {// Zig-zig || Zag-zag
    shared_ptr<Node> y = x->parent;
    shared_ptr<Node> z = y->parent;
    if (y->left.lock() == x) {// Zig-zig
        // Node* A = x->left;
        shared_ptr<Node> B = x->right.lock();
        shared_ptr<Node> C = y->right.lock();
        // Node* D = z->right;

        x->parent = z->parent;
        x->right = y;

        y->parent = x;
        y->left = B;
        y->right = z;

        z->parent = y;
        z->left = C;

        if (x->parent != nullptr) {
            if (x->parent->left.lock() == z) x->parent->left = x;
            else x->parent->right = x;
        }

        if (B != nullptr) B->parent = y;
        if (C != nullptr) C->parent = z;
    } else {// Zag-zag
        //Node* A = z->left;
        shared_ptr<Node> B = y->left.lock();
        shared_ptr<Node> C = x->left.lock();
        //Node* D = x->right;

        x->parent = z->parent;
        x->left = y;

        y->parent = x;
        y->right = z;
        y->left = C;

        z->parent = y;
        z->right = B;

        if (x->parent != nullptr) {
            if (x->parent->left.lock() == z) x->parent->left = x;
            else x->parent->right = x;
        }

        if (B != nullptr) B->parent = z;
        if (C != nullptr) C->parent = y;
    }
}

void SplayTree::zig_zag(shared_ptr<Node> x) {// Zig-zag || Zag-zig
    shared_ptr<Node> y = x->parent;
    shared_ptr<Node> z = y->parent;
    if (y->right.lock() == x) {// Zig-zag
        //Node* A = y->left;
        shared_ptr<Node> B = x->left.lock();
        shared_ptr<Node> C = x->right.lock();
        //Node* D = z-> right;

        x->parent = z->parent;
        x->right = y;
        x->left = z;

        y->parent = x;
        y->right = B;

        z->parent = x;
        z->left = C;

        if (x->parent != nullptr) {
            if (x->parent->left.lock() == z) x->parent->left = x;
            else x->parent->right = x;
        }

        if (B != nullptr) B->parent = y;
        if (C != nullptr) C->parent = z;
    } else {// Zag-zig
        //shared_ptr<Node> A = z->left;
        shared_ptr<Node> B = x->left.lock();
        shared_ptr<Node> C = x->right.lock();
        //shared_ptr<Node> D = y->right;

        x->parent = z->parent;
        x->left = z;
        x->right = y;

        y->parent = x;
        y->left = C;

        z->parent = x;
        z->right = B;

        if (x->parent != nullptr) {
            if (x->parent->left.lock() == z) x->parent->left = x;
            else x->parent->right = x;
        }

        if (B != nullptr) B->parent = z;
        if (C != nullptr) C->parent = y;
    }
}

void SplayTree::splay(shared_ptr<Node> x) {
    while (x->parent != nullptr) {
        shared_ptr<Node> y = x->parent;
        shared_ptr<Node> z = y->parent;
        if (z == nullptr) zig(x);
        else if (z->left.lock() == y && y->left.lock() == x) zig_zig(x);
        else if (z->right.lock() == y && y->right.lock() == x) zig_zig(x);
        else zig_zag(x);
    }
    this->root = x;
}

void SplayTree::insert(int key) {
    if (this->root == nullptr) {
        shared_ptr<Node> new_node (new Node(key));
        this->root = new_node;
        return;
    }
    shared_ptr<Node> at = this->root;
    while (at != nullptr) {
        if (key < at->key) {
            if (at->left.lock() == nullptr) {
                shared_ptr<Node> new_node (new Node(key));
                new_node->parent = at;
                at->left = new_node;
                splay(new_node);
                return;
            }
            else at = at->left.lock();
        }
        else if (key > at->key) {
            if (at->right.lock() == nullptr) {
                shared_ptr<Node> new_node (new Node(key));
                new_node->parent = at;
                at->right = new_node;
                splay(new_node);
                return;
            }
            else at = at->right.lock();
        }
        else {
            splay(at);
            return;
        }
    }
}

bool SplayTree::search(int key) {
    shared_ptr<Node> ret = nullptr;
    shared_ptr<Node> prev = nullptr;
    shared_ptr<Node> at = this->root;
    while (at != nullptr) {
        prev = at;
        if (at->key == key) {
            ret = at;
            break;
        }
        else if (key < at->key)
            at = at->left.lock();
        else if (key > at->key)
            at = at->right.lock();
    }
    if (ret!=nullptr) {
        splay(ret);
        return true;
    
    } else if (prev!=nullptr)
        splay(prev);
    return false;
}

int main() {
    // _Tree Testing
    BinTree tree;

    // Insert values
    tree.insert(50);
    tree.insert(30);
    tree.insert(70);
    tree.insert(20);
    tree.insert(40);
    tree.insert(60);
    tree.insert(80);

    // Search for some values
    cout << "Search 30: " << (tree.search(30) ? "Found" : "Not Found") << endl;
    cout << "Search 100: " << (tree.search(100) ? "Found" : "Not Found") << endl;

    return 0;
}