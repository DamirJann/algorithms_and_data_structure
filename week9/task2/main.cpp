#include <iostream>
#include <fstream>
#include <vector>

using namespace std;
int main() {


    ifstream in("input.txt");
    ofstream out("output.txt");

    string str;
    long long int counter = 0;
    vector<vector<int>> chars(256);
    char chr;

    int k = 0;
    while (in >> chr){
        if (chr != ' '){
            chars[chr].push_back(k);
            k++;
        }
    }

    for (auto index: chars){
        long long int n = index.size();
        if (n >= 2) {
            long long int S = -((n-1)*n)/2;
            for (int i = 0; i < n; i++) {
                S += index[i] *(2*i-n+1);
            }
            counter += S;
        }

    }

    out << counter;

    in.close();
    out.close();
    return 0;
}
