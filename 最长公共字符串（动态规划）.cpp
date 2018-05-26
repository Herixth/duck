#include <iostream>
#include <cstring>
using namespace std;
int count = 0;
const int maxn = 1000;
int b[maxn][maxn];
int c[maxn][maxn];
int x[maxn] = { 0 };
int y[maxn] = { 0 };

void LCS(int m, int n) {
    int i = 0, j = 0;
    for(i = 1; i <= m; i ++)
        c[i][0] = 0;
    for(i = 1; i <= n; i ++)
        c[0][i] = 0;
    c[0][0] = 0;
    for(i = 1; i <= m; i ++)
        for(j = 1; j <= n; j ++) {
            if(x[i - 1] == y[j - 1]) {
                c[i][j] = c[i - 1][j - 1] + 1;
                b[i][j] = 1;
            }
            else if(c[i - 1][j] > c[i][j - 1]) {
                c[i][j] = c[i - 1][j];
                b[i][j] = 2;
            }
            else {
                c[i][j] = c[i][j - 1];
                b[i][j] = 3;
            }
        }
}
 
void show(int i, int j) {
    if(!i || !j) return;
    if(b[i][j] == 1) {
        show(i - 1, j - 1);
        count ++;
    } else if(b[i][j] == 2)
        show(i - 1, j);
    else
        show(i, j - 1);
}
int main() {
    int len = 0;
    cin >> len;
    int m = len, n = len;
    for (int inc = 0; inc < len; inc ++) 
    	cin >> x[inc];
    for (int inc = 0; inc < len; inc ++)
    	cin >> y[inc];
    LCS(m, n);
    show(m, n);
    cout << count << endl;
}
