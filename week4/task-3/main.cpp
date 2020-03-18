#include <iostream>
#include <fstream>
#include <string>
#include <map>
using namespace std;

class stack{
private:
    int array[100000];
public:
    int size = 0;
    void push(const int& elem);
    int pop();
    const int top();
};







int main() {
    ifstream in("input.txt");
    ofstream out("output.txt");
    map<char, char> dict = {
            {'(', ')'},
            {'[', ']'}
    };
    int n;

    in >> n;

    for (int i = 0; i < n; i++){
        stack stk;
        string sequence;
        bool isCorrect = true;
        in >> sequence;

        for (int i = 0; (isCorrect) && (i < sequence.size()); i++){
            if ((sequence[i] == '(') || (sequence[i] == '[')){
                stk.push(sequence[i]);
            }
            else{
                if ((stk.size == 0) || (dict[stk.pop()] != sequence[i])){
                    isCorrect = false;
                }

            }
        }
        if (stk.size != 0) isCorrect = false;

        out << (isCorrect? "YES": "NO" ) << endl;
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
    return array[size];
}

const int stack::top(){
    return array[size-1];
}