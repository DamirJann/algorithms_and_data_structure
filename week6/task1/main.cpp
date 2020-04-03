#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

int main() {
    ifstream in("input.txt");
    ofstream out("output.txt");
    int n, m;
    vector<int> array;

    in >> n;

    for (int i = 0; i < n; i++){
        int tmp;
        in >> tmp;
        array.push_back(tmp);
    }

    in >> m;

    for (int i = 0; i < m; i++){
        int num;
        in >> num;
        int l = -1,
            r = n;

        while (l < r - 1){
            int pivot = array[(l+r)/2];
            if (num <= pivot) {
                r = (l + r) / 2;
            }
            else{
                l = (l + r) / 2;
            }
        }

        int l_ind = ((r != n) && (array[r] == num)) ? r : -2;

        l = -1;
        r = n;
        while (l < r - 1){
            int pivot = array[(l+r)/2];
            if (num >= pivot) {
                l = (l + r) / 2;
            }
            else{
                r = (l + r) / 2;
            }
        }

        int r_ind = ((l != -1) && (array[l] == num)) ? l : -2;


        out << l_ind+1 << ' ' << r_ind+1 << '\n';

    }

    in.close();
    out.close();
    return 0;
}
