#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

struct node{
    node(const string& key, const string& value);
    string key;
    string value;
    node* pNextNode;
    node* prev;
    node* next;
    bool isEqual(const string& key) const;
    ~node();
};

class set{
private:
    int BUCKET_COUNT;
private:
    node** hashArray = new node*[1000000];
    node* pCurrentNode;
public:
    set();
    int hashCode(const string& key) const;
    void insert(const string& key, const string& value);
    node* find(const string& key) const;
    void erase(const string& key);
};

using namespace std;

int main() {
    ifstream in("input.txt");
    ofstream out("output.txt");

    int n;
    set numbers;
    in >> n;

    for (int i = 0; i < n; i++){
        string command, key, value;
        in >> command >> key;
        if (command == "put"){
            in >> value;
            numbers.insert(key, value);
        }
        else if (command == "get"){
            node* pNode = numbers.find(key);
            out << (pNode == nullptr ? "<none>" : pNode->value) << endl;
        }
        else if (command == "prev"){
            node* pNode = numbers.find(key);
            out << ((pNode == nullptr) || (pNode->prev == nullptr) ?
                    "<none>":pNode->prev->value) << endl;
        }
        else if (command == "next"){
            node* pNode = numbers.find(key);
            out << ((pNode == nullptr) || (pNode->next == nullptr) ?
                    "<none>":pNode->next->value) << endl;
        }
        else if (command == "delete"){
            numbers.erase(key);
        }
    }

    in.close();
    out.close();

    return 0;
}

node::~node(){
    node* left = this->prev;
    node* right = this->next;

    if (left != nullptr){
        left->next = right;
    }
    if (right != nullptr){
        right->prev = left;
    }

}

set::set(): BUCKET_COUNT(1000000), pCurrentNode(nullptr){
    for (node** p = hashArray; p < hashArray + BUCKET_COUNT; p++){
        *p = nullptr;
    }
}

node::node(const string& key, const string& value): key(key), value(value), pNextNode(nullptr), next(nullptr), prev(nullptr){}

bool node::isEqual(const string& key) const{
    return this->key == key;
}

int set::hashCode(const string& key) const{
    long long int hash = 0;
    long long int p = 3;

    for (int i = 0; i < key.size(); i++){
        p = p*3;
        hash += key[i]*i*p;
    }
    return hash % BUCKET_COUNT;
}

void set::insert(const string& key, const string& value){
    int index = hashCode(key);
    node* p;

    if ((p = find(key)) != nullptr){
        p->value = value;
    }
    else {
        p = hashArray[index];
        if (p == nullptr) {
            hashArray[index] = new node(key, value);
        } else {
            hashArray[index] = new node(key, value);
            hashArray[index]->pNextNode = p;
        }

        // change pCurrentNode
        if (pCurrentNode != nullptr) {
            pCurrentNode->next = hashArray[index];
            hashArray[index]->prev = pCurrentNode;
        }
        pCurrentNode = hashArray[index];
    }
}

node* set::find(const string& key) const{
    node* pCurrentNode = hashArray[hashCode(key)];
    while (pCurrentNode != nullptr){
        if (pCurrentNode->isEqual(key)){
            return pCurrentNode;
        }
        pCurrentNode = pCurrentNode->pNextNode;
    }
    return nullptr;
}

void set::erase(const string& key){
    node* pPreviousNode = hashArray[ hashCode(key)];

    if (pPreviousNode != nullptr) {
        // deleted node is head
        if (pPreviousNode->isEqual(key)) {
            hashArray[ hashCode(key)] = pPreviousNode->pNextNode;
            if (pPreviousNode == pCurrentNode) pCurrentNode = pPreviousNode->prev;
            delete pPreviousNode;
        } else {
            node *pCurrentNode = pPreviousNode->pNextNode;
            while (pCurrentNode != nullptr) {
                if (pCurrentNode->isEqual(key)) {
                    pPreviousNode->pNextNode = pCurrentNode->pNextNode;
                    if (this->pCurrentNode == pCurrentNode) this->pCurrentNode = pCurrentNode->prev;
                    delete pCurrentNode;
                }
                pPreviousNode = pCurrentNode;
                pCurrentNode = pCurrentNode->pNextNode;
            }
        }
    }
}
