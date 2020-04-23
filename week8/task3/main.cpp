#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

class set{
private:
    int HASH_COUNT;
public:
    int count = 0;
public:
    long long int key;
private:
    long long int* hashArray = new long long int[20'000'000];
public:
    set();
    bool insert(long long int key);
    long long int h(long long int key, long long int i);
};

using namespace std;

int main() {
    ifstream in("input.txt");
    ofstream out("output.txt");

    long long int N, X, A, B, AC, BC, AD, BD;
    set numbers;
    in >> N >> X >> A >> B >> AC >> BC >> AD >> BD;

    for (long long int i = 0; i < N; i++){
        if (!numbers.insert(X)){
            A = (A+AC) % 1000;
            B = (B+BC) % 1000000000000000;
        }
        else{
            A = (A+AD) % 1000;
            B = (B+BD) % 1000000000000000;
        }
        X = (X*A+B) % 1000000000000000;
    }

    out << X << ' ' << A << ' ' << B;
    cout << numbers.count;
    in.close();
    out.close();

    return 0;
}

set::set(): HASH_COUNT(20'000'000){
    for (long long int* p = hashArray; p < hashArray+HASH_COUNT; p++){
        *p = -1;
    }
}


bool set::insert(long long int key){
    bool isInserted = false;

    for (long long int i = 0; (i < HASH_COUNT) && (!isInserted); i++){
        int j = (key%HASH_COUNT+key/HASH_COUNT+i) % HASH_COUNT;
        if (hashArray[j] == -1){
            hashArray[j] = key;
            isInserted = true;
           count++;
           if (count % 10000 == 0) cout << count << endl;

        }
        else if (hashArray[j] == key){
            break;
        }
    }
    return isInserted;
}


long long int set::h(long long int key, long long int i){
    return (key%HASH_COUNT+key/HASH_COUNT+i) % HASH_COUNT;
}