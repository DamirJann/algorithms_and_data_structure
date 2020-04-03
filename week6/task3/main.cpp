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
    };
    vector<node> array;
    int size;

public:
    int getHeight() const;
    int getHeight(const int& currentNode) const;
    void read(ifstream& in);
};





int main() {
    ifstream in("input.txt");
    ofstream out("output.txt");

    Tree tree;
    tree.read(in);


    out << tree.getHeight();

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

