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

class BinTree {
    private:
        node_ptr root;
    public:
        BinTree() : root(nullptr) {};
        void insert(int key);
        bool search(int target);
};

void BinTree::insert(int key) {
    if (this->root == nullptr) {
        this->root = make_shared<Node>(Node(key));
        return;
    }
    node_ptr at = this->root;
    while (at != nullptr) {
        if (key < at->key) {
            if (at->left == nullptr) {
                at->left = make_shared<Node>(Node(key));
                at->left->parent = at;
                return;
            }
            else at = at->left;
        }
        else if (key > at->key) {
            if (at->right == nullptr) {
                at->right = make_shared<Node>(Node(key));
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
    shared_ptr<Node> at = this->root;
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

int main() {
    // BinTree Testing
    cout << "Testing BinTree:\n";
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
    cout << "\tSearch 30: " << (binTree.search(30) ? "Found" : "Not Found") << endl;
    cout << "\tSearch 100: " << (binTree.search(100) ? "Found" : "Not Found") << endl;

    return 0;
}