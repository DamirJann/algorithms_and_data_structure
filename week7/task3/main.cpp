#include <iostream>
#include <vector>
#include <fstream>

using namespace std;




class Tree{
public:
    class node{
    public:
        node(const int& value);
        node();
        int value;
        int left;
        int right;
        int parent = 0;
        int height = 1;
    };
private:
    int root = 1;
    int size;
    vector<node> array;
    int subTreeCount(const int& currentNode) const;
    int getLeft(const int& currentNode) const;
    int getRight(const int& currentNode) const;
    int getParent(const int& currentNode) const;
    int getValue(const int& currentNode) const;
    void printTree(ofstream& out, const int& currentNode) const;
    void fixHeight(const int& currentNode);
public:
    void insert(const int& key);
    int getHeight(const int& CurrentNode) const;
    void read(ifstream& in);
    int removeByKey(const int& key);
    int getNode(const int& key) const;
    int getSize() const;
    int setHeights(int currentNode);
    void printBalanceFactors(ofstream& out) const;
    void printTree(ofstream& out) const;
    int getBalanceFactor(const int& currentNode) const;
    void balance(const int& currentNode);
};





int main() {
    ifstream in("input.txt");
    ofstream out("output.txt");

    Tree tree;
    tree.read(in);

    int key;
    in >> key;

    tree.setHeights(1);
    tree.insert(key);
    tree.printTree(out);



    in.close();
    out.close();
    return 0;
}

void Tree::read(ifstream& in){
    int n;
    in >> n;
    size = n;
    array.resize(n+1);
    for (int i = 1; i <= n; i++){
        int l, r;
        in >> array[i].value >> array[i].left >> array[i].right;
        array[getLeft(i)].parent = i;
        array[getRight(i)].parent = i;
    }
}

int Tree::getHeight(const int& currentNode) const{
    if (size == 0 || currentNode == 0){
        return 0;
    }
    return array[currentNode].height;
}




int Tree::removeByKey(const int& key){

    int currentNode = getNode(key);
    size -=  subTreeCount(currentNode);

    if (array[currentNode].parent != 0){
        if (getLeft(getParent(currentNode)) == currentNode){
            array[getParent(currentNode)].left = 0;
        }
        else{
            array[getParent(currentNode)].right = 0;
        }
    }
    return size;
}


int Tree::subTreeCount(const int& currentNode) const{
    if (currentNode == 0){
        return 0;
    }
    return 1 + subTreeCount(getLeft(currentNode)) + subTreeCount(getRight(currentNode)) ;

}

int Tree::getSize() const{
    return size;
}


int Tree::getNode(const int& key) const{
    if (size == 0) {
        return 0;
    }
    else{
        int currentNode = root;
        while (array[currentNode].value != key){
            if (key < array[currentNode].value){
                if (getLeft(currentNode) == 0){
                    currentNode = 0;
                    break;
                }
                else{
                    currentNode = getLeft(currentNode);
                }
            }
            else{
                if (getRight(currentNode) == 0){
                    currentNode = 0;
                    break;
                }
                else{
                    currentNode = getRight(currentNode);
                }
            }
        }
        return currentNode;
    }

}

int Tree::getLeft(const int& currentNode) const{
    return array[currentNode].left;
}
int Tree::getRight(const int& currentNode) const {
    return array[currentNode].right;
}
int Tree::getParent(const int& currentNode) const{
    return array[currentNode].parent;
}
int Tree::getValue(const int& currentNode) const{
    return array[currentNode].value;
}


int Tree::setHeights(int currentNode){
    if (currentNode == 0 || size == 0){
        return 0;
    }

    int leftHeight = setHeights(getLeft(currentNode));
    int rightHeight = setHeights(getRight(currentNode));

    array[currentNode].height = 1 + (leftHeight > rightHeight ? leftHeight : rightHeight);

    return array[currentNode].height;
}

void Tree::printBalanceFactors(ofstream &out) const{
    for (int i = 1; i <= size; i++){
        out << getBalanceFactor(i) << '\n';
    }
}

int Tree::getBalanceFactor(const int& currentNode) const{
    return getHeight(getRight(currentNode))-getHeight(getLeft(currentNode));
}

void Tree::balance(const int& currentNode){
    if (getBalanceFactor(currentNode) == 2) {
        int B = currentNode;
        int A = getRight(currentNode);

        // double rotation
        if (getBalanceFactor(A) == -1) {
            int C = getLeft(A);
            array[getLeft(C)].parent = B;
            array[getRight(C)].parent = A;
            array[B].right = getLeft(C);
            array[A].left = getRight(C);
            array[C].parent = getParent(B);
            if (getParent(B) != 0){
                if (getLeft(getParent(B)) == B){
                    array[getParent(B)].left = C;
                }
                else{
                    array[getParent(B)].right = C;
                }
            }
            array[C].left = B;
            array[C].right = A;
            array[B].parent = C;
            array[A].parent = C;
            if (root == B) {
                root = C;
            }
            fixHeight(A);
            fixHeight(B);
            fixHeight(C);
        }
        //simple rotation
        else {
            array[getLeft(A)].parent = B;
            array[B].right = getLeft(A);
            array[A].parent = getParent(B);
            if (getParent(B) != 0){
                if (getLeft(getParent(B)) == B){
                    array[getParent(B)].left = A;
                }
                else{
                    array[getParent(B)].right = A;
                }
            }
            array[B].parent = A;
            array[A].left = B;
            if (root == B) {
                root = A;
            }
            fixHeight(B);
            fixHeight(A);
        }
    }
    else if (getBalanceFactor(currentNode) == -2){
        int B = currentNode;
        int A = getLeft(currentNode);
        // double rotation
        if (getBalanceFactor(A) == 1) {
            int C = getRight(A);
            array[getLeft(C)].parent = A;
            array[getRight(C)].parent = B;
            array[B].left = getRight(C);
            array[A].right = getLeft(C);
            array[C].parent = getParent(B);
            if (getParent(B) != 0){
                if (getLeft(getParent(B)) == B){
                    array[getParent(B)].left = C;
                }
                else{
                    array[getParent(B)].right = C;
                }
            }
            array[C].left = A;
            array[C].right = B;
            array[B].parent = C;
            array[A].parent = C;
            if (root == B) {
                root = C;
            }
            fixHeight(A);
            fixHeight(B);
            fixHeight(C);
        }
        //simple rotation
        else {
            array[getRight(A)].parent = B;
            array[B].left = getRight(A);
            array[A].parent = getParent(B);
            if (getParent(B) != 0){
                if (getLeft(getParent(B)) == B){
                    array[getParent(B)].left = A;
                }
                else{
                    array[getParent(B)].right = A;
                }
            }
            array[B].parent = A;
            array[A].right = B;
            if (root == B) {
                root = A;
            }
            fixHeight(B);
            fixHeight(A);

        }

    }

}

void Tree::printTree(ofstream& out) const{
    int number = 1;
    int ind = 0;
    vector<int> deck(0);
    deck.push_back(root);

    out << size << endl;
    while (ind < deck.size()){
        out << getValue(deck[ind]) << ' ';
        if (getLeft(deck[ind]) != 0){
            deck.push_back(getLeft(deck[ind]));
            number++;
            out << number;
        }
        else{
            out << 0;
        }

        out << ' ';
        if (getRight(deck[ind]) != 0){
            deck.push_back(getRight(deck[ind]));
            number++;
            out << number;
        }
        else{
            out << 0;
        }
        out << endl;
        ind++;

    }


}

void Tree::printTree(ofstream& out, const int& currentNode) const{
    if (currentNode == 0){
        return;
    }
    out << getValue(currentNode) << ' ' << getLeft(currentNode) << ' ' << getRight(currentNode) << endl;

    printTree(out, getLeft(currentNode));
    printTree(out, getRight(currentNode));
}

void Tree::insert(const int& key){

    array.emplace_back(key);
    size++;

    if (size == 1) {
        root = size;
    }
    else{
        int currentNode = root;
        bool isFounded = false;
        while (!isFounded){
            if (key < getValue(currentNode)){
                if (getLeft(currentNode) == 0){
                    array[currentNode].left = size;
                    array[size].parent = currentNode;
                    isFounded = true;
                }
                else{
                    currentNode = getLeft(currentNode);
                }
            }
            else if (key > getValue(currentNode)){
                if (getRight(currentNode) == 0){
                    array[currentNode].right = size;
                    array[size].parent = currentNode;
                    isFounded = true;
                }
                else{
                    currentNode = getRight(currentNode);
                }
            }
        }

        while (currentNode != 0){
            balance(currentNode);
            fixHeight(currentNode);
            currentNode = getParent(currentNode);
        }
    }
}

Tree::node::node():node(0){}
Tree::node::node(const int& value):value(value), left(0), right(0), parent(0), height(1){}

void Tree::fixHeight(const int& currentNode){
    if (currentNode != 0){
        array[currentNode].height = 1+ (getHeight(getRight(currentNode)) > getHeight(getLeft(currentNode)) ?
                                    getHeight(getRight(currentNode)) : getHeight(getLeft(currentNode)));
    }
}