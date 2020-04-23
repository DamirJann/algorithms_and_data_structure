#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

class set{
private:
    int HASH_COUNT;
public:
    struct node{
        node(long long int key);
        long long int key;
        long long int value;
        node* pNextNode;
        bool isEqual(long long int key);
    };
private:
    node** hashArray = new node*[100000];
public:
    set();
    int hashCode(long long int key);
    void insert(long long int key);
    bool find(long long int key);
    void erase(long long int key);
};

using namespace std;

int main() {
    ifstream in("input.txt");
    ofstream out("output.txt");

    int n;
    set numbers;
    in >> n;

    for (int i = 0; i < n; i++){
        char command;
        long long int num;
        in >> command >> num;
        switch(command){
            case 'A': {
                numbers.insert(num);
                break;
            }
            case '?': {
                out << (numbers.find(num) ? 'Y':'N') << endl;
                break;
            }
            case 'D': {
                numbers.erase(num);
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

set::set(): HASH_COUNT(100000){
    for (node** p = hashArray; p < hashArray+HASH_COUNT; p++){
        *p = nullptr;
    }
}

set::node::node(long long int key): key(key), pNextNode(nullptr){}

bool set::node::isEqual(long long int key){
    return this->key == key;
}

int set::hashCode(long long int key){
    return abs(key) % HASH_COUNT;
}

void set::insert(long long int key){
    int index = hashCode(key);
    node* p = hashArray[index];

    if (p == nullptr){
        hashArray[index] = new node(key);
    }
    else if (!find(key)){
        hashArray[index] = new node(key);
        hashArray[index]->pNextNode = p;
    }
}

bool set::find(long long int key){
    node* pCurrentNode = hashArray[hashCode(key)];
    while (pCurrentNode != nullptr){
        if (pCurrentNode->isEqual(key)){
            return true;
        }
        pCurrentNode = pCurrentNode->pNextNode;
    }
    return false;
}

void set::erase(long long int key){
    node* pPreviousNode = hashArray[hashCode(key)];

    if (pPreviousNode != nullptr) {
        // deleted node is head
        if (pPreviousNode->isEqual(key)) {
            hashArray[hashCode(key)] = pPreviousNode->pNextNode;
            delete pPreviousNode;
        } else {
            node *pCurrentNode = pPreviousNode->pNextNode;
            while (pCurrentNode != nullptr) {
                if (pCurrentNode->isEqual(key)) {
                    pPreviousNode->pNextNode = pCurrentNode->pNextNode;
                    delete pCurrentNode;
                }
                pPreviousNode = pCurrentNode;
                pCurrentNode = pCurrentNode->pNextNode;
            }
        }
    }
}
