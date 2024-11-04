#include <iostream>

using namespace std;

struct Node {
    int key;
    Node* root;
    Node* left;
    Node* right;

    Node(int key) : key(key), root(nullptr), left(nullptr), right(nullptr) {}
};

class BinTree {
    private:
        Node* root;
    public:
        BinTree() : root(nullptr) {};
        void insert(int key);
        bool search(int target);
};

void BinTree::insert(int key) {
    if (this->root == nullptr) {
        this->root = new Node(key);
        return;
    }
    Node* at = this->root;
    while (at != nullptr) {
        if (key < at->key) {
            if (at->left == nullptr) {
                Node* new_node = new Node(key);
                new_node->root = at;
                at->left = new_node;
                return;
            }
            else at = at->left;
        }
        else if (key > at->key) {
            if (at->right == nullptr) {
                Node* new_node = new Node(key);
                new_node->root = at;
                at->right = new_node;
                return;
            }
            else at = at->right;
        }
        else
            return;
    }
}

bool BinTree::search(int key) {
    Node* at = this->root;
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

class SplayTree {
    private:
        Node* root;
        
        void zig(Node*);
        void zig_zig(Node*);
        void zig_zag(Node*);

        void splay(Node*);
    
    public:
        SplayTree() : root(nullptr) {};
        SplayTree(Node* tree) : root(tree) {};

        void insert(int val);
        bool search(int val);
};

void SplayTree::zig(Node* x) {// Zig || Zag
    Node* y = x->root;
    if (y->left == x) {// Zig
        // Node* A = x->left;
        Node* B = x->right;
        // Node* C = y->right;
        x->root = nullptr;
        x->right = y;
        y->root = x;
        y->left = B;
        if (B != nullptr) B->root = y;
    }
    else {// Zag
        // Node* A = y->left;
        Node* B = x->left;
        // Node* C = x->right;
        x->root = nullptr;
        x->left = y;
        y->root = x;
        y->right = B;
        if (B != nullptr) B->root = y;
    }
}

void SplayTree::zig_zig(Node* x) {// Zig-zig || Zag-zag
    Node* y = x->root;
    Node* z = y->root;
    if (y->left == x) {// Zig-zig
        // Node* A = x->left;
        Node* B = x->right;
        Node* C = y->right;
        // Node* D = z->right;

        x->root = z->root;
        x->right = y;

        y->root = x;
        y->left = B;
        y->right = z;

        z->root = y;
        z->left = C;

        if (x->root != nullptr) {
            if (x->root->left == z) x->root->left = x;
            else x->root->right = x;
        }

        if (B != nullptr) B->root = y;
        if (C != nullptr) C->root = z;
    } else {// Zag-zag
        //Node* A = z->left;
        Node* B = y->left;
        Node* C = x->left;
        //Node* D = x->right;

        x->root = z->root;
        x->left = y;

        y->root = x;
        y->right = z;
        y->left = C;

        z->root = y;
        z->right = B;

        if (x->root != nullptr) {
            if (x->root->left == z) x->root->left = x;
            else x->root->right = x;
        }

        if (B != nullptr) B->root = z;
        if (C != nullptr) C->root = y;
    }
}

void SplayTree::zig_zag(Node* x) {// Zig-zag || Zag-zig
    Node* y = x->root;
    Node* z = y->root;
    if (y->right == x) {// Zig-zag
        //Node* A = y->left;
        Node* B = x->left;
        Node* C = x->right;
        //Node* D = z-> right;

        x->root = z->root;
        x->right = y;
        x->left = z;

        y->root = x;
        y->right = B;

        z->root = x;
        z->left = C;

        if (x->root != nullptr) {
            if (x->root->left == z) x->root->left = x;
            else x->root->right = x;
        }

        if (B != nullptr) B->root = y;
        if (C != nullptr) C->root = z;
    } else {// Zag-zig
        Node* A = z->left;
        Node* B = x->left;
        Node* C = x->right;
        Node* D = y->right;

        x->root = z->root;
        x->left = z;
        x->right = y;

        y->root = x;
        y->left = C;

        z->root = x;
        z->right = B;

        if (x->root != nullptr) {
            if (x->root->left == z) x->root->left = x;
            else x->root->right = x;
        }

        if (B != nullptr) B->root = z;
        if (C != nullptr) C->root = y;
    }
}

void SplayTree::splay(Node* x) {
    while (x->root != nullptr) {
        Node* y = x->root;
        Node* z = y->root;
        if (z == nullptr) zig(x);
        else if (z->left == y && y->left == x) zig_zig(x);
        else if (z->right == y && y->right == x) zig_zig(x);
        else zig_zag(x);
    }
    this->root = x;
}

void SplayTree::insert(int key) {
    if (this->root == nullptr) {
        this->root = new Node(key);
        return;
    }
    Node* at = this->root;
    while (at != nullptr) {
        if (key < at->key) {
            if (at->left == nullptr) {
                Node* new_node = new Node(key);
                new_node->root = at;
                at->left = new_node;
                splay(new_node);
                return;
            }
            else at = at->left;
        }
        else if (key > at->key) {
            if (at->right == nullptr) {
                Node* new_node = new Node(key);
                new_node->root = at;
                at->right = new_node;
                splay(new_node);
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
    Node* ret = nullptr;
    Node* prev = nullptr;
    Node* at = this->root;
    while (at != nullptr) {
        prev = at;
        if (at->key == key) {
            ret = at;
            break;
        }
        else if (key < at->key)
            at = at->left;
        else if (key > at->key)
            at = at->right;
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
    cout << "Search 30: " << (tree.search(30) ? "Found" : "Not Found") << endl;
    cout << "Search 100: " << (tree.search(100) ? "Found" : "Not Found") << endl;

    return 0;
}