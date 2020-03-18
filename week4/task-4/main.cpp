#include <iostream>
#include <fstream>
using namespace std;

class elem{
public:
    int value;
    int localMin;
};


class queue{
private:
    elem* lArray = new elem[1000000];
    elem* rArray = new elem[1000000];
public:
    int lArraySize = 0;
    int rArraySize = 0;

    void push(const int& elem);
    void pop();
    int getMin();
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
        else if (chr == '-'){
            que.pop();
        }
        else{
            out << que.getMin() << endl;
        }
    }

    in.close();
    out.close();
    return 0;
}


void queue::push(const int& newElem){
    lArray[lArraySize].value = newElem;
    lArray[lArraySize].localMin = newElem ;
    if ((lArraySize != 0) && (lArray[lArraySize-1].localMin < newElem)){
        lArray[lArraySize].localMin = lArray[lArraySize-1].localMin;
    }
    lArraySize++;
}





void queue::pop(){
    if (rArraySize == 0){
        while (lArraySize != 0){
            int value = lArray[lArraySize-1].value;
            rArray[rArraySize].value = value;
            rArray[rArraySize].localMin = value;
            if ((rArraySize != 0) && (rArray[rArraySize-1].localMin < rArray[rArraySize].localMin)){
                rArray[rArraySize].localMin = rArray[rArraySize-1].localMin;
            }
            rArraySize++;
            lArraySize--;
        }
    }
    rArraySize--;
}

int queue::getMin(){
    int lArrayMin = lArraySize == 0 ? 1000000000:lArray[lArraySize-1].localMin;
    int rArrayMin = rArraySize == 0 ? 1000000000:rArray[rArraySize-1].localMin;

    return lArrayMin < rArrayMin ? lArrayMin:rArrayMin;

}