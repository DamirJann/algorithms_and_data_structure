#include <iostream>
#include <fstream>
using namespace std;

class stack{
private:
    int* array = new int[1000000];
public:
    int size = 0;
    void push(const int& elem);
    int pop();
};




int main(){

    ifstream in("input.txt");
    ofstream out("output.txt");

    int n;
    stack stk;

    in >> n;
    for (int i = 0 ; i < n; i++){
        string token;
        in >> token;

        switch (token[0]){
            case '+':
                stk.push(stk.pop()+stk.pop());
                break;
            case '-': {
                int tmp  = -stk.pop();
                stk.push(stk.pop()+tmp);
                break;
            }
            case '*':
                stk.push(stk.pop()*stk.pop());
                break;
            default:
                stk.push(atoi(token.c_str()));
                break;
        }
    }

    out << stk.pop();


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
    return array[size];
}

