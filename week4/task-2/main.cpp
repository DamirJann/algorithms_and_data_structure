#include <iostream>
#include <fstream>
using namespace std;

class queue{
private:
    int array[1000000];
public:
    const int MAX_SIZE = 1000000;
    int head = 0;
    int tail = 0;
    void push(const int& elem);
    int pop();
};







int main() {
    ifstream in("input.txt");
    ofstream out("output.txt");

    queue que;
    int n;

    in >> n;

    for (int i = 0; i < n; i++){
        char chr;
        in >> chr;
        if (chr ==  '+'){
            int elem;
            in >> elem;
            que.push(elem);

        }
        else{
            out << que.pop() << endl;
        }
    }

    in.close();
    out.close();
    return 0;
}


void queue::push(const int& elem){

    array[tail] = elem;
    tail = tail == MAX_SIZE ? 0:tail+1;
}

int queue::pop(){
    int elem = array[head];
    head = (head+1) == MAX_SIZE ? 0:head+1;
    return elem;
}