#include <iostream>
#include <fstream>
using namespace std;
 
void flip(int& a) {
    a = (a == 0) ? 1 : 0;
}
 
int main() {
  
 
    ifstream input("../input3.txt") ;
    if (!input) {
        cout << "Failed to open input file \n" ;
        return 1 ;
    }
 
    int k = 0, n = 0 ;
    input >> k >> n ;
 
    int arr[1000];
    for (int i = 0; i < n; i++) {
        if (!(input >> arr[i]) || (arr[i] != 0 && arr[i] != 1)) {
            cout << "Invalid or missing binary data.\n";
            return 1;
        }
    }
    input.close() ;
 
    int count = 0 ;
    for (int i = 0 ; i <= n - k ; i++) {
        if (arr[i] == 0) {
            for (int j = 0; j < k; j++) {
                flip(arr[i + j]);
            }
            count++;
        }
    }
 
    for (int i = 0; i < n; i++) {
        if (arr[i] == 0) {
            cout << -1 << endl;
            return 0;
        }
    }
 
    cout << "Minimum number of flips = " << count << endl;
    return 0;
}