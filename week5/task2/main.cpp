#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;


class cheap{
private:
    int* array = new int[1000000];
    int size = 0;

    int getLeftChild(const int& i) const;
    int getRightChild(const int& i) const;
    int getParent(const int& i) const;
public:
    int extractMin(const int& x);
    void insert(const int& x);
    void replace(const int& x, const int& y);
    void print() const;
};

int main() {
    ifstream in("input.txt");
    ofstream out("output.txt");
    int n;
    cheap chp;

    in >> n;

    for (int i = 0; i < n; i++){
        string str;
        in >> str;

        switch(str[0]){
            case ('A'):{
                chp.insert(atoi(str.substr(2).c_str()));
                break;
            }
            case ('D'):{
                stringstream stringstream1(str);
                int x, y;
                stringstream1.ignore();
                stringstream1 >> x >> y;
                chp.replace(x, y);
                break;
            }
            default:{
                out << chp.extractMin(atoi(str.c_str())) << endl;
                break;
            }
        }

    }


    in.close();
    out.close();
    return 0;
}


int getLeftChild(const int& i) const{
    
}
int getRightChild(const int& i) const{

}

int getParent(const int& i) const{

}


int cheap::extractMin(const int& x){

}

void cheap::insert(const int& x){

}


void cheap::replace(const int& x, const int& y){

}

void cheap::print() const{
    for (int i = 0; i < size; i++){
        cout << array[i] << ' ';
    }
    cout << endl;
}