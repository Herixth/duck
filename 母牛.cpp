#include <iostream>  
using namespace std;  

int main() {  
    int num, i;  
    int f[56] = { 0, 1, 2, 3 };  
    for(i = 4; i <= 55; i ++)  
        f[i] = f[i - 1] + f[i - 3];  
    cin >> num;
    cout<< f[num] <<endl;  
    return 0;  
}
