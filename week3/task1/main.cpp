#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;


int main() {
    ifstream in("input.txt");
    ofstream out("output.txt");
    vector<string> digit;
    const int CHAR_BORDER = 256;
    const int SHIFT = 8;
    const int MASK = (1 << SHIFT)-1;
    int* counter = new int[CHAR_BORDER];


    int n, m;

    in >> n >> m;
    int* nArray = new int[n];
    int* array = new int[n*m];

    int* tmp = new int[n * m];


    for (int i = 0; i < n; i++){
        in >> *(nArray+i);
    }

    int k = 0;
    for (int i = 0; i < m; i++){
        int num;
        in >> num;
        for (int* j = &nArray[0]; j < &nArray[0]+n; j++){
            *(tmp + k) = (*j) * num;
            k++;
        }
    }



    for (int i = 0; i < 4; i++){

        // clear vector count by zero
        for (int* j = counter; j < counter+CHAR_BORDER; j++){
            *j = 0;
        }
        // count all digits
        for (int j = 0; j < n*m; j++){
            *(array+j)= *(tmp + j);
            counter[((*(array+j)) >> (i*SHIFT)) & MASK]++;
        }
        // summirize
        for (int* j = counter+1; j < counter+CHAR_BORDER; j++){
            *j += *(j-1);
        }
        //change tmp
        for (int* j = array+n*m-1; j >= array; j--){
            tmp[counter[(*j >> (i * SHIFT)) & MASK] - 1] =  *j;
            counter[(*j >> (i*SHIFT)) & MASK]--;
        }
    }

    long long int result = 0;
    for (int* i = tmp; i < tmp + n * m; i+=10){
        result += *i;

    }

    out << result;

    in.close();
    out.close();
    return 0;
}
