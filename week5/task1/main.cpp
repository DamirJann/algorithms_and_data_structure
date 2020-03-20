#include <iostream>
#include <vector>
#include <fstream>
using namespace std;






int main() {
    ifstream in("input.txt");
    ofstream out("output.txt");

    int n;
    bool isCheap = true;
    vector<int> cheap;
    cheap.reserve(1000000);
    in >> n;

    for (int i = 0; i < n; i++){
        int buffer;
        in >> buffer;
        cheap.push_back(buffer);
    }

    for (int i = cheap.size()-1; (isCheap) && (i >= 1); i--){
        if (cheap[i] < cheap[(i-1)/2]){
            isCheap = false;
        }
    }

    out << (isCheap ? "YES":"NO");

    in.close();
    out.close();
    return 0;
}

