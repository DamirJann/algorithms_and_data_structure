#include <iostream>
#include <fstream>
using namespace std;

class stack{
private:
    int array[100000];
public:
    int size = 0;
    void push(const int& elem);
    int pop();
};







int main() {
    ifstream in("input.txt");
    ofstream out("output.txt");

    stack stk;
    int n;

    in >> n;

    for (int i = 0; i < n; i++){
        int chr;
        in >> chr;
        if (chr ==  '+'){
            int elem;
            in >> elem;
            stk.push(elem);

        }
        else{
            out << stk.pop() << endl;
        }
    }

    in.close();
    out.close();
    return 0;
}


void stack::push(const int& elem){
    array[size] = elem;
    size++;
}

int stack::pop(){
    size--;
    return array[size+1];
}