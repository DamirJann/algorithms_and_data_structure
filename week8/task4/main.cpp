#include <iostream>
#include <map>
#include <vector>
using namespace std;

long long int hashCode(string str, int base);


int main() {
    cout << hashCode("aabcb", 3);
    return 0;
}


long long int hashCode(string str, int base){
    long long int result = 0;
    long long int pow = 1;
    for (int i = 0; i < str.size(); i++){
        result += (str[str.size()-i-1])*pow;
        pow *= base;
    }
    return result % 16;
}

