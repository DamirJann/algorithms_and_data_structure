#include <iostream>
#include <vector>
#include <fstream>
using namespace std;
int main() {

    vector<int> index;

    ifstream in("input.txt");
    ofstream out("output.txt");

    string p, t;

    in >> p >> t;

    for (int i = 0; i < t.size()-p.size()+1; i++){
        bool isDiff = false;
        for (int j = 0; j < p.size(); j++){
            if (p[j] != t[i+j]){
                isDiff = true;
                break;
            }
        }
        if (!isDiff){
            index.push_back(i);
        }
    }

    out << index.size() << endl;
    for (auto i: index){
        out << i+1 << ' ';
    }


    in.close();
    out.close();

    return 0;
}
