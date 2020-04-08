#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

class Tree{
public:
    class node{
    public:
        node(const int& value);
        int key;
        node* left;
        node* right;
        int height;
    };
private:
    node* root = nullptr;

    bool isList(const node* pNode);
    bool isEmptyNode(const node* pNode);
    bool isRoot(const node* pNode);
    int getBalanceFactor(const node* pNode);
    int getHeight(const node* pNode);
    node* balance(node* pNode);
    node* leftRotation(node* pNode);
    node* rightRotation(node* pNode);
    void fixHeight(node* pNode);
    node* balanceToRoot(node* pCurrentNode, node* pNode);
    node* findMax(node* pNode);
    void insert(const int& key, node* pNode);
    node* getParentMax(node* pNode);
    node* getParent(const int& key);
public:
    bool isEmpty();
    void insert(const int& key);
    void remove(const int& key);
    void replaceChild(node* parent, const int& key, node* pChild);
    node* find(const int& key);
    int getBalanceFactor();
};







int main() {
    ifstream in("input.txt");
    ofstream out("output.txt");

    int n;
    Tree tree;

    in >> n;

    for (int i = 0; i < n; i++){
        int key;
        char command;
        in >> command >> key;

        switch (command) {
            case('A'):{
                tree.insert(key);
                out << tree.getBalanceFactor() << endl;
                break;
            }
            case('D'):{
                tree.remove(key);
                out << tree.getBalanceFactor() << endl;
                break;
            }
            case('C'):{
                out << (tree.find(key) == nullptr ? 'N' : 'Y') << endl;
                break;
            }
            default:
                break;
        }
    }



    in.close();
    out.close();
    return 0;
}




Tree::node::node(const int& key):key(key), left(nullptr), right(nullptr), height(1){}




bool Tree::isList(const node* pNode){
    return (pNode->left == nullptr && pNode->right == nullptr);
}

bool Tree::isEmptyNode(const node* pNode){
    return (pNode == nullptr);
}

bool Tree::isRoot(const node* pNode){
    return (root == pNode) && (root != nullptr);
}

int Tree::getBalanceFactor(const node* pNode){
    return getHeight(pNode->right) - getHeight(pNode->left);
}

int Tree::getHeight(const node* pNode){
    return (pNode == nullptr) ? 0:pNode->height;
}
Tree::node* Tree::balance(node* pNode){
    if (getBalanceFactor(pNode) == 2) {
        node* B = pNode;
        node* A = B->right;
        if (getBalanceFactor(A) == -1){
            B->right = rightRotation(A);
        }
        return leftRotation(B);
    }
    else if (getBalanceFactor(pNode) == -2) {
        node* B = pNode;
        node* A = B->left;
        if (getBalanceFactor(A) == 1){
            B->left = leftRotation(A);
        }
        return rightRotation(B);
    }
    return pNode;
}


Tree::node* Tree::leftRotation(node* pNode){
    node* B = pNode;
    node* A = B->right;
    B->right = A->left;
    A->left = B;
    if (B == root){
        root = A;
    }
    fixHeight(B);
    fixHeight(A);

    return A;
}

Tree::node* Tree::rightRotation(node* pNode){
    node* B = pNode;
    node* A = B->left;
    B->left = A->right;
    A->right = B;
    if (B == root){
        root = A;
    }
    fixHeight(B);
    fixHeight(A);
    return A;
}


void Tree::fixHeight(node* pNode){
    if (!isEmptyNode(pNode)){
        pNode->height = 1 + (getHeight(pNode->right) > getHeight(pNode->left) ?
                                   getHeight(pNode->right) : getHeight(pNode->left));
    }
}


Tree::node* Tree::balanceToRoot(node* pCurrentNode, node* pNode){
    if (pCurrentNode == nullptr || pNode == nullptr) return nullptr;

    if (pCurrentNode->key > pNode->key){
        pCurrentNode->left = balanceToRoot(pCurrentNode->left, pNode);
    }
    if (pCurrentNode->key < pNode->key){
        pCurrentNode->right = balanceToRoot(pCurrentNode->right, pNode);
    }
    fixHeight(pCurrentNode);
    return balance(pCurrentNode);
}

Tree::node* Tree::findMax(node* pNode){
    while (pNode->right != nullptr){
        pNode = pNode->right;
    }
    return pNode;
}

bool Tree::isEmpty(){
    return root == nullptr;
}

void Tree::insert(const int& key, node* pNode){

    if (key < pNode->key){
        if (pNode->left == nullptr){
            pNode->left = new node(key);
            balanceToRoot(root, pNode);
        }
        else{
            insert(key, pNode->left);
        }
    }
    else if (key > pNode->key){
        if (pNode->right == nullptr){
            pNode->right = new node(key);
            balanceToRoot(root, pNode);
        }
        else{
            insert(key, pNode->right);
        }
    }
    else {
        return;
    }
}

Tree::node* Tree::getParentMax(node* pNode){

    while (pNode->right->right != nullptr){
        pNode = pNode->right;
    }
    return pNode;
}

Tree::node* Tree::getParent(const int& key){
    node* pNode = root;
    while (pNode != nullptr) {
        if (((pNode->left != nullptr) && (pNode->left->key == key)) ||
            ((pNode->right != nullptr) && (pNode->right->key == key))) {
            return pNode;
        } else {
            if (key < pNode->key) pNode = pNode->left == nullptr ? nullptr:pNode->left;
            else
            if (key > pNode->key) pNode = pNode->right == nullptr ? nullptr:pNode->right;
            else
            if (key == pNode->key) pNode = nullptr;
        }
    }
    return nullptr;
}

void Tree::insert(const int& key){
    if (root == nullptr){
        root = new node(key);
    }
    else {
        insert(key, root);
    }
}

void Tree::remove(const int& key){
    if (root == nullptr) return;
    node* parent = getParent(key);
    if (parent == nullptr && key != root->key){
        return;
    }
    node *pChild = (parent == nullptr) ?
                    root : ((parent->left != nullptr) && (parent->left->key == key)) ? parent->left : parent->right;

    if (isList(pChild)) {
        replaceChild(parent, key, nullptr);
        balanceToRoot(root, parent);
    }
    else if (pChild->left == nullptr) {
        replaceChild(parent, key, pChild->right);
        balanceToRoot(root, parent);
    }
    else {


        node* pMaxParent = (pChild->left->right == nullptr) ? pChild : getParentMax(pChild->left);
        node *pMax = pMaxParent == pChild ? pChild->left : pMaxParent->right;

        replaceChild(parent, key, pMax);
        if (pMaxParent == pChild){
            pMax->right = pChild->right;
        }
        else{
            pMaxParent->right = pMax->left;
            pMax->left = pChild->left;
            pMax->right = pChild->right;
        }
        balanceToRoot(root, pMaxParent);
    }

}

void Tree::replaceChild(node* parent, const int& key, node* pChild) {
    if (parent != nullptr) {
        if ((parent->left != nullptr) && (parent->left->key == key)) {
            parent->left = pChild;
        } else {
            parent->right = pChild;
        }
    }
    else{
        root = pChild;
    }
}

Tree::node* Tree::find(const int& key){
    if (isEmpty()){
        return nullptr;
    }
    node* pNode = root;

    while (true){
        if (key == pNode->key){
            return pNode;
        }
        else if (key < pNode->key){
            if (pNode->left == nullptr){
                return nullptr;
            }
            else{
                pNode = pNode->left;
            }
        }
        else{
            if (pNode->right == nullptr){
                return nullptr;
            }
            else{
                pNode = pNode->right;
            }
        }
    }
}

int Tree::getBalanceFactor(){
    return isEmpty() ? 0:getBalanceFactor(root);
}
