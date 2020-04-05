#include <iostream>
#include <vector>
#include <fstream>

using namespace std;




class Tree{
private:
    struct node{
        int value;
        int left;
        int right;
        int parent = 0;
        int height = 1;
    };
    int size;
    vector<node> array;
    int subTreeCount(const int& currentNode) const;
    int getLeft(const int& currentNode) const;
    int getRight(const int& currentNode) const;
    int getParent(const int& currentNode) const;
public:
    int getHeight(const int& CurrentNode) const;
    void read(ifstream& in);
    int removeByKey(const int& key);
    int getNodeByKey(const int& key) const;
    int getSize() const;
    int setHeights(int currentNode);
    void printBalanceFactors(ofstream& out) const;
    int getBalanceFactor(const int& currentNode) const;
};





int main() {
    ifstream in("input.txt");
    ofstream out("output.txt");

    Tree tree;
    tree.read(in);

    tree.setHeights(1);
    tree.printBalanceFactors(out);



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

    int currentNode = getNodeByKey(key);
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


int Tree::getNodeByKey(const int& key) const{
    if (size == 0) {
        return 0;
    }
    else{
        int currentNode = 1;
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

int Tree::setHeights(int currentNode){
    if (currentNode == 0){
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