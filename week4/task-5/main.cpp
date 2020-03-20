
#include <iostream>
#include <fstream>
#include <string>
#include <map>
using namespace std;

class queue{
private:
    int* array = new int[1000000];
public:
    const int NUM_RANGE = 65536;
    const int MAX_SIZE = 1000000;
    int head = 0;
    int tail = 0;
    void push(const long long& elem);
    int pop();
};







int main() {
    ifstream in("input.txt");
    ofstream out("output.txt");

    queue que;
    bool isQ = false;
    auto* command = new string[1000000];
    map<string, int> labels;
    int reg[26];
    int n;

    for (int & i : reg){
        i = 0;
    }

    int i = 0;
    while (getline(in, command[i])){
        if (command[i][0] != ':') {
            i++;
        }
        else{
            labels[command[i].substr(1)] = i;
        }
    }
    n = i;
    i = 0;

    while ((!isQ) && (i < n)){

        switch (command[i][0]) {
            case '+': {
                int leftO = que.pop();
                int rightO = que.pop();
                que.push(leftO + rightO);
                break;
            }
            case '-':{
                int leftO = que.pop();
                int rightO = que.pop();
                que.push(leftO - rightO);
                break;
            }
            case '*': {
                long long leftO = que.pop();
                long long rightO = que.pop();
                que.push(leftO * rightO);
                break;
            }
            case '/': {
                int leftO = que.pop();
                int rightO = que.pop();
                que.push(rightO == 0 ? 0 : leftO/rightO);
                break;
            }
            case '%': {
                int leftO = que.pop();
                int rightO = que.pop();
                que.push(rightO == 0 ? 0 : leftO % rightO);
                break;
            }
            case '>' :
                reg[command[i][1]-'a'] = que.pop();
                break;
            case '<':
                que.push(reg[command[i][1]-'a']);
                break;
            case 'P':
                out << (command[i].size() == 1 ? que.pop() : reg[command[i][1]-'a']) << endl;
                break;
            case 'C':
                out << static_cast<char>((command[i].size() == 1 ? que.pop(): reg[command[i][1]-'a']) % 256);
                break;
            case 'J': {
                i = labels[command[i].substr(1)]-1;
                break;
            }
            case 'Z':
                if (reg[command[i][1]-'a'] == 0){
                    i = labels[command[i].substr(2)]-1;
                }
                break;
            case 'E': {
                if (reg[command[i][1]-'a'] == reg[command[i][2]-'a']){
                    i = labels[command[i].substr(3)]-1;
                }
                break;
            }
            case 'G': {
                if (reg[command[i][1] - 'a'] > reg[command[i][2] - 'a']) {
                    i = labels[command[i].substr(3)] - 1;
                }
                break;
            }
            case 'Q': {
                isQ = true;
                break;
            }
            default:{
                que.push(atoi(command[i].c_str()));
            }
        };
        i++;
    }

    in.close();
    out.close();
    return 0;
}


void queue::push(const long long& elem){

    array[tail] = (elem+NUM_RANGE) % NUM_RANGE;
    tail = tail == MAX_SIZE ? 0:tail+1;
}

int queue::pop(){
    int elem = array[head];
    head = head+1 == MAX_SIZE ? 0:head+1;
    return elem;
}
