#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>

using namespace std;


int main() {
    ifstream in("input.txt");
    ofstream out("output.txt");
    int n, B;
    vector<double> h;

    in >> n;
    h.resize(n);
    in >> h[0];

    double l = 0, r = h[0];
    while (r-l > 0.000000000001){
        h[1] = (r+l)/2;
        bool isLower = true;
        for (int i = 2; i < n; i++){
            h[i] = 2*h[i-1]-h[i-2]+2;
            if (h[i] < 0){
                isLower = false;
                break;
            }
        }

        if (isLower){
            r = (r+l)/2;
        }
        else{
            l = (r+l)/2;
        }
    }



    out << fixed << h[n-1];

    in.close();
    out.close();
    return 0;
}
