#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <map>

using namespace std;




class cheap{
private:
    int lines[100009];
    int location[100009];
    int array[100009];
    int size = 0;

    int getLeftChild(const int& i) const;
    int getRightChild(const int& i) const;
    int getParent(const int& i) const;

public:
    string extractMin();
    void insert(const int& lineInd, const int& x);
    void replace(const int& x, const int& y);
    void siftUp(int i);
    void siftDown(int i);
    void print() const;

};

int main() {
    ifstream in("input.txt");
    ofstream out("output.txt");
    int n;
    cheap chp;

    in >> n;

    for (int i = 2; i < n+2; i++){
        string str;
        in >> str;



        switch(str[0]){
            case ('A'):{
                string number;
                in >> number;
                chp.insert(i, atoi(number.c_str()));
                break;
            }
            case ('D'):{
                int x, y;
                in >> x >> y;
                chp.replace(x+1, y);
                break;
            }
            default:{
                out << chp.extractMin() << endl;
                break;
            }
        }

    }

    in.close();
    out.close();
    return 0;
}







int cheap::getLeftChild(const int& i) const{
    return (i+1)*2-1 >= size ? i : (i+1)*2-1;
}
int cheap::getRightChild(const int& i) const{
    return (i+1)*2 >= size ? i : (i+1)*2;
}

pint cheap::getParent(const int& i) const{
    return i == 0 ? 0 : (i-1)/2;
}


string cheap::extractMin(){
    if (size == 0) return "*";
    int min = array[0];
    array[0] = array[size-1];
    location[0] = lines[size-1];
    lines[size-1] = 0;
    size--;
    siftDown(0);
    return to_string(min);
}

void cheap::insert(const int& lineInd, const int& x){
    lines[lineInd] = size;
    location[size] = lineInd;
    array[size] = x;
    size++;
    siftUp(size-1);
}


void cheap::replace(const int& x, const int& y){
    int index = lines[x];

    array[index] = y;



    siftUp(index);

}

void cheap::siftUp(int i){
    while ((getParent(i) != i) && (array[i] < array[getParent(i)])){

        swap(array[i], array[getParent(i)]);
        swap(lines[location[i]], lines[location[getParent(i)]]);
        swap(location[i], location[getParent(i)]);
        i = getParent(i);
    }
}

void cheap::siftDown(int i) {
    while (getLeftChild(i) != i) {
        int indOfMin = array[getLeftChild(i)] < array[getRightChild(i)] ? getLeftChild(i) : getRightChild(i);
        if (array[i] > array[indOfMin]) {
            swap(array[i], array[indOfMin]);
            swap(lines[location[i]], lines[location[indOfMin]]);
            swap(location[i], location[indOfMin]);
            i = indOfMin;
        } else {
            break;
        }

    }
}

void cheap::print() const{
    for (int i = 0; i < size; i++){
        cout << array[i] << '-' << array[i] << ' ' ;
    }
    cout << endl;
}

