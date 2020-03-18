#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

int normilize(const char& chr);


int main() {
    ifstream in("input.txt");
    ofstream out("output.txt");
    vector<string> digit;
    const int CHAR_BORDER = 26;
    vector<int> counter(CHAR_BORDER);
    vector<int> position, newPosition;

    int n, m, k;

    in >> n >> m >> k;

    for (int i = 0; i < n; i++){
        position.push_back(i);
        newPosition.push_back(i);
    }

    for (int i = 0; i < m; i++){
        string buf;
        in >> buf;
        digit.push_back(buf);
    }



    for (int i = 0; i < k; i++){

        // clear vector count by zero
        for (int j = 0; j < CHAR_BORDER; j++){
            counter[j] = 0;
        }
        // count all digits
        for (int j = 0; j < n; j++){
            counter[normilize(digit[m-i-1][j])]++;
        }
        // summirize
        for (int j = 1; j < CHAR_BORDER; j++){
            counter[j] += counter[j-1];
        }
        // change position
        for (int j = n-1; j >= 0; j--){
            char chr = digit[m-i-1][position[j]];
            newPosition[counter[normilize(chr)]-1] = position[j];
            counter[normilize(digit[m-i-1][position[j]])]--;
        }
        // save position
        for (int j = 0; j < n; j++){
            position[j] = newPosition[j];
        }

    }

    for (int i = 0; i < n; i++){
        out << position[i]+1 << ' ';
    }
    in.close();
    out.close();
    return 0;
}

int normilize(const char& chr){
    return int(chr)-97;
}