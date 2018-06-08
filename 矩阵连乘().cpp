#include <iostream>  
using namespace std;
const int maxn = 2000;  
int p[maxn] = { 0 };
int m[maxn][maxn] = { 0 };  

void Mchain(int n) {  
    for(int r = 2; r <= n; r ++) {  
        for(int i = 0; i <= n - r; i ++) {  
            int j = i + r - 1;  
            m[i][j] = m[i][i] + m[i + 1][j] + p[i] * p[i + 1] * p[j + 1];  
            for(int k = i + 1; k < j; k ++) {  
                int t = m[i][k] + m[k + 1][j] + p[i] * p[k + 1] * p[j + 1];  
                if(t < m[i][j]) {  
                    m[i][j] = t;  
                }  
            }  
        }  
    }  
}
  
int main() {  
    int n;  
    
    cin >> n;  
    for(int i = 0; i <= n; i ++)   
        cin >> p[i];  
        
    for(int i = 0; i < n; i ++)   
        m[i][i] = 0;   
  
    Mchain(n);  
    cout << m[0][n - 1] << endl;  
    return 0;  
}  
