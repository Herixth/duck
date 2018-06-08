#include <iostream>
using namespace std;

void Calculate(long a, long b, long &x, long &y){  
    if(!b){  
        x = 1;
		y = 0;  
        return;  
    }  
    Calculate(b, a % b, y, x);  
    y -= a / b * x;  
    return;  
}  

int main(){  
    long a, b;  
    for( ; ; ){
    	cin >> a >> b;
		if(!a && !b) break;  
        long x, y;  
        Calculate(a, b, x, y);
		cout << (x + b) % b << endl;  
    }  
    return 0; 
} 

