#include <iostream>
#include <memory>

using namespace std;

struct Node {
    int key;
    std::weak_ptr<Node> parent;
    std::shared_ptr<Node> left;
    std::shared_ptr<Node> right;

    Node(int key) : key(key), left(nullptr), right(nullptr) {};
    ~Node(){};
};

using node_ptr = shared_ptr<Node>;

class SplayTree {
    private:
        node_ptr root;
        
        void zig(node_ptr);
        void zag(node_ptr);
        void zig_zig(node_ptr);
        void zig_zag(node_ptr);
        void zag_zag(node_ptr);
        void zag_zig(node_ptr);

        void splay(shared_ptr<Node>);
    
    public:
        SplayTree() : root(nullptr) {};
        SplayTree(node_ptr tree) : root(tree) {};

        void insert(int key);
        bool search(int key);
};

void SplayTree::zig(node_ptr x) {// Zig
    node_ptr y = x->parent.lock();
    // Node* A = x->left;
    node_ptr B = x->right;
    // Node* C = y->right;
    x->parent.reset();
    x->right = y;
    y->left = B;
    y->parent = x;
    if (B != nullptr) B->parent = y;
}
void SplayTree::zag(node_ptr x) {
    node_ptr y = x->parent.lock();
    // Node* A = y->left;
    node_ptr B = x->left;
    // Node* C = x->right;
    x->parent.reset();
    x->left = y;
    y->right = B;
    y->parent = x;
    if (B != nullptr) B->parent = y;
}

void SplayTree::zig_zig(node_ptr x) {
    node_ptr y = x->parent.lock();
    node_ptr z = y->parent.lock();
    node_ptr B = x->right;
    node_ptr C = y->right;
    if (node_ptr p = z->parent.lock()) {
        x->parent = (weak_ptr<Node>) p;
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

void SplayTree::zig_zag(node_ptr x) {
    node_ptr y = x->parent.lock();
    node_ptr z = y->parent.lock();
    node_ptr B = x->left;
    node_ptr C = x->right;
    if (node_ptr p = z->parent.lock()) {
        x->parent = (weak_ptr<Node>) p;
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

void SplayTree::zag_zag(node_ptr x) {
    node_ptr y = x->parent.lock();
    node_ptr z = y->parent.lock();
    node_ptr B = y->left;
    node_ptr C = x->left;
    if (node_ptr p = z->parent.lock()) {
        x->parent = (weak_ptr<Node>) p;
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

void SplayTree::zag_zig(node_ptr x) {
    node_ptr y = x->parent.lock();
    node_ptr z = y->parent.lock();
    node_ptr B = x->left;
    node_ptr C = x->right;
    if (node_ptr p = z->parent.lock()) {
        x->parent = (weak_ptr<Node>) p;
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

void SplayTree::splay(shared_ptr<Node> x) {
    while (node_ptr y = x->parent.lock()) {
        if (node_ptr z = y->parent.lock()) {
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
        this->root = make_shared<Node>(Node(key));
        return;
    }
    shared_ptr<Node> at = this->root;
    while (at != nullptr) {
        if (key < at->key) {
            if (at->left == nullptr) {
                at->left = make_shared<Node>(Node(key));
                at->left->parent = (weak_ptr<Node>) at;
                splay(at->left);
                return;
            }
            else at = at->left;
        }
        else if (key > at->key) {
            if (at->right == nullptr) {
                at->right = make_shared<Node>(Node(key));
                at->right->parent = (weak_ptr<Node>) at;
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
    node_ptr ret = nullptr;
    node_ptr at = this -> root;
    node_ptr prev = nullptr;
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

int main() {
    // SplayTree Testing
    cout << "\nTesting SplayTree:\n";
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
    cout << "\tSearch 30: " << (tree.search(30) ? "Found" : "Not Found") << endl;
    cout << "\tSearch 100: " << (tree.search(100) ? "Found" : "Not Found") << endl;

    return 0;
}