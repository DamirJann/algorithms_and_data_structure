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
    };
    int size;
    vector<node> array;
    int getHeight(const int& currentNode) const;
    int subTreeCount(const int& currentNode) const;
    int getNodeByKey(const int& key, const int& currentNode) const;

public:
    int getHeight() const;
    void read(ifstream& in);
    int removeByKey(const int& key);
    int getNodeByKey(const int& key) const;
    int getSize() const;
};





int main() {
    ifstream in("input.txt");
    ofstream out("output.txt");

    Tree tree;
    tree.read(in);

    int m;

    in >> m;

    for (int i = 0; i < m; i++){
        int key;
        in >> key;
        tree.removeByKey(key);
        out << tree.getSize() << '\n';
    }



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
        array[array[i].left].parent = i;
        array[array[i].right].parent = i;
    }
}

int Tree::getHeight() const{
    return (size == 0 ? 0 : getHeight(1));
}


int Tree::getHeight(const int& currentNode) const{
    if (currentNode == 0){
        return 0;
    }

    int leftHeight = getHeight(array[currentNode].left);
    int rightHeight = getHeight(array[currentNode].right);

    return 1 + (leftHeight > rightHeight ? leftHeight : rightHeight);
}

int Tree::removeByKey(const int& key){

    int currentNode = getNodeByKey(key);
    size -=  subTreeCount(currentNode);

    if (array[currentNode].parent != 0){
        if (array[array[currentNode].parent].left == currentNode){
            array[array[currentNode].parent].left = 0;
        }
        else{
            array[array[currentNode].parent].right = 0;
        }
    }
    return size;
}


int Tree::subTreeCount(const int& currentNode) const{
    if (currentNode == 0){
        return 0;
    }
    return 1 + subTreeCount(array[currentNode].left) + subTreeCount(array[currentNode].right) ;

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
                if (array[currentNode].left == 0){
                    currentNode = 0;
                    break;
                }
                else{
                    currentNode = array[currentNode].left;
                }
            }
            else{
                if (array[currentNode].right == 0){
                    currentNode = 0;
                    break;
                }
                else{
                    currentNode = array[currentNode].right;
                }
            }
        }
        return currentNode;
    }

}

